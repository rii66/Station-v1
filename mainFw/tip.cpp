#include "tip.h"
#include "state.h"

TipConfig tipDatabase[] = {

    {
        TIP_T12,

        600,
        900,

        3.2,
        0.12,
        1.8,

        255,  // pwm 100%
        450,

        0.12f,   // slope
        0,       // tempOffset
        0,       // adcOffset

        "T12"
    },


    {
        TIP_C210,

        100,
        500,

        2.8,
        0.10,
        1.4,

        71,  // pwm ~28%
        380,

        0.12f,   // slope
        0,
        0,

        "C210"
    }

};


const int TOTAL_SUPPORTED_TIPS =
    sizeof(tipDatabase) / sizeof(tipDatabase[0]);



// ===== CUSTOM PROFILE =====
TipConfig customTipProfile = {

    TIP_CUSTOM,

    0,
    1023,

    2.0,
    0.05,
    0.8,

    255,  // pwm 100%
    600,

    0.12f,   //slope
    0,      //temp
    0,      //adc

    "CUSTOM"
};

TipConfig *activeTip = nullptr;