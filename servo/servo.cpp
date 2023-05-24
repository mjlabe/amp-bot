// SERVOs ---------------------------------------------------------------------------------------------------
#include "servo.h"


void servo_start_middle() {
      // ----------------------------------------------------------------------------------------------------------
  // SERVOS RUSHES TO MIDDLE POSITION FIX
  // ----------------------------------------------------------------------------------------------------------

  volume = EEPROM.read(0);    // 400++ for last position --> eeprom killer
  shape  = EEPROM.read(1);
  gain =   EEPROM.read(2);
  int m =  EEPROM.read(94);
  int mO = EEPROM.read(95);
  if (m == 1)
    masterOffset = mO;
  else
    masterOffset = -mO;    
  int s = EEPROM.read(96);
  int sO = EEPROM.read(97);
  if (s == 1)
    shapeOffset = sO;
  else
    shapeOffset = -sO;    
  int g = EEPROM.read(98);
  int gO = EEPROM.read(99);
  if (g == 1)
    gainOffset = gO;
  else
    gainOffset = -gO;    
  lastVolume = ((volume * 10) + 600);
  lastShape = ((shape * 10) + 600);
  lastGain = ((gain * 10) + 600);
  lastVolume = constrain(lastVolume, 600, 2180);  // limit to range of servos in ms
  lastShape = constrain(lastShape, 600, 2180);
  lastGain = constrain(lastGain, 600, 2180);
}

void servo_attach_position() {
  // ----------------------------------------------------------------------------------------------------------
  // SERVO ATTACH POSITION
  // ----------------------------------------------------------------------------------------------------------

  VolumeServo.writeMicroseconds(lastVolume);      
  ShapeServo.writeMicroseconds(lastShape);       
  GainServo.writeMicroseconds(lastGain);    
  VolumeServo.attach(VolumePin);
  ShapeServo.attach(ShapePin);
  GainServo.attach(GainPin);
  delay(DELAY);
  VolumeServo.slowmove(90,volumeSpeed);  // middle position
  ShapeServo.slowmove(shapeMax,shapeSpeed);  // end position
  GainServo.slowmove(gainMin,gainSpeed);     // start position
}