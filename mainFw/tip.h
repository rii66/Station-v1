#ifndef TIP_H
#define TIP_H

#include <Arduino.h>


// ===== TIP ID =====
typedef enum {

    TIP_T12 = 0,
    TIP_C210,
    TIP_AUTO,
    TIP_CUSTOM // ptc support 

} TipID;



// ===== TIP DATABASE =====
typedef struct {

    TipID tipID;

    int minADC;
    int maxADC;

    float kp;
    float ki;
    float kd;

    uint8_t maxPWM;     // %

    int maxTemp;
    
    float slope;    // ADC ke suhu

    int tempOffset;
    int adcOffset;

    const char *name;

} TipConfig;



// ===== GLOBAL =====

extern TipConfig tipDatabase[];
extern const int TOTAL_SUPPORTED_TIPS;

extern TipConfig customTipProfile;

extern TipConfig *activeTip;

extern TipID detectedTip;


// ===== API =====

void applyTipProfile(TipConfig *targetTip);

void detectTip();


#endif