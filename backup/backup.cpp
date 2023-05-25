#include "amp_bot.h"
#include "button.cpp"
#include "servo.cpp"


// ----------------------------------------------------------------------------------------------------------
// BACKUP PRESETS TO EEPROM (500++) AND SERIAL.PRINTLN
// ----------------------------------------------------------------------------------------------------------


  // ----------------------------------------------------------------------------------------------------------
  // INIT: WAIT FOR BACKUP/RESTORE CUE & BLINK BUTTONS
  // ----------------------------------------------------------------------------------------------------------

void wait_for_backup_restore() {
  for (int i=0; i<2; i++) {
    digitalWrite(ledPin[0], HIGH);
    digitalWrite(ledPin[1], HIGH);
    digitalWrite(ledPin[2], HIGH);
    delay (172);
    digitalWrite(ledPin[0], LOW);
    digitalWrite(ledPin[1], LOW);
    digitalWrite(ledPin[2], LOW);
    delay (172);
  }
  if (!digitalRead(buttonPin1))
    backupPresets();
  if (!digitalRead(buttonPin2) && !digitalRead(buttonPin3))
    restoreBackup();
  analogWrite(R_PIN, 0);
  analogWrite(G_PIN, 0);
  analogWrite(B_PIN, 0);

  servo_start_middle()

  servo_attach_position()
}

// ==========================================================================================================
// FUNCTIONS
// ==========================================================================================================

// ----------------------------------------------------------------------------------------------------------
// BACKUP PRESETS TO EEPROM (500++) AND SERIAL.PRINTLN
// ----------------------------------------------------------------------------------------------------------

void backupPresets() {
  pressed[0] = 0;
  editState = 997;
  Serial.println("Service Menu");
  blinkButton(ledPin[0]);
  blinkButton(ledPin[1]);
  blinkButton(ledPin[2]);
  Serial.println("Listing old backup (EEPROM 500 - 749):");
  Serial.print("[");
  for (int a=500; a<750; a++) {
    int zz = EEPROM.read(a);
    delay(5);
    Serial.print(zz);
    Serial.print(", ");
  }
  Serial.println("]");
  Serial.println();
  Serial.println("Creating backup (EEPROM 0 - 249 to 500 - 749):");
  Serial.print("[");
  for (int a=0; a<250; a++) {
    int zz = EEPROM.read(a);
    delay(5);
    Serial.print(zz);
    Serial.print(", ");
    EEPROM.write((a+500), zz);
  }
  Serial.println("]");
  editState = 0;
}

// ----------------------------------------------------------------------------------------------------------
// RESTORE BACKUP
// ----------------------------------------------------------------------------------------------------------

void restoreBackup() {
  pressed[1] = 0;
  pressed[2] = 0;
  editState = 997;
  Serial.println("Restoring backup (to EEPROM 0 - 249)");
  blinkButton(ledPin[2]);
  blinkButton(ledPin[1]);
  blinkButton(ledPin[0]);
  for (int a=500; a<750; a++) {
    int zz = EEPROM.read(a);
    delay(5);
    EEPROM.write((a-500), zz);
  }
  editState = 0;
}