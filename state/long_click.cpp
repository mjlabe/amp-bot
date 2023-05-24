#include "amp_bot.h"


void handle_long_click() {
    // --------------------------------------------------------------------------------------- BUTTON1 LONG CLICK
    if(pressed[0] == -1) {
      if (editState == 0)
        edit();
      if (editState > 1 && editState < 710 && editState != 700) {    //  ----- move back in editmode
        editState--;
        if (editState == 1)
          analogWrite(G_PIN, 0); 
        if (editState == 2) 
          analogWrite(B_PIN, 0); 
        if (editState == 3) {
          analogWrite(R_PIN, 0); 
          analogWrite(G_PIN, 0); 
        }
        if (editState == 4) 
          analogWrite(B_PIN, 0); 
        if (editState == 5) 
          analogWrite(R_PIN, 0);
        if (editState == 700)
          analogWrite(G_PIN, 0); 
        if (editState == 701) 
          analogWrite(B_PIN, 0); 
          
      }
// ------------------------------------------------------------------------------------------- CLICK AND HOLD
      if (editState == 999) {
        y = easeFreemode;
        x = 1;
        float d = easeFreemode;
        while(button[0].depressed == true){
          button[0].Update();
          y = y - x;
          d = easeFreemode - sqrt(x)/2;
          d = constrain (d, 1, easeFreemode);
          if (y < 0) {
            if (DirectionVolume) {
              volume++;
              delay(d);
            } else {
              volume--;
              delay(d);
            }
            x = x + sqrt(x)/3;
            y = easeFreemode;
          } 
          volume = constrain(volume, volumeMin, volumeMax);
   //       Serial.print("volume: ");
   //       Serial.println(volume);
          indicator(volume, volumeIndicator1, volumeIndicator2, volumeIndicator3);
          analogWrite(R_PIN, volume + volumeMin - 1);
          analogWrite(G_PIN, 0);
          analogWrite(B_PIN, 0);
          VolumeServo.slowmove(volume,editSpeed);
          ledsOff();
        }
      }     
   //   EEPROM.write(400, volume);
      pressed[0] = 0;
    }
// --------------------------------------------------------------------------------------- BUTTON2 LONG CLICK
    if(pressed[1] == -1) {
      if (editState == 0) {
        boostVolume();
      }
      if (editState == 900) {
        bank--;
        if (bank < 1)
          bank = 4;
        ledStates();
      }
// ------------------------------------------------------------------------------------------- CLICK AND HOLD
      if (editState == 999) {
        y = easeFreemode;
        x = 1;
        float d = easeFreemode;
        while(button[1].depressed == true){
          button[1].Update();
          y = y - x;
          d = (1.5 * easeFreemode) - sqrt(x);
          d = constrain (d, 1, (1.5 * easeFreemode));
          if (y < 0) {
            if (DirectionShape) {
              shape++;
              delay(d);
            } else {
              shape--;
              delay(d);
            }
            x = x + sqrt(x)/3;
            y = easeFreemode;
          } 
          shape = constrain(shape, shapeMin, shapeMax);
  //        Serial.print("shape: ");
  //        Serial.println(shape);
          indicator(shape, shapeIndicator1, shapeIndicator2, shapeIndicator3);
          analogWrite(G_PIN, shape + shapeMin - 1);
          analogWrite(R_PIN, 0);
          analogWrite(B_PIN, 0);
          ShapeServo.slowmove(shape,editSpeed);
          ledsOff();
        }
      }     
   //   EEPROM.write(401, shape);
      pressed[1] = 0;
    }
// -------------------------------------------------------------------------------- BUTTON2 DOUBLE LONG CLICK
    if(pressed[1] == -2) {
      if (editState == 0 || editState == 900) {
        bank--;
        if (bank < 1)
          bank = 4;
        ledStates();
      }
      pressed[1] = 0;  
    }    
// --------------------------------------------------------------------------------------- BUTTON3 LONG CLICK
    if(pressed[2] == -1) {
      if (editState == 0) {
        boostGain();
      } 
      if (editState == 900) {
        bank++;
        if (bank > 4)
          bank = 1;
        ledStates();
      } 
// ------------------------------------------------------------------------------------------- CLICK AND HOLD
      if (editState == 999) {
        y = easeFreemode;
        x = 1;
        float d = easeFreemode;
        while(button[2].depressed == true){
          button[2].Update();
          y = y - x;
          d = easeFreemode - sqrt(x)/2;
          d = constrain (d, 1, easeFreemode);
          if (y < 0) {
            if (DirectionGain) {
              gain++;
              delay(d);
            } else {
              gain--;
              delay(d);
            }
            x = x + sqrt(x)/3;
            y = easeFreemode;
          } 
          gain = constrain(gain, gainMin, gainMax);
    //      Serial.print("gain: ");
    //      Serial.println(gain);
          indicator(gain, gainIndicator1, gainIndicator2, gainIndicator3);
          analogWrite(B_PIN, gain + gainMin - 1);
          analogWrite(G_PIN, 0);
          analogWrite(R_PIN, 0);
          GainServo.slowmove(gain,editSpeed);
          ledsOff();
        }
      }     
   //   EEPROM.write(402, gain);
      pressed[2] = 0;
    }
// -------------------------------------------------------------------------------- BUTTON3 DOUBLE LONG CLICK
    if(pressed[2] == -2) {
      if (editState == 0 || editState == 900) {
        bank++;
        if (bank > 4)
          bank = 1;
        ledStates();
      }
      pressed[2] = 0;  
    }  
// ------------------------------------------------------------------------------------- BUTTON1 DOUBLE CLICK
}
