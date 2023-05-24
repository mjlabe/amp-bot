#include "amp_bot.h"


void handle_triple_click() {
    // ------------------------------------------------------------------------------------ BUTTON1 TRIPPLE CLICK
    if(pressed[0] == 3) {
      if (editState == 0) {
        lastBtn = 1;
        loadBtn1();
        moveServos(); 
        freemode();
      }
      if (editState >0 && editState < 100) {
        editState = 0;
        ledStates();
        button[0].longClickTime  = longClickTime_default;
        button[1].longClickTime  = longClickTime_default;
        button[2].longClickTime  = longClickTime_default;
      }
      if (editState == 999) {
        ledsOff();
        savePreset();
        delay(500);
        editState = 0;
        ledStates();
        moveServos();
        button[0].longClickTime  = longClickTime_default;
        button[1].longClickTime  = longClickTime_default;
        button[2].longClickTime  = longClickTime_default;
        DirectionVolume = true;
        DirectionShape = true;
        DirectionGain = true;
      }
      pressed[0] = 0;
    }
// ------------------------------------------------------------------------------------ BUTTON2 TRIPPLE CLICK
    if(pressed[1] == 3) {
      if (editState == 0) {
        lastBtn = 2;
        loadBtn2();
        moveServos();
        freemode();            
      }
      if (editState == 999) {
        ledsOff();
        editState = 0;
        restorePreset();
        ledStates();
        moveServos();
        button[0].longClickTime  = longClickTime_default;
        button[1].longClickTime  = longClickTime_default;
        button[2].longClickTime  = longClickTime_default;
        DirectionVolume = true;
        DirectionShape = true;
        DirectionGain = true;
      }
      pressed[1] = 0;
    }
// ------------------------------------------------------------------------------------ BUTTON3 TRIPPLE CLICK
    if(pressed[2] == 3) {
      if (editState == 0) {
        lastBtn = 3;
        loadBtn3();
        moveServos();
        freemode();
      }
      if (editState == 1) {
        oldState = state;
        copyPreset();
      }
      if (editState == 999) {
        ledsOff();
        editState = 0;
        restorePreset();
        ledStates();
        moveServos();
        button[0].longClickTime  = longClickTime_default;
        button[1].longClickTime  = longClickTime_default;
        button[2].longClickTime  = longClickTime_default;
        DirectionVolume = true;
        DirectionShape = true;
        DirectionGain = true;
      }
      pressed[2] = 0;
    }
//-------    
}