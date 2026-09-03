#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include <ArduinoOTA.h>
#include <Preferences.h>

// Konfigurasi dan State Utama
#include "config.h"
#include "state.h"
#include "storage.h"

// Modul UI dan Display
#include "display.h"
#include "ui.h"
#include "icons.h"
#include "pages.h"
#include "menu.h"
#include "bootanim.h"

// Modul Hardware/Sensor/Aktuator
#include "encoder.h"
#include "buzzer.h"
#include "rgb.h"
#include "motion.h"
#include "boost.h"

// Algoritma/Kontrol
#include "tip.h"
#include "pid.h"
#include "pwm.h"
#include "ptc.h"

// Jaringan dan Web (Network)
#include "wifi_manager.h"
#include "webserver.h"
#include "websocket_handler.h"
#include "web.h"
#include "ota.h"

#include "monitoring.h"

// ================= GLOBAL =================
WebServer server(80);
WebSocketsServer webSocket(81);

void initWebServer();

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(
  U8G2_R0,
  U8X8_PIN_NONE
);
// ========================================
 //================= SETUP =================
  // =========================================
void setup() {

  Serial.begin(115200);
  
  booting = true;
  initRGB();
  booting = false;

  initDisplay();
  playBootAnimation();

  initStorage();
  loadSettings();              //load data booting
  setTipProfile(currentTip); 

  initEncoder();
  
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RGB_RED, OUTPUT);
  pinMode(RGB_BLUE, OUTPUT);

  initPWM();
  initPTC();
  
  detectTip();
  
  setupWiFi();
  setupOTA();

  initWebServer();
  initWebSocket();

  initMotion();

  lastActivity = millis();
   
  beep();
}

// =========================================
 // ==============   LOOP  =================
  // ==========================================
void loop() {

  // ==========================================
  // 1. SENSOR & LOGIC
  // ==========================================
  monitorADC();
  
  // mengeksekusi proteksi (handleSafety).
  updatePID();              

  // mata solder dicabut (ERR), panggil deteksi ulang.
  // delay(500) di detectTip() 
  if (tipError) {
      detectTip();
  }


  // ==========================================
  // 2. INPUT & MENU (Interaksi User)
  // ==========================================
  bool btn = buttonPressed();
  int dir = getEncoderDelta();

  handleMenu(dir, btn);
  menuClick = false;


  // ==========================================
  // 3. BACKGROUND SYSTEM (Fitur Tambahan)
  // ==========================================
  updateBoost();
  updateMotion();
  updateRGB();


  // ==========================================
  // 4. NETWORK (Konektivitas)
  // ==========================================
  ArduinoOTA.handle();
  server.handleClient();
  webSocket.loop();


  // ==========================================
  // 5. DISPLAY & DATA (Output)
  // ==========================================
  drawUI();
  sendLiveData();


  // ==========================================
  // 6. PACING (Napas Prosesor) // Menjaga loop berjalan stabil di ~50Hz
  // ==========================================
  delay(20);
}
