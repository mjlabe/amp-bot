#include <EEPROM.h>


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
