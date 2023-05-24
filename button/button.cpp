#include <EEPROM.h>
#include "button.h"


// ----------------------------------------------------------------------------------------------------------
// FREEMODE
// ----------------------------------------------------------------------------------------------------------

int freemode() {
  ledsOff();
  blinkButton(B_PIN);
  delay(200);
  blinkButton(B_PIN);
  editState = 998;   // avoid tripple click to exit is also triggered
  button[0].longClickTime  = 271;
  button[1].longClickTime  = 271;
  button[2].longClickTime  = 271;
}

// ----------------------------------------------------------------------------------------------------------
// LOAD PRESET IF BUTTON1 WAS PRESSED
// ----------------------------------------------------------------------------------------------------------

int loadBtn1() {
  switch (bank) {
    case 1:
      volume = EEPROM.read(0);
      shape  = EEPROM.read(1);
      gain = EEPROM.read(2);
      volumeSpeed = EEPROM.read(200);
      shapeSpeed = EEPROM.read(201);
      gainSpeed = EEPROM.read(202);
      state = 1;
      break;
    case 2:
      volume = EEPROM.read(9);
      shape  = EEPROM.read(10);
      gain = EEPROM.read(11);
      volumeSpeed = EEPROM.read(209);
      shapeSpeed = EEPROM.read(210);
      gainSpeed = EEPROM.read(211);
      state = 4;
      break;
    case 3:
      volume = EEPROM.read(18);
      shape  = EEPROM.read(19);
      gain = EEPROM.read(20);
      volumeSpeed = EEPROM.read(218);
      shapeSpeed = EEPROM.read(219);
      gainSpeed = EEPROM.read(220);
      state = 7;
      break;
    case 4:
      volume = EEPROM.read(27);
      shape  = EEPROM.read(28);
      gain = EEPROM.read(29);
      volumeSpeed = EEPROM.read(227);
      shapeSpeed = EEPROM.read(228);
      gainSpeed = EEPROM.read(229);
      state = 10;
      break;
  } 
}

// ----------------------------------------------------------------------------------------------------------
// LOAD PRESET IF BUTTON2 WAS PRESSED
// ----------------------------------------------------------------------------------------------------------

int loadBtn2() {  
  switch (bank) {
    case 1:
      volume = EEPROM.read(3);
      shape  = EEPROM.read(4);
      gain = EEPROM.read(5);
      volumeSpeed = EEPROM.read(203);
      shapeSpeed = EEPROM.read(204);
      gainSpeed = EEPROM.read(205);
      state = 2;
      break;
    case 2:
      volume = EEPROM.read(12);
      shape  = EEPROM.read(13);
      gain = EEPROM.read(14);
      volumeSpeed = EEPROM.read(212);
      shapeSpeed = EEPROM.read(213);
      gainSpeed = EEPROM.read(214);
      state = 5;
      break;
    case 3:
      volume = EEPROM.read(21);
      shape  = EEPROM.read(22);
      gain = EEPROM.read(23);
      volumeSpeed = EEPROM.read(221);
      shapeSpeed = EEPROM.read(222);
      gainSpeed = EEPROM.read(223);
      state = 8;
      break;
    case 4:
      volume = EEPROM.read(30);
      shape  = EEPROM.read(31);
      gain = EEPROM.read(32);
      volumeSpeed = EEPROM.read(230);
      shapeSpeed = EEPROM.read(231);
      gainSpeed = EEPROM.read(232);
      state = 11;
      break;
  }
}
// ----------------------------------------------------------------------------------------------------------
// LOAD PRESET IF BUTTON3 WAS PRESSED
// ----------------------------------------------------------------------------------------------------------

int loadBtn3() {        
  switch (bank) {
    case 1:
      volume = EEPROM.read(6);
      shape  = EEPROM.read(7);
      gain = EEPROM.read(8);
      volumeSpeed = EEPROM.read(206);
      shapeSpeed = EEPROM.read(207);
      gainSpeed = EEPROM.read(208);
      state = 3;
      break;
    case 2:
      volume = EEPROM.read(15);
      shape  = EEPROM.read(16);
      gain = EEPROM.read(17);
      volumeSpeed = EEPROM.read(215);
      shapeSpeed = EEPROM.read(216);
      gainSpeed = EEPROM.read(217);
      state = 6;
      break;
    case 3:
      volume = EEPROM.read(24);
      shape  = EEPROM.read(25);
      gain = EEPROM.read(26);
      volumeSpeed = EEPROM.read(224);
      shapeSpeed = EEPROM.read(225);
      gainSpeed = EEPROM.read(226);
      state = 9;
      break;
    case 4:
      volume = EEPROM.read(33);
      shape  = EEPROM.read(34);
      gain = EEPROM.read(35);
      volumeSpeed = EEPROM.read(233);
      shapeSpeed = EEPROM.read(234);
      gainSpeed = EEPROM.read(235);
      state = 12;
      break;
  }
}
