#ifndef PAGES_H
#define PAGES_H

#include <Arduino.h>

/* ===== PAGE ===== */
enum Pages {
  PAGE_SET,
  PAGE_BOOST,
  PAGE_SLEEP,
  PAGE_CAL,
  PAGE_PID,
  PAGE_TIP,
  PAGE_BUZZER,
  PAGE_TOTAL
};

/* ===== SET ===== */
enum {
  SET_TEMP,
  SET_BOOST,
  SET_SLEEP,
  SET_CAL,
  SET_PID,
  SET_TIP,
  SET_BUZZER,
  SET_SAVE,
  SET_EXIT,
  SET_COUNT
};

/* ===== PID ===== */
enum {
  PID_KI,
  PID_KP,
  PID_KD,
  PID_SAVE,
  PID_EXIT,
  PID_COUNT
};

/* ===== BOOST ===== */
enum {
  BOOST_TEMP,
  BOOST_TIME,
  BOOST_SAVE,
  BOOST_EXIT,
  BOOST_COUNT
};

/* ===== SLEEP ===== */
enum {
  SLEEP_TEMP,
  SLEEP_TIME,
  SLEEP_SAVE,
  SLEEP_EXIT,
  SLEEP_COUNT
};

/* ===== CAL ===== */
enum {
  CAL_OFFSET,
  CAL_SAVE,
  CAL_EXIT,
  CAL_COUNT
};

/* ===== TIP ===== */
enum {
  TIP_ITEM_T12,
  TIP_ITEM_C210,
  TIP_ITEM_AUTO,
  TIP_ITEM_CUSTOM,
  TIP_ITEM_SAVE,
  TIP_ITEM_EXIT,
  TIP_COUNT
};

/* ===== BUZZER ===== */
enum {
  BUZ_ON,
  BUZ_OFF,
  BUZ_SAVE,
  BUZ_EXIT,
  BUZ_COUNT
};

extern bool inMenu;
extern bool inEdit;

#endif