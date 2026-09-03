#ifndef CONFIG_H
#define CONFIG_H

#define WIFI_SSID       "ICA ELEK"
#define WIFI_PASS       "koyok tekek"

#define AP_SSID         "SolderStation"
#define AP_PASS         "88889999"

#define OTA_HOSTNAME    "SolderStation"

/* ===== PINS ===== */
#define TEMP_PIN        0
#define PWM_PIN         2
#define BUZZER_PIN      8
#define RGB_RED         9
#define RGB_BLUE        10
#define ENC_SW          3
#define ENC_A           4
#define ENC_B           5
#define OLED_SDA        6
#define OLED_SCL        7
#define MOTION_PIN      1

/* ===== TIP TYPE ===== */
/* DIPINDAHKAN KE TIP FILE 
#define TIP_T12         0
#define TIP_C210        1
#define TIP_CUSTOM    2   

/* ===== PID T12 ===== */
#define PID_KP_T12      3.2f
#define PID_KI_T12      0.12f
#define PID_KD_T12      1.8f

/* ===== PID C210 ===== */
#define PID_KP_C210     2.8f
#define PID_KI_C210     0.10f
#define PID_KD_C210     1.4f

/* ===== PID CUSTOM ===== */
#define PID_KP_CUSTOM   3.0f
#define PID_KI_CUSTOM   0.11f
#define PID_KD_CUSTOM   1.6f

/* ===== TEMP LIMIT ===== */
#define TEMP_MIN        100
#define TEMP_MAX_T12    450
#define TEMP_MAX_C210   380
#define TEMP_MAX_CUSTOM  600

/* ===== DEFAULT TEMP ===== */
#define DEFAULT_TEMP    320
#define DEFAULT_BOOST_TEMP 470
#define DEFAULT_SLEEP_TEMP 195
#define DEFAULT_BOOST_TIME    12

// ===== TEMP OFFSET =====
#define OFFSET_TEMP_T12      0
#define OFFSET_TEMP_C210     0
#define OFFSET_TEMP_CUSTOM   0

// ===== ADC OFFSET =====
#define OFFSET_ADC_T12       0
#define OFFSET_ADC_C210      0
#define OFFSET_ADC_CUSTOM    0

/* ===== ADC DETECT ===== */
#define ADC_NO_TIP          150
#define ADC_NO_TIP_PTC     4000
#define ADC_CUSTOM_MIN    501
#define ADC_CUSTOM_MAX   599

/* ===== HARDWARE PWM CONFIG ===== */
#define PWM_FREQ        20000   // Frekuensi PWM (20kHz)
#define PWM_RES         8       // Resolusi 8-bit (0-255)
#define PWM_MAX_VAL     255     // Nilai maksimal 8-bit

/* ===== PWM POWER LIMIT (Skala 8-bit: 0-255) ===== */
// Pengaman utama biar elemen gak jadi abu!
#define MAX_PWM_T12     255     // 100% dari 255
#define MAX_PWM_C210    71      // 28% dari 255 = ~71 (C210 dibatasi )
#define MAX_PWM_CUSTOM  255     // 100% dari 255


#endif