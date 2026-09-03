#include <U8g2lib.h>
#include <Arduino.h>

#include "icons.h"
#include "pages.h"
#include "state.h"
#include "pid.h"
#include "tip.h"
#include "boost.h"
#include "buzzer.h"

extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;

/* ====================================================
                       SET PAGE UI DASHBOARD
==================================================== */
void drawSetPage(int x) {
  char buf[16];

  // ===== TITLE PAGE =====
  if (!inEdit) {
    u8g2.setFont(u8g2_font_fub30_tf);
    u8g2.drawStr(x + 28, 38, "SET");

    u8g2.setFont(u8g2_font_6x10_tf);
    u8g2.drawStr(x + 30, 60, "Click Enter");
    return;
  }

  // ===== HEADER =====
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.drawLine(x, 12, x+127, 12);

  // SAVE
  if (item == SET_SAVE) {
    u8g2.drawBox(x+4, 2, 40, 8);
    u8g2.setDrawColor(0);
    u8g2.drawStr(x+10, 9, "SAVE");
    u8g2.setDrawColor(1);
  } else {
    u8g2.drawStr(x+10, 9, "SAVE");
  }

  // EXIT
  if (item == SET_EXIT) {
    u8g2.drawBox(x+84, 2, 40, 8);
    u8g2.setDrawColor(0);
    u8g2.drawStr(x+92, 9, "EXIT");
    u8g2.setDrawColor(1);
  } else {
    u8g2.drawStr(x+92, 9, "EXIT");
  }
  
  // ===== CURRENT TEMP =====
  drawcurrentTemp(x);

  // ===== LABEL =====
  u8g2.setFont(u8g2_font_7x14_tf);

  if (item == SET_TEMP)
    u8g2.drawStr(x+10, 22, "> TEMP");
  else
    u8g2.drawStr(x+18, 22, "TEMP");

  // ===== BIG TEMP =====
  u8g2.setFont(u8g2_font_logisoso24_tf);
  sprintf(buf, "%d", targetTemp);
  u8g2.drawStr(x+22, 50, buf);

  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.drawStr(x+92, 34, "C");

  // ===== FOOTER =====
  u8g2.drawLine(x, 54, x+127, 54);

  sprintf(buf, "MIN:%d", TEMP_MIN);
  u8g2.drawStr(x+8, 63, buf);

  sprintf(buf, "MAX:%d", maxTemp);
  u8g2.drawStr(x+74, 63, buf);
}
// STATUS TEMPERATUR MENU //
void drawcurrentTemp(int x)
{
    char buf[8];
    sprintf(buf, "%dC", currentTemp);

    u8g2.setFont(u8g2_font_6x10_tf);
    int w = u8g2.getStrWidth(buf);
    u8g2.drawStr(x + (128 - w) / 2, 9, buf);
}

/* =========================================================
                             BOOST PAGE
==================================================== */
void drawBoostPage(int x) {
  char buf[12];

  // ===== TITLE PAGE =====
  if (!inEdit) {
    u8g2.setFont(u8g2_font_fub30_tf);
    u8g2.drawStr(x + 8, 38, "BosT");

    u8g2.setFont(u8g2_font_6x10_tf);
    u8g2.drawStr(x + 30, 60, "masuk");
    return;
  }

  // ===== SUB MENU =====
  u8g2.setFont(u8g2_font_6x10_tf);

  // header zone (kuning OLED)
  u8g2.drawLine(x, 12, x+127, 12);
  
  drawcurrentTemp(x);

  // SAVE
  if (item == BOOST_SAVE) {
    u8g2.drawBox(x+4, 2, 40, 8);
    u8g2.setDrawColor(0);
    u8g2.drawStr(x+10, 9, "SAVE");
    u8g2.setDrawColor(1);
  } else {
    u8g2.drawStr(x+10, 9, "SAVE");
  }

  // EXIT
  if (item == BOOST_EXIT) {
    u8g2.drawBox(x+84, 2, 40, 8);
    u8g2.setDrawColor(0);
    u8g2.drawStr(x+92, 9, "EXIT");
    u8g2.setDrawColor(1);
  } else {
    u8g2.drawStr(x+92, 9, "EXIT");
  }

  // BODY
  if (item == BOOST_TEMP) u8g2.drawStr(x+4, 30, ">");
  u8g2.drawStr(x+16, 30, "TEMP");
  sprintf(buf, "%dC", boostTemp);
  u8g2.drawStr(x+88, 30, buf);

  if (item == BOOST_TIME) u8g2.drawStr(x+4, 44, ">");
  u8g2.drawStr(x+16, 44, "TIME");
  sprintf(buf, "%ds", boostTimeSec);
  u8g2.drawStr(x+88, 44, buf);

  u8g2.drawLine(x, 63, x+127, 63);
}

/* ====================================================
                             SLEEP PAGE
==================================================== */
void drawSleepPage(int x) {
  char buf[12];

  // ===== TITLE PAGE =====
  if (!inEdit) {
    u8g2.setFont(u8g2_font_profont29_mr);
    u8g2.drawStr(x + 12, 36, "SLEEP");

    u8g2.setFont(u8g2_font_6x10_tf);
    u8g2.drawStr(x + 30, 60, "masuk");
    return;
  }

  // ===== SUB MENU =====
  u8g2.setFont(u8g2_font_6x10_tf);

  // Header (zona kuning)
  u8g2.drawLine(x, 12, x + 127, 12);
  
  drawcurrentTemp(x);

  // SAVE
  if (item == SLEEP_SAVE) {
    u8g2.drawBox(x + 4, 2, 40, 8);
    u8g2.setDrawColor(0);
    u8g2.drawStr(x + 10, 9, "SAVE");
    u8g2.setDrawColor(1);
  } else {
    u8g2.drawStr(x + 10, 9, "SAVE");
  }

  // EXIT
  if (item == SLEEP_EXIT) {
    u8g2.drawBox(x + 84, 2, 40, 8);
    u8g2.setDrawColor(0);
    u8g2.drawStr(x + 92, 9, "EXIT");
    u8g2.setDrawColor(1);
  } else {
    u8g2.drawStr(x + 92, 9, "EXIT");
  }

  // TEMP
  if (item == SLEEP_TEMP) u8g2.drawStr(x + 4, 30, ">");
  u8g2.drawStr(x + 16, 30, "TEMP");
  sprintf(buf, "%dC", sleepTemp);
  u8g2.drawStr(x + 88, 30, buf);

  // TIME
  if (item == SLEEP_TIME) u8g2.drawStr(x + 4, 44, ">");
  u8g2.drawStr(x + 16, 44, "TIME");
  sprintf(buf, "%ds", sleepTimeSec);
  u8g2.drawStr(x + 88, 44, buf);

  // Footer
  u8g2.drawLine(x, 63, x + 127, 63);
}

/* ====================================================
                             CAL PAGE
==================================================== */
void drawCalPage(int x) {
  char buf[12];

  if (!inEdit) {
    u8g2.setFont(u8g2_font_fub30_tf);
    u8g2.drawStr(x + 28, 40, "CAL");

    u8g2.setFont(u8g2_font_6x10_tf);
    u8g2.drawStr(x + 30, 60, "Click Enter");
    return;
  }

  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.drawLine(x, 12, x+127, 12);
  
  drawcurrentTemp(x);

  if (item == CAL_SAVE) {
    u8g2.drawBox(x+4, 2, 40, 8);
    u8g2.setDrawColor(0);
    u8g2.drawStr(x+10, 9, "SAVE");
    u8g2.setDrawColor(1);
  } else {
    u8g2.drawStr(x+10, 9, "SAVE");
  }

  if (item == CAL_EXIT) {
    u8g2.drawBox(x+84, 2, 40, 8);
    u8g2.setDrawColor(0);
    u8g2.drawStr(x+92, 9, "EXIT");
    u8g2.setDrawColor(1);
  } else {
    u8g2.drawStr(x+92, 9, "EXIT");
  }

  if (item == CAL_OFFSET) u8g2.drawStr(x+4, 34, ">");
  u8g2.drawStr(x+16, 34, "OFFSET");

  sprintf(buf, "%d", tempOffset);
  u8g2.drawStr(x+88, 34, buf);
}

/* ====================================================
                             PID PAGE
==================================================== */
void drawPIDPage(int x) {
  char buf[16];

  // =========================================
  // LEVEL 0 : PID COVER
  // =========================================
  if (!inEdit) {
    u8g2.setFont(u8g2_font_fub30_tf);
    u8g2.drawStr(x + 28, 40, "PID");

    u8g2.setFont(u8g2_font_6x10_tf);
    u8g2.drawStr(x + 34, 60, "Click Enter");
    return;
  }

  // HEADER
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.drawLine(x, 12, x + 127, 12);
  
  drawcurrentTemp(x); // status temperatur 

  // =========================================
  // LEVEL 1 : PID LIST
  // =========================================
  if (!isEditingValue) {

    // SAVE
    if (item == PID_SAVE) {
      u8g2.drawBox(x + 4, 2, 40, 8);
      u8g2.setDrawColor(0);
      u8g2.drawStr(x + 10, 9, "SAVE");
      u8g2.setDrawColor(1);
    } else {
      u8g2.drawStr(x + 10, 9, "SAVE");
    }

    // EXIT
    if (item == PID_EXIT) {
      u8g2.drawBox(x + 84, 2, 40, 8);
      u8g2.setDrawColor(0);
      u8g2.drawStr(x + 92, 9, "EXIT");
      u8g2.setDrawColor(1);
    } else {
      u8g2.drawStr(x + 92, 9, "EXIT");
    }

    // LIST PID
    if (item == PID_KI) u8g2.drawStr(x + 10, 28, ">");
    u8g2.drawStr(x + 22, 28, "KI ────");

    if (item == PID_KP) u8g2.drawStr(x + 10, 42, ">");
    u8g2.drawStr(x + 22, 42, "KP ────");

    if (item == PID_KD) u8g2.drawStr(x + 10, 56, ">");
    u8g2.drawStr(x + 22, 56, "KD ────");
  }

  // =========================================
  // LEVEL 2 : EDIT VALUE
  // =========================================
  else {

    float val = 0;
    const char* label = "";

    if (item == PID_KP) {
      val = kp;
      label = "KP";
    }
    else if (item == PID_KI) {
      val = ki;
      label = "KI";
    }
    else if (item == PID_KD) {
      val = kd;
      label = "KD";
    }

    // SAVE
    u8g2.drawStr(x + 10, 9, "SAVE");
    u8g2.drawStr(x + 92, 9, "EXIT");

    // LABEL BESAR
    u8g2.setFont(u8g2_font_fub14_tf);
    u8g2.drawStr(x + 48, 28, label);

    // SLIDER
    u8g2.drawFrame(x + 18, 36, 92, 8);

    int slider = map(val * 100, 0, 99900, 0, 88);
    u8g2.drawDisc(x + 20 + slider, 40, 3);

    // VALUE
    u8g2.setFont(u8g2_font_6x12_tf);
    sprintf(buf, "%.2f", val);
    u8g2.drawStr(x + 42, 58, buf);
  }
}

/* ====================================================
                             BUZZER PAGE
==================================================== */
void drawBuzzerPage(int x) {
  // ===== TITLE PAGE =====
  if (!inEdit) {
    u8g2.setFont(u8g2_font_fub30_tf);
    u8g2.drawStr(x + 8, 32, "BuzeR");

    u8g2.setFont(u8g2_font_6x10_tf);
    u8g2.drawStr(x + 30, 60, "Click Enter");
    return;
  }

  // ===== SUB MENU =====
  u8g2.setFont(u8g2_font_6x10_tf);

  // header
  u8g2.drawLine(x, 12, x+127, 12);
  
  drawcurrentTemp(x);

  // SAVE
  if (item == BUZ_SAVE) {
    u8g2.drawBox(x+4, 2, 40, 8);
    u8g2.setDrawColor(0);
    u8g2.drawStr(x+10, 9, "SAVE");
    u8g2.setDrawColor(1);
  } else {
    u8g2.drawStr(x+10, 9, "SAVE");
  }

  // EXIT
  if (item == BUZ_EXIT) {
    u8g2.drawBox(x+84, 2, 40, 8);
    u8g2.setDrawColor(0);
    u8g2.drawStr(x+92, 9, "EXIT");
    u8g2.setDrawColor(1);
  } else {
    u8g2.drawStr(x+92, 9, "EXIT");
  }

  // ON
  if (item == BUZ_ON) u8g2.drawStr(x+10, 28, ">");
  u8g2.drawStr(x+24, 28, "ON");

  // OFF
  if (item == BUZ_OFF) u8g2.drawStr(x+10, 42, ">");
  u8g2.drawStr(x+24, 42, "OFF");

  // footer
  u8g2.drawLine(x, 54, x+127, 54);

  if (buzzerEnabled)
    u8g2.drawStr(x+36, 63, "STATE: ON");
  else
    u8g2.drawStr(x+34, 63, "STATE: OFF");
}

/* ====================================================
                          TIP PAGE
==================================================== */
void drawTipPage(int x) {

  if (!inEdit) {
    u8g2.setFont(u8g2_font_fub30_tf);
    u8g2.drawStr(x + 24, 40, "TIP");

    u8g2.setFont(u8g2_font_6x10_tf);
    u8g2.drawStr(x + 30, 60, "Click Enter");
    return;
  }

  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.drawLine(x, 12, x + 127, 12);
  
  drawcurrentTemp(x);

  // ===== SAVE =====
  if (item == TIP_ITEM_SAVE) {
    u8g2.drawBox(x + 4, 2, 40, 8);
    u8g2.setDrawColor(0);
    u8g2.drawStr(x + 10, 9, "SAVE");
    u8g2.setDrawColor(1);
  } else {
    u8g2.drawStr(x + 10, 9, "SAVE");
  }

  // ===== EXIT =====
  if (item == TIP_ITEM_EXIT) {
    u8g2.drawBox(x + 84, 2, 40, 8);
    u8g2.setDrawColor(0);
    u8g2.drawStr(x + 92, 9, "EXIT");
    u8g2.setDrawColor(1);
  } else {
    u8g2.drawStr(x + 92, 9, "EXIT");
  }

  // ===== T12 =====
  if (item == TIP_ITEM_T12)
    u8g2.drawStr(x + 4, 30, ">");
  u8g2.drawStr(x + 16, 30, "T12");

  // ===== C210 =====
  if (item == TIP_ITEM_C210)
    u8g2.drawStr(x + 52, 30, ">");
  u8g2.drawStr(x + 64, 30, "C210");

  // ===== AUTO =====
  if (item == TIP_ITEM_AUTO)
    u8g2.drawStr(x + 4, 44, ">");
  u8g2.drawStr(x + 16, 44, "AUTO");

  // ===== CUSTOM =====
  if (item == TIP_ITEM_CUSTOM)
    u8g2.drawStr(x + 52, 44, ">");
  u8g2.drawStr(x + 64, 44, "CUSTOM");

// ===== CURRENT STATUS =====
u8g2.drawLine(x, 54, x + 127, 54);

u8g2.setFont(u8g2_font_6x10_tf);

// MODE
u8g2.drawStr(x + 2, 61, "MODE:");

if (currentTipMode == TIP_ITEM_AUTO)
    u8g2.drawStr(x + 34, 61, "AUTO");

else if (currentTipMode == TIP_ITEM_T12)
    u8g2.drawStr(x + 34, 61, "T12");

else if (currentTipMode == TIP_ITEM_C210)
    u8g2.drawStr(x + 34, 61, "C210");

else if (currentTipMode == TIP_ITEM_CUSTOM)
    u8g2.drawStr(x + 34, 61, "CUSTOM");
}