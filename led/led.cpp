#include "led.h"



// ----------------------------------------------------------------------------------------------------------
// BLINK BUTTON LED
// ----------------------------------------------------------------------------------------------------------

int blinkButton(int pin) {
  if (digitalRead(pin)) {
    digitalWrite(pin, LOW);
    delay (100);
    digitalWrite(pin, HIGH);
    delay (100);
  } else {
    digitalWrite(pin, HIGH);
    delay (100);
    digitalWrite(pin, LOW);
    delay (100);
  }         
}

// ----------------------------------------------------------------------------------------------------------
// BLINK ALL BUTTON LEDs
// ----------------------------------------------------------------------------------------------------------

int blinkAllButtons() {
  blinker++;
  if (blinker > 80)
    blinker = 0;
  if (blinker > 40 && blinker < 80) {
    digitalWrite(ledPin[0], LOW);
    digitalWrite(ledPin[1], LOW);
    digitalWrite(ledPin[2], LOW); 
  } else {
    digitalWrite(ledPin[0], HIGH);
    digitalWrite(ledPin[1], HIGH);
    digitalWrite(ledPin[2], HIGH); 
  }    
}

// ----------------------------------------------------------------------------------------------------------
// ALL LEDs OFF
// ----------------------------------------------------------------------------------------------------------

int ledsOff() {
  digitalWrite(ledPin[0], LOW);
  digitalWrite(ledPin[1], LOW);
  digitalWrite(ledPin[2], LOW); 
  analogWrite(R_PIN, 0);
  analogWrite(G_PIN, 0);
  analogWrite(B_PIN, 0);
}  

// ----------------------------------------------------------------------------------------------------------
// SET VALUE-INDICATOR LEDs
// ----------------------------------------------------------------------------------------------------------

int indicator(int which, int marker1, int marker2, int marker3) {
  digitalWrite(ledPin[0], LOW);
  digitalWrite(ledPin[1], LOW);
  digitalWrite(ledPin[2], LOW); 
  if (which > marker1)
    digitalWrite(ledPin[0], HIGH);
  else 
    digitalWrite(ledPin[0], LOW);
  if (which > marker2)
    digitalWrite(ledPin[1], HIGH);
  else 
    digitalWrite(ledPin[1], LOW);
  if (which > marker3)
    digitalWrite(ledPin[2], HIGH);
  else 
    digitalWrite(ledPin[2], LOW);
}

int offsetIndicator(int which, int ledpin) {
  if (which < 0) {
    digitalWrite(ledPin[0], HIGH);
    digitalWrite(ledPin[1], HIGH);
    digitalWrite(ledPin[2], LOW);
    analogWrite(ledpin, which * -2.833333);
  }
  if (which == 0) {
    digitalWrite(ledPin[0], HIGH);
    digitalWrite(ledPin[1], HIGH);
    digitalWrite(ledPin[2], HIGH);
    blinker++;
    if (blinker > 80)
      blinker = 0;
    if (blinker > 40 && blinker < 80)
      analogWrite(ledpin, 0); 
    else 
      analogWrite(ledpin, 50);
  }
  if (which > 0) {
    digitalWrite(ledPin[0], LOW);
    digitalWrite(ledPin[1], HIGH);
    digitalWrite(ledPin[2], HIGH);
    analogWrite(ledpin, which * 2.833333);
  }  
}

// ----------------------------------------------------------------------------------------------------------
// CHECK WHAT STATE IS SELECTED AND LIGHT THE RIGHT LEDs
// ----------------------------------------------------------------------------------------------------------

int ledStates() {
  delay (2);
  digitalWrite(ledPin[0], LOW);
  digitalWrite(ledPin[1], LOW);
  digitalWrite(ledPin[2], LOW);
  switch (state) {
    case 1:
      if (bank == 1) 
        digitalWrite(ledPin[0], HIGH);
      else
        digitalWrite(ledPin[0], LOW);
      break;
    case 2:
      if (bank == 1) 
        digitalWrite(ledPin[1], HIGH);
      else
        digitalWrite(ledPin[1], LOW);
      break;
    case 3:
      if (bank == 1) 
        digitalWrite(ledPin[2], HIGH);
      else
        digitalWrite(ledPin[2], LOW);
      break;
    case 4:
      if (bank == 2) 
        digitalWrite(ledPin[0], HIGH);
      else
        digitalWrite(ledPin[0], LOW);
      break;
    case 5:
      if (bank == 2) 
        digitalWrite(ledPin[1], HIGH);
      else
        digitalWrite(ledPin[1], LOW);
      break;
    case 6:
      if (bank == 2) 
        digitalWrite(ledPin[2], HIGH);
      else
        digitalWrite(ledPin[2], LOW);
      break;
    case 7:
      if (bank == 3) 
        digitalWrite(ledPin[0], HIGH);
      else
        digitalWrite(ledPin[0], LOW);
      break;
    case 8:
      if (bank == 3) 
        digitalWrite(ledPin[1], HIGH);
      else
        digitalWrite(ledPin[1], LOW);
      break;
    case 9:
      if (bank == 3) 
        digitalWrite(ledPin[2], HIGH);
      else
        digitalWrite(ledPin[2], LOW);
      break;
    case 10:
      if (bank == 4) 
        digitalWrite(ledPin[0], HIGH);
      else
        digitalWrite(ledPin[0], LOW);
      break;
    case 11:
      if (bank == 4) 
        digitalWrite(ledPin[1], HIGH);
      else
        digitalWrite(ledPin[1], LOW);
      break;
    case 12:
      if (bank == 4) 
        digitalWrite(ledPin[2], HIGH);
      else
        digitalWrite(ledPin[2], LOW);
      break;
  }  
  switch (bank) {
    case 1: r = 0;   g = 0;   b = 0;   break;
    case 2: r = 0;   g = 10;  b = 0;   break;
    case 3: r = 0;   g = 0;   b = 20;  break;
    case 4: r = 10;  g = 10;  b = 10;  break;
  }
  analogWrite(R_PIN, r);
  analogWrite(G_PIN, g);
  analogWrite(B_PIN, b);
}
