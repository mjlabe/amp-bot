#include "amp_bot.h"


void handle_state() {
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
}