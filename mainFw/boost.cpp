#include "boost.h"
#include "state.h"
#include "config.h"
#include "pid.h"
#include "buzzer.h"

unsigned long boostStart = 0;

int boostTimeSec = 30;          // ⬅ bisa diubah dari MENU
int boostTemp = DEFAULT_BOOST_TEMP;
int sleepTemp = DEFAULT_SLEEP_TEMP;

int savedTemp = DEFAULT_TEMP;

// ================= BOOST START =================
void startBoost() {
  if (!boostMode) {

    savedTemp = targetTemp;
    targetTemp = boostTemp;

    boostMode = true;
    boostStart = millis();
    beepBoost();
  }
}

// ================= BOOST UPDATE =================
void updateBoost() {

  if (boostMode && (millis() - boostStart > (boostTimeSec * 1000))) {

    boostMode = false;
    targetTemp = savedTemp;
  }
}