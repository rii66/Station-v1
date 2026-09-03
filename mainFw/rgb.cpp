#include "rgb.h"
#include "pid.h"
#include "state.h"

static bool blinkState = false;
static unsigned long lastBlink = 0;

/* ===== INIT ===== */
void initRGB() {
  pinMode(RGB_RED, OUTPUT);
  pinMode(RGB_BLUE, OUTPUT);

  digitalWrite(RGB_RED, HIGH);
  digitalWrite(RGB_BLUE, HIGH);
}

/* ===== COMMON ANODE PWM ===== */
void setRGB(uint8_t r, uint8_t b) {
  analogWrite(RGB_RED, 255 - r);
  analogWrite(RGB_BLUE, 255 - b);
}

/* ===== UPDATE RGB STATE ===== */
void updateRGB() {
  
  /* ===== BOOTING ===== */
  if (booting) {
    int v = (millis() / 10) % 255;
    setRGB(v, 255 - v);
    return;
  }

  /* ===== SLEEP = PINK ===== */
  if (sleeping) {
    setRGB(255, 120);
    return;
  }

  /* ===== BOOST = PURPLE BLINK ===== */
  if (boostMode) {
    if (millis() - lastBlink > 250) {
      blinkState = !blinkState;
      lastBlink = millis();
    }

    if (blinkState) setRGB(180, 255);
    else setRGB(0, 0);

    return;
  }

  /* ===== OVER TEMP ===== */
  if (currentTemp > targetTemp + 15) {
    if (millis() - lastBlink > 120) {
      blinkState = !blinkState;
      lastBlink = millis();
    }

    if (blinkState) setRGB(255, 0);
    else setRGB(0, 0);

    return;
  }

  /* ===== HEATING ===== */
  if (currentTemp < targetTemp - 5) {
    int intensity = map(currentTemp, 0, targetTemp, 50, 255);
    setRGB(intensity, 0);
    return;
  }
  
  /* ===== COOLING ===== */
  if (currentTemp > targetTemp + 5) {
    
    int intensity = map(currentTemp, 255, targetTemp, 50, 255);
    
    setRGB(27, 204); 
    return;
  }

  /* ===== READY ===== */
  if (abs(currentTemp - targetTemp) <= 8) {
    setRGB(0, 255);
    return;
  }
  
  /* ==== Control Web ====*/
  if (webControl) {
    setRGB(0,180);
    return;
  }

  /* ===== IDLE ===== */
  setRGB(8, 2);
}