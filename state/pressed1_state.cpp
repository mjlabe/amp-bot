#include "amp_bot.h"


void pressed1_state() {
    if (editState == 0) { 
        digitalWrite(ledPin[0], LOW);
        digitalWrite(ledPin[1], HIGH);
        digitalWrite(ledPin[2], LOW);
        loadBtn2();
        moveServos();
      }
      if (editState == 900) {
        switch (bank) {
          case 1: state = 2;    break;
          case 2: state = 5;    break;
          case 3: state = 8;    break;
          case 4: state = 11;   break;
        }         
        savePreset();
        ledStates();
        moveServos();  
        editState = 0;
        button[0].longClickTime  = longClickTime_default;
        button[1].longClickTime  = longClickTime_default;
        button[2].longClickTime  = longClickTime_default;
      }
      if (editState == 999) {
        if (DirectionShape == true)
          DirectionShape = false; // Switch direction
        else
          DirectionShape = true; // Switch direction
      }
      pressed[1] = 0;
//Serial.println("btn2 click released");
}