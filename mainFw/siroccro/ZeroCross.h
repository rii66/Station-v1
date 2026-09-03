#ifndef ZEROCROSS_H
#define ZEROCROSS_H

#include <Arduino.h>
#include "config.h"

class ZeroCross {
public:

  void begin() {
    pinMode(HEATER_PIN, OUTPUT);
    digitalWrite(HEATER_PIN, LOW);

    pinMode(AC_SYNC_PIN, INPUT_PULLUP);

    power = 0;
    cnt = 0;
    active = false;
    last_zc = 0;
  }

  // =========================================
  // Dipanggil dari Zero-Cross ISR
  //
  // PC817 + bridge:
  // 50 Hz AC -> sekitar 100 event/detik
  // 1 event = 1 half-cycle
  // =====================================
  void IRAM_ATTR onZeroCross() {

    // Catat bahwa zero-cross masih datang
    last_zc = micros();

    // 0% = heater OFF
    if (power == 0) {
      digitalWrite(HEATER_PIN, LOW);
      active = false;
      cnt = 0;
      return;
    }

    // Burst-fire
    //
    // power = 30
    // 30 half-cycle ON
    // 70 half-cycle OFF
    //
    if (cnt < power) {
      digitalWrite(HEATER_PIN, HIGH);
      active = true;
    }
    else {
      digitalWrite(HEATER_PIN, LOW);
      active = false;
    }

    cnt++;

    // Satu periode kontrol selesai
    if (cnt >= POWER_PERIOD) {
      cnt = 0;
    }
  }

  // =========================================================
  // Set power
  // =========================================================
  void setPower(uint8_t p) {

    power = constrain(
      p,
      0,
      HEATER_MAX_POWER
    );

    if (power == 0) {
      digitalWrite(HEATER_PIN, LOW);
      active = false;
      cnt = 0;
    }
  }

  // ========================================
  // Getter
  // ====================================
  uint8_t getPower() const {
    return power;
  }

  bool hasAC() const {
    return (micros() - last_zc) < 50000UL;
  }

  bool isActive() const {
    return active;
  }

private:

  volatile uint8_t power;
  volatile uint8_t cnt;
  volatile bool active;
  volatile uint32_t last_zc;
};

#endif