#include "amp_bot.h"


void handle_double_click() {
    // ------------------------------------------------------------------------------------- BUTTON1 DOUBLE CLICK
    if(pressed[0] == 2) {
      if (editState == 1) {
        editState = 700;
        ledsOff();
      }
      if (editState == 900) {
        state = oldState;
        ledStates();
        editState = 0;
      }
      pressed[0] = 0;
    }
// ------------------------------------------------------------------------------------- BUTTON2 DOUBLE CLICK
    if(pressed[1] == 2) {
      if (editState == 1) {
        editState = 750;
        ledsOff();
      }
       if (editState == 900) {
        state = oldState;
        ledStates();
        editState = 0;
      }
      pressed[1] = 0;
    }
// ------------------------------------------------------------------------------------- BUTTON3 DOUBLE CLICK
    if(pressed[2] == 2) {
}