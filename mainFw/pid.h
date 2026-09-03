#ifndef PID_H
#define PID_H

#include <Arduino.h>
#include "config.h"
#include "boost.h"

/* ===== PID INTERNAL VAR ===== */
extern float pidError;
extern float pidIntegral;
extern float pidDerivative;
extern float lastError;

/* ===== WEB SINKRON ===== */
extern int targetTemp;

/* ===== PID ===== */
int readTemp();
void detectTip();
void updatePID();

/* ===== SAFETY ===== */
void handleSafety();

#endif