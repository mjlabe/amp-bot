#include "amp_bot.h"


void handle_no_lag_bank_event() {
// --------------------------------------------------------------------------------------------- NO LAG EVENT
// ------------------- ALLOW IMEDIATE BUTTON RESPONSE WHILE SWITCHING PRESETS FROM BTN3 TO BTN2 IN BANK 3 + 4 
  if (!digitalRead(buttonPin2)) {
    if (editState == 0 && bank > 2) {
      if (state == 9 || state == 12) {
        digitalWrite(ledPin[0], LOW);
        digitalWrite(ledPin[1], HIGH);
        digitalWrite(ledPin[2], LOW);
        loadBtn2();
        moveServos();
      }
    }
  }
// ------------------- ALLOW IMEDIATE BUTTON RESPONSE WHILE SWITCHING PRESETS FROM BTN2 TO BTN3 IN BANK 3 + 4 
  if (!digitalRead(buttonPin3)) {
    if (editState == 0 && bank > 2) {
      if (state == 8 || state == 11) {
        digitalWrite(ledPin[0], LOW);
        digitalWrite(ledPin[1], LOW);
        digitalWrite(ledPin[2], HIGH);
        loadBtn3();
        moveServos();
      }
    }
  }
}