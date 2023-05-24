#include <VarSpeedServo.h>


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
  