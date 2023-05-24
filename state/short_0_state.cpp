#include "amp_bot.h"


void short_0_state() {
  if (editState == 0) {
      digitalWrite(ledPin[0], HIGH);
      digitalWrite(ledPin[1], LOW);
      digitalWrite(ledPin[2], LOW);
      loadBtn1();
      moveServos();
    }
/*
Serial.print("----- ");
Serial.print(state);
Serial.println(" -----");
Serial.print("Volume :");
Serial.println(volume);
Serial.print("Shape :");
Serial.println(shape);
Serial.print("Gain :");
Serial.println(gain);
Serial.print("Volume Speed :");
Serial.println(volumeSpeed);
Serial.print("Shape Speed :");
Serial.println(shapeSpeed);
Serial.print("Gain Speed :");
Serial.println(gainSpeed);
*/
// ------------------------------------------------------------------------------------------------ EDIT MODE
    if (editState == 2) {
      analogWrite(R_PIN, 0);
      analogWrite(G_PIN, shape - shapeMin + 1);
      indicator(shape, shapeIndicator1, shapeIndicator2, shapeIndicator3);
// Serial.print("Shape :");
    }
    if (editState == 3) {
      analogWrite(G_PIN, 0);
      analogWrite(B_PIN, gain - gainMin + 1);
      indicator(gain, gainIndicator1, gainIndicator2, gainIndicator3);
// Serial.println("Gain :");
    }
    if (editState == 4) {
      analogWrite(R_PIN, volumeSpeed);
      analogWrite(G_PIN, 0);
      analogWrite(B_PIN, volumeSpeed);
      indicator(volumeSpeed, servoSpeedsIndicator1, servoSpeedsIndicator2, servoSpeedsIndicator3);
// Serial.print("Volume Speed :");
    }
    if (editState == 5) {
// Serial.println("Shape Speed :");
      analogWrite(R_PIN, shapeSpeed/3);
      analogWrite(G_PIN, shapeSpeed);
      analogWrite(B_PIN, 0);
      indicator(shapeSpeed, servoSpeedsIndicator1, servoSpeedsIndicator2, servoSpeedsIndicator3);
      timer = 0;
      while(1){
        pressed[0] = 0;
        timer++;
        delay(10);
        if (!digitalRead(buttonPin2) || !digitalRead(buttonPin3))
          break;
        button[0].Update();
        if (button[0].clicks != 0) pressed[0] = button[0].clicks;
        if (pressed[0] == 1) {
          editState = 6;
          pressed[0] = 0;
          break;
        }
        if (pressed[0] == -1) {
          editState = 4;
          pressed[0] = 0;
          break;
        }
        if (timer > canelDelay*0.80) {
          digitalWrite(ledPin[0], HIGH);         
          digitalWrite(ledPin[1], LOW);         
          digitalWrite(ledPin[2], HIGH);         
        }
        if (timer > canelDelay*0.825) {
          digitalWrite(ledPin[0], LOW);         
          digitalWrite(ledPin[1], HIGH);         
          digitalWrite(ledPin[2], LOW);         
        }
        if (timer > canelDelay*0.85) {
          digitalWrite(ledPin[0], HIGH);         
          digitalWrite(ledPin[1], LOW);         
          digitalWrite(ledPin[2], HIGH);         
        }
        if (timer > canelDelay*0.875) {
          digitalWrite(ledPin[0], LOW);         
          digitalWrite(ledPin[1], LOW);         
          digitalWrite(ledPin[2], LOW);         
        }
        if (timer > canelDelay) {
          shapeSpeed = volumeSpeed;
          gainSpeed = volumeSpeed;
          editState = 7;
          break;
        }
        
      }
      timer = 0;
    }
    if (editState == 6) {
      analogWrite(R_PIN, 0);
      analogWrite(G_PIN, gainSpeed);
      analogWrite(B_PIN, gainSpeed);
      indicator(gainSpeed, servoSpeedsIndicator1, servoSpeedsIndicator2, servoSpeedsIndicator3);
// Serial.print("Gain Speed :");
    }
    if (editState == 7) {
      analogWrite(R_PIN, 0);
      analogWrite(G_PIN, 0);
      analogWrite(B_PIN, 0);
      savePreset();
      editState = 0;
      ledStates();
      moveServos();
      button[0].longClickTime  = longClickTime_default;
      button[1].longClickTime  = longClickTime_default;
      button[2].longClickTime  = longClickTime_default;
      pressed [0] = 0;
      // break;
    }
    if (editState == 701) {
      if (masterOffset < 0) {
        EEPROM.write(94, 0);
        int m = -masterOffset;
        EEPROM.write(95, m);
      } else {
        EEPROM.write(94, 1);
        int m = masterOffset;
        EEPROM.write(95, m);
      }
      ledsOff();
    }
    if (editState == 702) {
      if (shapeOffset < 0) {
        EEPROM.write(96, 0);
        int s = -shapeOffset;
        EEPROM.write(97, s);
      } else {
        EEPROM.write(96, 1);
        int s = shapeOffset;
        EEPROM.write(97, s);
      }        
      ledsOff();
    }
    if (editState == 703) {
      if (gainOffset < 0) {
        EEPROM.write(98, 0);
      } else {
        EEPROM.write(98, 1);
        int g = gainOffset;
        EEPROM.write(99, g);
      }
      button[0].longClickTime  = longClickTime_default;
      button[1].longClickTime  = longClickTime_default;
      button[2].longClickTime  = longClickTime_default;
      editState = 0;
      ledStates();
      moveServos();
    }
    if (editState == 751) {
      EEPROM.write(90, volumeBoost);
      ledsOff();
    }
    if (editState == 752) {
      EEPROM.write(91, speedVolumeboost);
      editState = 0;
      ledStates();
      button[0].longClickTime  = longClickTime_default;
      button[1].longClickTime  = longClickTime_default;
      button[2].longClickTime  = longClickTime_default;
    }
    if (editState == 761) {
      EEPROM.write(92, gainBoost);
      ledsOff();
    }
    if (editState == 762) {
      EEPROM.write(93, speedGainboost);
      editState = 0;
      ledStates();
      button[0].longClickTime  = longClickTime_default;
      button[1].longClickTime  = longClickTime_default;
      button[2].longClickTime  = longClickTime_default;
    }
    if (editState == 900) {
      switch (bank) {
        case 1: state = 1;   break;
        case 2: state = 4;   break;
        case 3: state = 7;   break;
        case 4: state = 10;  break;
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
      if (DirectionVolume == true)
        DirectionVolume = false; // Switch direction
      else
        DirectionVolume = true; // Switch direction
    }
    pressed[0] = 0;
//Serial.println("btn1 click released");
}