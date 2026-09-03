#include <Arduino.h>
#include <WiFi.h>
#include <U8g2lib.h>

#include "ui.h"
#include "state.h"
#include "pid.h"
#include "tip.h"
#include "pages.h"

extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;

void drawDashboard() {

    /* ===== CURRENT TEMP ===== */
  u8g2.setFont(u8g2_font_logisoso24_tf);

  if (tipError) {

    u8g2.setFont(u8g2_font_logisoso24_tf);
    u8g2.drawStr(0, 42, "EROR");

}
else {

    u8g2.setFont(u8g2_font_logisoso24_tf);

    char tempBuf[12];
    sprintf(tempBuf, "%d\xB0", currentTemp);
    u8g2.drawStr(0, 42, tempBuf);

}
  

  /* ===== TOP BAR ===== */
u8g2.setFont(u8g2_font_6x10_tf);

// ===== TIP STATUS =====
char tipBuf[16];

if (currentTipMode == TIP_ITEM_AUTO) {

    if (activeTip) {
        sprintf(tipBuf, "A>%s", activeTip->name);
    } 
    else {
        sprintf(tipBuf, "AUTO");
    }

}
else {

    if (activeTip) {
        sprintf(tipBuf, "%s", activeTip->name);
    }
    else {
        sprintf(tipBuf, "NoTip");
    }

}

u8g2.drawStr(0, 10, tipBuf);
  /*
char vbuf[10];
sprintf(vbuf, "%.1fV", inputVoltage);
u8g2.drawStr(36, 10, vbuf);
*/

// ===== WIFI STATUS =====
u8g2.drawStr(
    100, 10,
    WiFi.status() == WL_CONNECTED ? "WIFI" : "AP"
);

/* ===== RIGHT PANEL ===== */

u8g2.setFont(u8g2_font_6x10_tf);
u8g2.drawStr(78, 18, "SET");

u8g2.setFont(u8g2_font_logisoso18_tf);

if (tipError) {
  u8g2.drawStr(66, 36, "EROR");      // ganti suhu target
}
else if (sleeping) {
  u8g2.drawStr(66, 36, "SLEEP");     // ganti suhu target
}
else {
  // Normal
  char setBuf[12];
  sprintf(setBuf, "%d\xB0", targetTemp);
  u8g2.drawStr(74, 36, setBuf);
}

/* ===== PWM ===== */
u8g2.setFont(u8g2_font_6x10_tf);
u8g2.drawStr(78, 46, "PWM");

int pwmPercent = map(pwmOut, 0, 255, 0, 100);
int barWidth   = map(pwmOut, 0, 255, 0, 48);

u8g2.drawFrame(74, 50, 48, 8);
u8g2.drawBox(74, 50, barWidth, 8);

char pwmBuf[8];
sprintf(pwmBuf, "%d%%", pwmPercent);
u8g2.drawStr(86, 64, pwmBuf);

    /* ===== MODE BADGE ===== */
u8g2.drawFrame(0, 54, 52, 10);

if (boostMode)
    u8g2.drawStr(4, 62, "BOOST");
else if (sleeping)
    u8g2.drawStr(4, 62, "TiduR");
else if (manualPWMMode)
    u8g2.drawStr(4, 62, "PWM");
else
    u8g2.drawStr(4, 62, "StatuS");
    
}
