#ifndef STORAGE_H
#define STORAGE_H

#include "tip.h"

void applyTipProfile(TipConfig *targetTip);

void initStorage();
void loadSettings();
void saveSettings();
void saveActivePID();
void saveBoost();
void saveSleep();
void saveCal();
void saveTip();
void savePID();
void saveBuzzer();

void factoryReset();

#endif