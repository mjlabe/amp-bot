#include <EEPROM.h>
#include <VarSpeedServo.h>
#include <ClickButton.h>


// BUTTONs -------------------------------------------------------------------------------------------------- 
int function =                        0;
const int buttons =                   3;
const int buttonPin1 =                0;
const int buttonPin2 =                8;
const int buttonPin3 =               12;
ClickButton button[3] = {
  ClickButton (buttonPin1, LOW, CLICKBTN_PULLUP),
  ClickButton (buttonPin2, LOW, CLICKBTN_PULLUP),
  ClickButton (buttonPin3, LOW, CLICKBTN_PULLUP),
};
int pressed[buttons]  =     { 0, 0, 0 };

int longClickTime_default = 1720;  //longClickTime default

VarSpeedServo VolumeServo;
VarSpeedServo ShapeServo;
VarSpeedServo GainServo;
const int VolumePin =                 9;
const int ShapePin =                 10;
const int GainPin =                  11;
int masterOffset =                    0;
int shapeOffset =                     0;
int gainOffset =                      0;
int volume;
int shape;
int gain;
int gainBoost =                      27;
int volumeBoost =                    27;
int speedVolumeboost =                7;
int speedGainboost =                  7;
int lastVolume;
int lastShape;
int lastGain;
int volumeSpeed =                    27; // sweep speed, 1 is slowest, 255 fastest)
int shapeSpeed =                     27;
int gainSpeed =                      27;
int editSpeed =                     255;
int volumeMin =                       7; // range of the servos
int volumeMax =                     174;
int shapeMin =                        4;
int shapeMax =                      165;
int gainMin =                         7;
int gainMax =                       158;

// ----------------------------------------------------------------------------------------------------------
// READ BOOST VALUES
// ----------------------------------------------------------------------------------------------------------

volumeBoost = EEPROM.read(90);
speedVolumeboost = EEPROM.read(91);
gainBoost = EEPROM.read(92);
speedGainboost = EEPROM.read(93);
  


// INDICATOR LEVEL TO TRIGGER C1, C2 & C3 LEDs --------------------------------------------------------------
int volumeIndicator1 =               66;
int volumeIndicator2 =              127;
int volumeIndicator3 =              158;
int shapeIndicator1 =                99;
int shapeIndicator2 =               150;
int shapeIndicator3 =               161;
int gainIndicator1 =                 27;
int gainIndicator2 =                 88;
int gainIndicator3 =                127;
int servoSpeedsIndicator1 =          27;
int servoSpeedsIndicator2 =         127;
int servoSpeedsIndicator3 =         172;

// VARs -----------------------------------------------------------------------------------------------------
int DELAY =                          10;  // Delay per loop in ms
float easeFreemode =                 35;  // Free Mode Servospeed factor
int editState =                       0;
int bank =                            1;
int state =                           1;
int oldState =                        0;
int lastBtn =                         0;
int timer =                           0;
int blinker =                         0;
int tempo =                         400;  // tempo 400 will be arround 120 bpm
int canelDelay =                    400; // time until all servos will 
float y;                                   // get the value of the first in edit when switching to shapeSpeed
float x =                             1;
bool trigger =                 false;
bool DirectionVolume =          true;
bool DirectionShape =           true;
bool DirectionGain =            true;

// ----------------------------------------------------------------------------------------------------------
// READ BOOST VALUES
// ----------------------------------------------------------------------------------------------------------

volumeBoost = EEPROM.read(90);
speedVolumeboost = EEPROM.read(91);
gainBoost = EEPROM.read(92);
speedGainboost = EEPROM.read(93);

// LEDs -----------------------------------------------------------------------------------------------------
const int ledPin[buttons] = { 2, 4, 7 };    // Arduino pins to the LEDs
const int R_PIN =                     3;
const int G_PIN =                     5;
const int B_PIN =                     6;
int r;
int g;
int b;