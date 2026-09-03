#ifndef MONITORING_H
#define MONITORING_H

#include <Arduino.h>

inline void monitorADC() {
    static unsigned long lastPrint = 0;
    // Cetak setiap 500ms sekali supaya Serial Monitor tidak spam/nge-lag
    if (millis() - lastPrint > 500) {
        lastPrint = millis();

        uint16_t rawAdc = analogRead(TEMP_PIN); // Mengambil langsung dari pin config

        Serial.print("ADC Raw: ");
        Serial.print(rawAdc);
        Serial.print(" | currentTemp: ");
        Serial.print(currentTemp);
        Serial.print("C | targetTemp: ");
        Serial.println(targetTemp);
    }
}

#endif
