#include "amp_bot.h"


void pressed2_state() {
    if (editState == 0) {
        digitalWrite(ledPin[0], LOW);
        digitalWrite(ledPin[1], LOW);
        digitalWrite(ledPin[2], HIGH);
        loadBtn3();
        moveServos();
      } 
      if (editState == 900) {
        switch (bank) { 
          case 1: state = 3;   break;
          case 2: state = 6;   break;
          case 3: state = 9;   break;
          case 4: state = 12;  break;
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
        if (DirectionGain == true) 
          DirectionGain = false; // Switch direction
        else
          DirectionGain = true; // Switch direction
      }
      pressed[2] = 0;
//Serial.println("btn3 click released");
}
