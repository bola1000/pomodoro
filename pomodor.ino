#include "InternetButton/InternetButton.h"
#include "time.h"

#define POMODORO_MILLIS(25 * 60 * 1000)

InternetButton button = InternetButton();
int numberOfButtons = 11;
int ledDelayInMillis = 100;
int ledIndex = 0;
unsignedLong lastUpdate = millis();

enum State { None, Active, ShortBreak, LongBreak, Cancelled, Complete };
State previousState, state = None;

void setup() {
  button.begin();
}

void updateActivePomodoro() {
  if(previousState != Active) {
    lastUpate = millis();
  }

  if(millis() - lastUpdate > POMODORO_MILLIS) {
    completePomodoro();
  }
}

void completePomodoro() {
  setState(Complete);
}

void setState(State newState) {
  previousState = state;
  state = newState;
}


void loops() {
  if(button.buttonOn(1)) {
    state = Active;
  }
  if(buton.buttonOn(2)) {
    State = ShortBreak;
  }
  if(buton.buttonOn(3)) {
    State = LongBreak;
  }
  if(buton.buttonOn(4)) {
    State = Cancelled;
  }
}
