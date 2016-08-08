#include "InternetButton.h"
#include "time.h"

#define POMODORO_TIME 1

InternetButton button = InternetButton();
int numberOfButtons = 11;
int ledDelayInMillis = 100;
unsigned long pomodoroMillis = POMODORO_TIME * 60 * 1000;
unsigned long lastUpdate = millis();
int ledIndex = 0;

enum PomodoroState { None, Active, ShortBreak, LongBreak, Cancelled, Complete };
PomodoroState previousState, pomodoroState = None;

// Log message to cloud, message is a printf-formatted string
void debug(String message, int value) {
    char msg [50];
    sprintf(msg, message.c_str(), value);
    Particle.publish("DEBUG", msg);
}

void setup() {
  button.begin();
}

void updateActivePomodoro() {
  if(previousState != Active) {
    lastUpdate = millis();
  }

  unsigned long deltaTime = millis() - lastUpdate;
  if(deltaTime > pomodoroMillis) {
    debug("Completing pomodoro. deltaTime = %d", deltaTime);
    completePomodoro();
    return;
  }

  // calculate the amount of leds that should be lit.
  int percentageComplete = deltaTime / pomodoroMillis;
  int ledsToLight = numberOfButtons * percentageComplete;

  for(int i = 0; i <= ledsToLight; i++) {
    button.ledOn(i, 0, 255, 0);
  }
}

void completePomodoro() {
  previousState = pomodoroState;
  pomodoroState = Complete;

  for(int i = 0; i < numberOfButtons; i++) {
    button.ledOff(i);
  }
}

void loop() {
  if(button.buttonOn(1)) {
    button.allLedsOff();
    pomodoroState = Active;
  }
  if(button.buttonOn(2)) {
    // State = ShortBreak;
    pomodoroState = None;
  }
  if(button.buttonOn(3)) {
    pomodoroState = LongBreak;
  }
  if(button.buttonOn(4)) {
    pomodoroState = Cancelled;
  }

  if(pomodoroState == Active) {
    updateActivePomodoro();
    button.ledOn(6, 255, 0, 0);
  }

  if(pomodoroState == None) {
    button.allLedsOn(0, 0, 255);
  }
}
