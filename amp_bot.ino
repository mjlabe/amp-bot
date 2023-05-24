/*
---------------------------------------
|       AMPBOT FIRMWARE v1.5       |                                                               05/2023
---------------------------------------

    AMPBOT Arduino knob controller.
    
    Forked from TERRORBOT FOR ORANGE DARK TERROR HEAD
     
    copyright Michael Karsay 2013 - 2016
    http://beam.to/terrorBot

-------------------------------------------------------------------------------------------------------------
*/

#include <EEPROM.h>
#include amp_bot.h
#include "button.cpp"
#include "servo.cpp"
#include "backup.cpp"
#include "metronome.cpp"


// ==========================================================================================================
// SETUP
// ==========================================================================================================

void setup() {
  Serial.begin(9600);
  for (int i=0; i<buttons; i++) {
    pinMode(ledPin[i],OUTPUT);  
    button[i].debounceTime   = 7;   // Debounce timer in ms
    button[i].multiclickTime = 250;  // Time limit for multi clicks
    button[i].longClickTime  = longClickTime_default; // Time until long clicks register
  }
  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);

  // ----------------------------------------------------------------------------------------------------------
  // INIT: WAIT FOR BACKUP/RESTORE, SET SERVO START POSITION
  // ----------------------------------------------------------------------------------------------------------

  wait_for_backup_restore()
  servo_start_middle()
  servo_attach_position()
}

// ----------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------ VOID LOOP
// ----------------------------------------------------------------------------------------------------------
void loop() {
// check button events
  for (int i=0; i<buttons; i++)
  {
    button[i].Update();
    if (button[i].clicks != 0) pressed[i] = button[i].clicks;
// -------------------------------------------------------------------------------------- BUTTON1 SHORT CLICK
    if(pressed[0] == 1) {
      if (editState > 0 && editState < 770)
        editState++;
// ---------------------------------------------------------------------------------------------- NORMAL MODE
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
// -------------------------------------------------------------------------------------- BUTTON2 SHORT CLICK
    if(pressed[1] == 1) {
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
// -------------------------------------------------------------------------------------- BUTTON3 SHORT CLICK
    if(pressed[2] == 1) {
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
    if(pressed[2] == -3) {
     metronome();
     button[2].clicks = 0;  //will run twice without this line... BUG??
     pressed[2] = 0;  
   }

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
      if (editState == 1) {
        editState = 760;
        ledsOff();
      }
      if (editState == 900) {
        state = oldState;
        ledStates();
        editState = 0;
      }
      pressed[2] = 0;
    }
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
// ----------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------- EDIT STATE 1
  if (editState == 1) { 
    volume = ease(volume,volumeMin, volumeMax, 27);   
    indicator(volume, volumeIndicator1, volumeIndicator2, volumeIndicator3);
    analogWrite(R_PIN, volume + volumeMin - 1);
    int v = volume + masterOffset;
    v = constrain(v, volumeMin, volumeMax);
    VolumeServo.slowmove(v,editSpeed);
//Serial.println(volume);
  }
// --------------------------------------------------------------------------------------------- EDIT STATE 2
  if (editState == 2) {
    shape = ease(shape, shapeMin, shapeMax, 27);   
    indicator(shape, shapeIndicator1, shapeIndicator2, shapeIndicator3);
    analogWrite(G_PIN, shape + shapeMin - 1);
    int s = shape + shapeOffset;
    s = constrain(s, shapeMin, shapeMax);
    ShapeServo.slowmove(s,editSpeed);
//Serial.println(shape);
  }
// --------------------------------------------------------------------------------------------- EDIT STATE 3
  if (editState == 3) {
    gain = ease(gain, gainMin, gainMax, 27);   
    indicator(gain, gainIndicator1, gainIndicator2, gainIndicator3);
    analogWrite(B_PIN, gain + gainMin - 1);
    GainServo.slowmove(gain,editSpeed);
    int g = gain + gainOffset;
    g = constrain(g, gainMin, gainMax);
    GainServo.slowmove(g,editSpeed);
//Serial.println(gain);
  }
// --------------------------------------------------------------------------------------------- EDIT STATE 4
  if (editState == 4) {
    volumeSpeed = ease(volumeSpeed, 1, 255, 21);   
    indicator(volumeSpeed, servoSpeedsIndicator1, servoSpeedsIndicator2, servoSpeedsIndicator3);
    analogWrite(R_PIN, volumeSpeed);
    analogWrite(G_PIN, 0);
    analogWrite(B_PIN, volumeSpeed);
  }
// --------------------------------------------------------------------------------------------- EDIT STATE 5
  if (editState == 5) {
    shapeSpeed = ease(shapeSpeed, 1, 255, 21);   
    indicator(shapeSpeed, servoSpeedsIndicator1, servoSpeedsIndicator2, servoSpeedsIndicator3);
    analogWrite(R_PIN, shapeSpeed/3);
    analogWrite(G_PIN, shapeSpeed);
    analogWrite(B_PIN, 0);
  }
// --------------------------------------------------------------------------------------------- EDIT STATE 6
  if (editState == 6) {
    gainSpeed = ease(gainSpeed, 1, 255, 21);   
    indicator(gainSpeed, servoSpeedsIndicator1, servoSpeedsIndicator2, servoSpeedsIndicator3);
    analogWrite(R_PIN, 0);
    analogWrite(B_PIN, gainSpeed);
    analogWrite(G_PIN, gainSpeed);
  }
// ------------------------------------------------------------------------------------------- EDIT STATE 700
  if (editState == 700) { 
    masterOffset = ease(masterOffset, -90, 90, 27);   
    offsetIndicator(masterOffset, R_PIN);
    int v = volume + masterOffset;
    v = constrain(v, volumeMin, volumeMax);
    VolumeServo.slowmove(v,editSpeed);
// Serial.println(masterOffset);
  }
// ------------------------------------------------------------------------------------------- EDIT STATE 701
  if (editState == 701) { 
    shapeOffset = ease(shapeOffset, -90, 90, 27);   
    offsetIndicator(shapeOffset, G_PIN);
    int s = shape + shapeOffset;
    s = constrain(s, shapeMin, shapeMax);
    ShapeServo.slowmove(s,editSpeed);
  }
// ------------------------------------------------------------------------------------------- EDIT STATE 702
  if (editState == 702) { 
    gainOffset = ease(gainOffset, -90, 90, 27);   
    offsetIndicator(gainOffset, B_PIN);
    int g = gain + gainOffset;
    g = constrain(g, gainMin, gainMax);
    GainServo.slowmove(g,editSpeed);
  }
// ---------------------------------------------------------------- SETUP BOOST VALUES - EDIT STATE 750 / 760
// ------------------------------------------------------------------------------------------- EDIT STATE 750
  if (editState == 750) {
    volumeBoost = ease(volumeBoost, 1, 255, 21);   
    indicator(volumeBoost, 5, 15, 30);
    analogWrite(R_PIN, volumeBoost + volumeMin - 1);
    analogWrite(G_PIN, 0);
    analogWrite(B_PIN, 0);
  }
// ------------------------------------------------------------------------------------------- EDIT STATE 751
  if (editState == 751) {
    speedVolumeboost = ease(speedVolumeboost, 1, 255, 21);   
    indicator(speedVolumeboost, servoSpeedsIndicator1, servoSpeedsIndicator2, servoSpeedsIndicator3);
    analogWrite(R_PIN, speedVolumeboost);
    analogWrite(G_PIN, speedVolumeboost);
    analogWrite(B_PIN, 0);
  }
// ------------------------------------------------------------------------------------------- EDIT STATE 760
  if (editState == 760) {
    gainBoost = ease(gainBoost, 1, 255, 21);   
    indicator(gainBoost, 5, 15, 30);
    analogWrite(R_PIN, 0);
    analogWrite(B_PIN, gainBoost + gainMin - 1);
    analogWrite(G_PIN, 0);
  }
// ------------------------------------------------------------------------------------------- EDIT STATE 761
  if (editState == 761) {
    speedGainboost = ease(speedGainboost, 1, 255, 21);   
    indicator(speedGainboost, servoSpeedsIndicator1, servoSpeedsIndicator2, servoSpeedsIndicator3);
    analogWrite(R_PIN, 0);
    analogWrite(B_PIN, speedGainboost);
    analogWrite(G_PIN, speedGainboost);
  }
// ----------------------------------------------------------------------------- EDIT STATE 900 - COPY PRESET
  if (editState == 900) {
    blinkAllButtons();
    delay(DELAY);
  }
// -------------------------------------------------------------------------------- EDIT STATE 999 - FREEMODE
  if (editState == 998)
    editState++;   // avoid tripple click to exit is also triggered
  if (editState == 999) {
    if (DirectionVolume == true)
      digitalWrite(ledPin[0], HIGH); 
    else  
      digitalWrite(ledPin[0], LOW); 
    if (DirectionShape == true)
      digitalWrite(ledPin[1], HIGH);   
    else  
      digitalWrite(ledPin[1], LOW); 
    if (DirectionGain == true)
      digitalWrite(ledPin[2], HIGH);   
    else  
      digitalWrite(ledPin[2], LOW); 
  }
// ----------------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------ ENTER FREEMODE OR METRONOME
/*   if (button[0].depressed == true && button[2].depressed == false){  // press left button first
     if (!digitalRead(buttonPin3))                                    // then right button
       freemode();
   }
*/
// ----------------------------------------------------------------------------------------------------------

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
// ----------------------------------------------- END OF LOOP  
  delay(DELAY);
}
