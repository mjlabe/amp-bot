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
