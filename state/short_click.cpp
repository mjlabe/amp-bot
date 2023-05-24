#include "metronome.cpp"
#include "short_0_state.cpp"
#include "short_1_state.cpp"
#include "short_2_state.cpp"


void handle_short_click() {
    if(pressed[0] == 1) {
      if (editState > 0 && editState < 770)
        editState++;
      short_0_state()
    }
    
// -------------------------------------------------------------------------------------- BUTTON2 SHORT CLICK
    if(pressed[1] == 1) {
      short_1_state()
    }    
// -------------------------------------------------------------------------------------- BUTTON3 SHORT CLICK
    if(pressed[2] == 1) {
      short_2_state()
    }
    if(pressed[2] == -3) {
     metronome();
     button[2].clicks = 0;  //will run twice without this line... BUG??
     pressed[2] = 0;  
   }
}