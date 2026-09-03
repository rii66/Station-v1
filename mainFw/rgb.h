#ifndef RGB_H
#define RGB_H

#include <Arduino.h>
#include "state.h"

/* ===== PIN RGB ===== */
#define RGB_RED   9   
#define RGB_BLUE  10

/* ===== FUNCTION ===== */
void initRGB();
void updateRGB();
void setRGB(uint8_t r, uint8_t b);

#endif