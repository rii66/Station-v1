#include <Preferences.h>

#include "config.h"
#include "storage.h"
#include "pid.h"
#include "boost.h"
#include "state.h"
#include "menu.h"
#include "tip.h"
#include "pages.h"

Preferences prefs;

// ================= INIT =================

void initStorage() {
    prefs.begin("iron", false);
}

// ================= LOAD =================

void loadSettings() {

    targetTemp   = prefs.getInt("temp", DEFAULT_TEMP);

    boostTemp    = prefs.getInt("boostT", DEFAULT_BOOST_TEMP);
    boostTimeSec = prefs.getInt("boostS", DEFAULT_BOOST_TIME);

    sleepTemp    = prefs.getInt("sleepT", DEFAULT_SLEEP_TEMP);
    sleepTimeSec = prefs.getInt("sleepS", 240);
    buzzerEnabled = prefs.getBool("buzzer", true);

    // Mode terakhir
    currentTipMode = prefs.getInt("tipMode", TIP_ITEM_AUTO);
    // Validasi EEPROM
    if(currentTipMode < TIP_ITEM_T12 ||
    currentTipMode > TIP_ITEM_CUSTOM)
    {
    currentTipMode = TIP_ITEM_AUTO;
    }

    // ===== LOAD DATABASE =====
    for (int i = 0; i < TOTAL_SUPPORTED_TIPS; i++) {

        String key = String(tipDatabase[i].name);

        tipDatabase[i].kp = prefs.getFloat(
            (key + "_kp").c_str(),
            tipDatabase[i].kp
        );

        tipDatabase[i].ki = prefs.getFloat(
            (key + "_ki").c_str(),
            tipDatabase[i].ki
        );

        tipDatabase[i].kd = prefs.getFloat(
            (key + "_kd").c_str(),
            tipDatabase[i].kd
        );

        tipDatabase[i].tempOffset = prefs.getInt(
            (key + "_tOff").c_str(),
            tipDatabase[i].tempOffset
        );

        tipDatabase[i].adcOffset = prefs.getInt(
            (key + "_aOff").c_str(),
            tipDatabase[i].adcOffset
        );
    }

    // ===== RESTORE MODE =====
    switch (currentTipMode) {

        case TIP_ITEM_T12:
            applyTipProfile(&tipDatabase[0]);
            break;

        case TIP_ITEM_C210:
            applyTipProfile(&tipDatabase[1]);
            break;

        case TIP_ITEM_CUSTOM:
            applyTipProfile(&customTipProfile);
            break;

        case TIP_ITEM_AUTO:
        default:
            detectTip();
            break;
    }
}

// ================= APPLY PROFILE =================

void applyTipProfile(TipConfig *targetTip) {

    if (!targetTip)
        return;

    activeTip  = targetTip;
    currentTip = targetTip->tipID;

    kp = targetTip->kp;
    ki = targetTip->ki;
    kd = targetTip->kd;

    maxTemp = targetTip->maxTemp;

    tempOffset = targetTip->tempOffset;
    adcOffset  = targetTip->adcOffset;

    maxPwmLimit = map(
        targetTip->maxPWM,
        0,
        100,
        0,
        PWM_MAX_VAL
    );

    if (targetTemp > maxTemp)
        targetTemp = maxTemp;
}

// ================= SAVE MAIN =================

void saveSettings() {
    prefs.putInt("temp", targetTemp);
}

// ================= SAVE BOOST =================

void saveBoost() {

    prefs.putInt("boostT", boostTemp);
    prefs.putInt("boostS", boostTimeSec);

}

// ================= SAVE SLEEP =================

void saveSleep() {

    prefs.putInt("sleepT", sleepTemp);
    prefs.putInt("sleepS", sleepTimeSec);

}

// ================= SAVE CAL =================

void saveCal() {

    if (!activeTip)
        return;

    activeTip->tempOffset = tempOffset;
    activeTip->adcOffset  = adcOffset;

    String key = String(activeTip->name);

    prefs.putInt((key + "_tOff").c_str(), tempOffset);
    prefs.putInt((key + "_aOff").c_str(), adcOffset);
}

// ================= SAVE TIP =================

void saveTip() {

    // AUTO hanya menyimpan mode
    prefs.putInt("tipMode", currentTipMode);

}

// ================= SAVE PID =================

void saveActivePID() {

    if (!activeTip )
        return;

    activeTip->kp = kp;
    activeTip->ki = ki;
    activeTip->kd = kd;

    String key = String(activeTip->name);

    prefs.putFloat((key + "_kp").c_str(), kp);
    prefs.putFloat((key + "_ki").c_str(), ki);
    prefs.putFloat((key + "_kd").c_str(), kd);

}

// ================= SAVE BUZZER =================

void saveBuzzer() {

    prefs.putBool("buzzer", buzzerEnabled);

}
// ================= FACTORY RESET =================

void factoryReset() {

    prefs.clear();

}