#include "amp_bot.h"

// ----------------------------------------------------------------------------------------------------------
// METRONOME
// ----------------------------------------------------------------------------------------------------------

int metronome() {
  editState = 998;
  ledsOff();
  int counter = 0;
  while(1){
    x++;
    if (x > 7) {
     trigger = true;
     x = 0; 
    } else
      trigger = false;    
    counter++;
    delay (1);
    if (counter < 101)
      analogWrite(G_PIN, 72);
    if (counter > 100)
      analogWrite(G_PIN, 0);
    if (counter > tempo && counter < (tempo+100))
      digitalWrite(ledPin[0], HIGH);
    if (counter > (tempo+100))
      digitalWrite(ledPin[0], LOW);
    if (counter > ((tempo*2)+100) && counter < ((tempo*2)+200))
      digitalWrite(ledPin[1], HIGH);
    if (counter > (tempo*2)+200)
      digitalWrite(ledPin[1], LOW);
    if (counter > (tempo*3)+200 && counter < ((tempo*3)+300))
      digitalWrite(ledPin[2], HIGH);
    if (counter > (tempo*3)+300)
      digitalWrite(ledPin[2], LOW);
    if (counter > (tempo*4)+300)
      counter = 0;
    if (!digitalRead(buttonPin1)) {
      break;
    }
    if (!digitalRead(buttonPin2)) {
      if (trigger == true)
        tempo++;
    }
    if (!digitalRead(buttonPin3)) {
      if (trigger == true) {
        tempo--;
        if (tempo < 0)
          tempo = 0;
      }
    }    
  }
  editState = 0;
  ledStates();
  delay(721);
}
