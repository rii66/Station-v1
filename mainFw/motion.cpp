#include "motion.h"
#include "config.h"
#include "state.h"
#include "pid.h"
#include "tip.h"
#include "encoder.h"
#include "buzzer.h"

void initMotion() {
  pinMode(MOTION_PIN, INPUT_PULLUP);
}
// Motion //
void wakeFromSleep() {
  motionDetected = true;
  lastMotion = millis();

  if (sleeping) {
    sleeping = false;
    beepWake();
  }
}

void updateMotion() {
  bool motion = digitalRead(MOTION_PIN);

  /* Bangun Universal*/
  if (motion == LOW) {
    wakeFromSleep();
  }

  /* AUTO SLEEP */
  if (
    sleepTimer > 0 &&
    millis() - lastMotion > sleepTimer
  ) {
    if (!sleeping) {
      sleeping = true;

      beepSleep();  // sleep beep
    }
  }
}