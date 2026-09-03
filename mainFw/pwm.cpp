#include <Arduino.h>
#include "config.h"
#include "state.h"
#include "pwm.h"

void initPWM() {
    ledcAttach(PWM_PIN, PWM_FREQ, PWM_RES);
    heaterOff();
}

void heaterOff() {
    ledcWrite(PWM_PIN, 0);
}

void heaterOn() {
    ledcWrite(PWM_PIN, pwmOut);
}

void setPWM(int pwm) {

    if (pwm < 0)
        pwm = 0;

    pwmOut = pwm;

    ledcWrite(PWM_PIN, pwmOut);
}

void startTempRead() {
    heaterOff();
    delayMicroseconds(200);
}

void endTempRead() {
    heaterOn();
}