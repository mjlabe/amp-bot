//
// Created by Marc LaBelle on 5/25/23.
//

#ifndef AMP_BOT_BACKUP_HPP
#define AMP_BOT_BACKUP_HPP

#include <Arduino.h>

void wait_for_backup_restore();
void backupPresets();
void restoreBackup();

#endif //AMP_BOT_BACKUP_HPP
