#ifndef STATE_H
#define STATE_H

#include <Arduino.h>
#include "tip.h"

// ================= STATUS & STATE MAHCINE =================
extern uint8_t heaterState;

#define STATE_IDLE  0
#define STATE_HEAT  1
#define STATE_HOLD  2
#define STATE_SLEEP 3
#define STATE_BOOST 4
#define STATE_OVRHT 5
#define STATE_TIP   6

// ================= UI CORE =================
extern int item;
extern int page;
extern bool inMenu;
extern bool inEdit;
extern bool menuClick;
extern bool booting;
extern uint8_t pidStage;

extern bool isEditingValue;

// ================= SYSTEM FLAGS =================
extern bool sleeping;
extern bool boostMode;
extern bool manualPWMMode;
extern bool buzzerEnabled;
extern bool webControl;
extern bool motionDetected;
extern bool btnHolding;

// ================= SAFETY & LIMITS (Baru Ditambahkan) =================
extern int maxPwmLimit;
extern bool tipError;
extern bool overHeat;

// ================= TIP =================
extern TipID currentTip;
extern uint8_t currentTipMode;
//extern bool tipType;
//extern bool tipMode;

// ================= BOOST =================
extern int boostTemp;
extern unsigned long boostStartTime;

// ================= SLEEP =================
extern int sleepTemp;
extern int sleepTimeSec;
extern unsigned long sleepTimer;
extern int savedSleepTemp;

// ================= CALIBRATION =================
extern int tempOffset;
extern int adcOffset;
extern int adcRaw;

// ================= EDIT MODES =================
extern bool boostEditMode;
extern bool pidEditMode;
extern bool sleepEditMode;
extern bool buzzerEditMode;
extern bool calEditMode;

// ================= ENCODER / MENU =================
extern int lastEncoder;
extern int lastMenuPos;

// ================= TIMERS =================
extern unsigned long lastMotion;
extern unsigned long btnPressStart;
extern unsigned long lastActivity;

// ============== SYSTEM =================
extern int maxTemp;
extern float inputVoltage;

// ========= TEMPERATURE ===============
extern int targetTemp;    
extern int currentTemp;   
extern int pwmOut;

// ================= PID =================
extern float kp;
extern float ki;
extern float kd;

void setTipProfile(int type);

#endif
