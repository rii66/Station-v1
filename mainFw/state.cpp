#include "config.h"
#include "state.h"
#include "pages.h"
#include "tip.h"

// ================= UI =================
int page = 0;
int item = 0;

bool inMenu = false;
bool inEdit = false;
bool booting = true;
bool isEditingValue = false;

uint8_t pidStage = 0;

// ================= BUTTON =================
unsigned long btnPressStart = 0;
bool btnHolding = false;

// ================= MODE =================
bool sleeping = false;
bool boostMode = false;
bool manualPWMMode = false;

// ================= SYSTEM =================
unsigned long lastActivity = 0;
unsigned long lastMotion   = 0;
unsigned long sleepTimer   = 0;

int currentTemp = 0;
int pwmOut      = 0;

int tempOffset = 0;
int adcOffset  = 0;
int adcRaw     = 0;

int maxTemp     = 450;
int maxPwmLimit = 255;

float inputVoltage = 24.0f;

// ================= SETTINGS =================
int savedSleepTemp = DEFAULT_TEMP;
int sleepTimeSec   = 30;

bool menuClick = false;

bool buzzerEnabled  = true;
bool webControl     = false;
bool motionDetected = false;

// ================= TIP =================

TipID currentTip;      // tip/profil aktif
TipID detectedTip;     // hasil deteksi
uint8_t currentTipMode; // pilihan menu

// ================= PID =================
float kp = 0.0f;
float ki = 0.0f;
float kd = 0.0f;

// ================= SAFETY =================
uint8_t heaterState = STATE_IDLE;

bool tipError = false;
bool overHeat = false;


//======================================================
// PILIH MODE TIP
//======================================================

void setTipProfile(int mode)
{
    currentTipMode = mode;

    switch (mode)
    {
        // Manual T12
        case TIP_ITEM_T12:
            applyTipProfile(&tipDatabase[0]);
            break;

        // Manual C210
        case TIP_ITEM_C210:
            applyTipProfile(&tipDatabase[1]);
            break;

        // Manual Custom
        case TIP_ITEM_CUSTOM:
            applyTipProfile(&customTipProfile);
            break;

        // AUTO hanya memilih MODE.
        // Profil aktif dipilih oleh detectTip().
        case TIP_ITEM_AUTO:
        default:
            break;
    }

    // Clamp suhu bila profil berubah
    if (targetTemp > maxTemp)
        targetTemp = maxTemp;
}