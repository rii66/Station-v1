#include <WebSocketsServer.h>
#include <WiFi.h>

#include "config.h"
#include "boost.h"
#include "pid.h"
#include "tip.h"
#include "pwm.h"
#include "state.h"
#include "encoder.h"
#include "storage.h"
#include "ota.h"

extern WebSocketsServer webSocket;

void onWebSocketEvent(
    uint8_t num,
    WStype_t type,
    uint8_t *payload,
    size_t length)
{
    if (type != WStype_TEXT)
        return;

    String msg = String((char *)payload);

    Serial.println("RX: " + msg);

    /* ================= SET TEMP ================= */

    if (msg.startsWith("SET:")) {

        targetTemp = constrain(
            msg.substring(4).toInt(),
            TEMP_MIN,
            maxTemp);

        webControl = true;
        manualPWMMode = false;

        saveSettings();
    }

    /* ================= MANUAL PWM ================= */

    else if (msg.startsWith("PWM:")) {

        manualPWMMode = true;

        int pwmPercent = constrain(
            msg.substring(4).toInt(),
            0,
            100);

        int pwm = map(
            pwmPercent,
            0,
            100,
            0,
            maxPwmLimit);

        setPWM(pwm);
    }

    /* ================= BOOST ================= */

    else if (msg == "BOOST") {

        startBoost();
    }

    /* ================= MAX TEMP ================= */

    else if (msg.startsWith("MAXTEMP:")) {

        int hwLimit = activeTip ? activeTip->maxTemp : TEMP_MAX_T12;

        maxTemp = constrain(
            msg.substring(8).toInt(),
            TEMP_MIN,
            hwLimit);

        if (targetTemp > maxTemp)
            targetTemp = maxTemp;

        saveSettings();
    }

    /* ================= SLEEP ================= */

    else if (msg.startsWith("SLEEPTIME:")) {

        sleepTimeSec = msg.substring(10).toInt();

        saveSleep();
    }

    /* ================= PID ================= */

    else if (msg.startsWith("PID:")) {

        if (!activeTip)
            return;

        String data = msg.substring(4);

        int p1 = data.indexOf(',');
        int p2 = data.lastIndexOf(',');

        float newKp = data.substring(0, p1).toFloat();
        float newKi = data.substring(p1 + 1, p2).toFloat();
        float newKd = data.substring(p2 + 1).toFloat();

        kp = newKp;
        ki = newKi;
        kd = newKd;

        activeTip->kp = newKp;
        activeTip->ki = newKi;
        activeTip->kd = newKd;

        saveActivePID();
    }

    /* ================= TIP ================= */

    else if (msg.startsWith("TIP:")) {

        String requested = msg.substring(4);

        for (int i = 0; i < TOTAL_SUPPORTED_TIPS; i++) {

            if (requested.equalsIgnoreCase(tipDatabase[i].name)) {

                applyTipProfile(&tipDatabase[i]);

                saveTip();

                break;
            }
        }
    }

    lastActivity = millis();
}

/* ================================================= */

void initWebSocket()
{
    webSocket.begin();
    webSocket.onEvent(onWebSocketEvent);
}

/* ================================================= */

void sendLiveData()
{
    String packet = "{";

    packet += "\"temp\":" + String(currentTemp) + ",";
    packet += "\"set\":" + String(targetTemp) + ",";

    packet += "\"pwm\":";
    packet += String(map(pwmOut, 0, maxPwmLimit, 0, 100));
    packet += ",";

    packet += "\"wifi\":";
    packet += (WiFi.status() == WL_CONNECTED ? "true" : "false");
    packet += ",";

    packet += "\"tip\":\"";
    packet += (activeTip ? activeTip->name : "NONE");
    packet += "\",";

    packet += "\"kp\":";
    packet += String(kp, 2);
    packet += ",";

    packet += "\"ki\":";
    packet += String(ki, 2);
    packet += ",";

    packet += "\"kd\":";
    packet += String(kd, 2);
    packet += ",";

    packet += "\"maxTemp\":";
    packet += String(activeTip ? activeTip->maxTemp : maxTemp);
    packet += ",";

    packet += "\"maxPWM\":";
    packet += String(activeTip ? activeTip->maxPWM : 100);
    packet += ",";

    packet += "\"state\":\"";

    if (tipError)
        packet += "ERROR";
    else if (boostMode)
        packet += "BOOST";
    else if (sleeping)
        packet += "SLEEP";
    else if (manualPWMMode)
        packet += "MANUAL";
    else
        packet += "PID";

    packet += "\"";

    packet += "}";

    webSocket.broadcastTXT(packet);
}