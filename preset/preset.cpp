#include "amp_bot.h"


// ----------------------------------------------------------------------------------------------------------
// EDIT PRESET
// ----------------------------------------------------------------------------------------------------------

void edit() {
  editState = 1;
  button[0].longClickTime  = 500;
  button[1].longClickTime  = 500;
  button[2].longClickTime  = 500;
  analogWrite(R_PIN, volume - volumeMin + 1);
  analogWrite(G_PIN, 0);
  analogWrite(B_PIN, 0); 
  indicator(volume, volumeIndicator1, volumeIndicator2, volumeIndicator3);
/*
Serial.print("--- Editing ");
Serial.print(state);
Serial.println(" ---");
Serial.print("Volume :");
*/
}

// ----------------------------------------------------------------------------------------------------------
// COPY PRESET
// ----------------------------------------------------------------------------------------------------------

void copyPreset() {
  editState = 900;
  timer = 0;
  blinker = 0;
  while (1) {
   if (!digitalRead(buttonPin1) || !digitalRead(buttonPin2) || !digitalRead(buttonPin3))
    break;
   timer++;
    if (timer == 400) {
      state = oldState;
      button[0].longClickTime  = longClickTime_default;
      button[1].longClickTime  = longClickTime_default;
      button[2].longClickTime  = longClickTime_default;
      editState = 0;
      ledStates();
      timer = 0;
      break;
    }
    blinkAllButtons();
    delay(DELAY*2);    
  }
}

// ----------------------------------------------------------------------------------------------------------
// RESTORE PRESET
// ----------------------------------------------------------------------------------------------------------

void restorePreset() {
  switch (lastBtn) {
    case 1:
      loadBtn1();
      break;
    case 2:
      loadBtn2();
      break;
    case 3:
      loadBtn3();
      break;
  }    
}

// ----------------------------------------------------------------------------------------------------------
// SAVE PRESET TO EEPROM
// ----------------------------------------------------------------------------------------------------------

void savePreset() {
  switch (state) {
    case 1:
      EEPROM.write(0, volume);
      EEPROM.write(1, shape);
      EEPROM.write(2, gain);
      EEPROM.write(200, volumeSpeed);
      EEPROM.write(201, shapeSpeed);
      EEPROM.write(202, gainSpeed);
      break;
    case 2:
      EEPROM.write(3, volume);
      EEPROM.write(4, shape);
      EEPROM.write(5, gain);
      EEPROM.write(203, volumeSpeed);
      EEPROM.write(204, shapeSpeed);
      EEPROM.write(205, gainSpeed);
      break;
    case 3:
      EEPROM.write(6, volume);
      EEPROM.write(7, shape);
      EEPROM.write(8, gain);
      EEPROM.write(206, volumeSpeed);
      EEPROM.write(207, shapeSpeed);
      EEPROM.write(208, gainSpeed);
      break;
    case 4:
      EEPROM.write(9, volume);
      EEPROM.write(10, shape);
      EEPROM.write(11, gain);
      EEPROM.write(209, volumeSpeed);
      EEPROM.write(210, shapeSpeed);
      EEPROM.write(211, gainSpeed);
      break;
    case 5:
      EEPROM.write(12, volume);
      EEPROM.write(13, shape);
      EEPROM.write(14, gain);
      EEPROM.write(212, volumeSpeed);
      EEPROM.write(213, shapeSpeed);
      EEPROM.write(214, gainSpeed);
      break;
    case 6:
      EEPROM.write(15, volume);
      EEPROM.write(16, shape);
      EEPROM.write(17, gain);
      EEPROM.write(215, volumeSpeed);
      EEPROM.write(216, shapeSpeed);
      EEPROM.write(217, gainSpeed);
      break;
    case 7:
      EEPROM.write(18, volume);
      EEPROM.write(19, shape);
      EEPROM.write(20, gain);
      EEPROM.write(218, volumeSpeed);
      EEPROM.write(219, shapeSpeed);
      EEPROM.write(220, gainSpeed);
      break;
    case 8:
      EEPROM.write(21, volume);
      EEPROM.write(22, shape);
      EEPROM.write(23, gain);
      EEPROM.write(221, volumeSpeed);
      EEPROM.write(222, shapeSpeed);
      EEPROM.write(223, gainSpeed);
      break;
    case 9:
      EEPROM.write(24, volume);
      EEPROM.write(25, shape);
      EEPROM.write(26, gain);
      EEPROM.write(224, volumeSpeed);
      EEPROM.write(225, shapeSpeed);
      EEPROM.write(226, gainSpeed);
      break;
    case 10:
      EEPROM.write(27, volume);
      EEPROM.write(28, shape);
      EEPROM.write(29, gain);
      EEPROM.write(227, volumeSpeed);
      EEPROM.write(228, shapeSpeed);
      EEPROM.write(229, gainSpeed);
      break;
    case 11:
      EEPROM.write(30, volume);
      EEPROM.write(31, shape);
      EEPROM.write(32, gain);
      EEPROM.write(230, volumeSpeed);
      EEPROM.write(231, shapeSpeed);
      EEPROM.write(232, gainSpeed);
      break;
    case 12:
      EEPROM.write(33, volume);
      EEPROM.write(34, shape);
      EEPROM.write(35, gain);
      EEPROM.write(233, volumeSpeed);
      EEPROM.write(234, shapeSpeed);
      EEPROM.write(235, gainSpeed);
      break;
  }
}