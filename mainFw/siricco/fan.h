#ifndef FAN_H
#define FAN_H

#include <Arduino.h>
#include "config.h"

class Fan {
public:
  void begin() {
    // ESP32 core 3.x ke atas
    ledcAttach(PIN_FAN_PWM, FAN_PWM_FREQ, FAN_PWM_RES);
    ledcWrite(PIN_FAN_PWM, 0);
    current_speed = 0;
  }

  void setSpeed(uint8_t speed) {
    speed = constrain(speed, 0, 255);

    if (speed > 0 && speed < FAN_MIN_SPEED) {
      speed = FAN_MIN_SPEED;
    }

    ledcWrite(PIN_FAN_PWM, speed);
    current_speed = speed;
  }

  void off() {
    ledcWrite(PIN_FAN_PWM, 0);
    current_speed = 0;
  }

  uint8_t getSpeed() const {
    return current_speed;
  }

  bool isRunning() const {
    return current_speed >= FAN_MIN_SPEED;
  }

private:
  uint8_t current_speed;
};

#endif