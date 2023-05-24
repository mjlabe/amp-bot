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

#include amp_bot.h
#include "button.cpp"
#include "servo.cpp"
#include "backup.cpp"
#include "short_click.cpp"
#include "long_click.cpp"
#include "state.cpp"
#include "handle_freemode"
#include "no_lag_bank_event.cpp"


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
  for (int i = 0; i < buttons; i++)
  {
    button[i].Update();
    if (button[i].clicks != 0) pressed[i] = button[i].clicks;

    handle_short_click()

    handle_long_click()

    handle_double_click()

    handle_triple_click()
  }

  handle_state()

  handle_freemode()

  handle_no_lag_bank_event()

// ----------------------------------------------- END OF LOOP  
  delay(DELAY);
}
