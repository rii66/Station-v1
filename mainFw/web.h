#ifndef WEB_H
#define WEB_H
#include <pgmspace.h>

const char index_html[] PROGMEM = R"rawliteral(

<!DOCTYPE html>
<html lang="id">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Solder Station PRO</title>
<style>
body{
  margin:0;
  font-family:Segoe UI,sans-serif;
  background:linear-gradient(135deg,#0f172a,#1e293b,#020617);
  color:white;
}
.topbar{
  padding:12px;
  background:rgba(0,0,0,.3);
  backdrop-filter:blur(10px);
  border-bottom:1px solid rgba(255,255,255,.08);
  font-weight:bold;
}
.menuBtn{
  float:right;
  font-size:26px;
  cursor:pointer;
}
.menuBox{
  position:fixed;
  top:50px;
  right:10px;
  width:220px;
  background:rgba(255,255,255,.05);
  backdrop-filter:blur(15px);
  border:1px solid rgba(255,255,255,.1);
  border-radius:12px;
  display:none;
  z-index:999;
}
.menuBox div{
  padding:12px;
  border-bottom:1px solid rgba(255,255,255,.08);
  cursor:pointer;
}
.menuBox div:hover{
  background:rgba(255,255,255,.1);
}
.card{
  margin:10px;
  padding:15px;
  border-radius:16px;
  background:rgba(255,255,255,.05);
  backdrop-filter:blur(15px);
  border:1px solid rgba(255,255,255,.08);
}
button{
  padding:10px;
  margin:4px;
  border:none;
  border-radius:10px;
  background:linear-gradient(90deg,#06b6d4,#2563eb);
  color:white;
  font-weight:bold;
}
input[type=range],select,input[type=file]{
  width:100%;
}
.big{
  font-size:42px;
  text-align:center;
}
.statusBar{
  display:flex;
  justify-content:space-between;
  font-size:12px;
  opacity:.8;
}
.sleepBtn{
  background:#1e293b;
  color:white;
  border:1px solid rgba(255,255,255,.1);
}
.sleepBtn.active{
  background:linear-gradient(90deg,#22c55e,#06b6d4);
  color:black;
}
progress{
  width:100%;
}
</style>
</head>
<body>

<div class="topbar">
🔥 🅂🄾🄻🄳🄴🅁 🅂🅃🄰🅃🄸🄾🄽 🔥
<span class="menuBtn" onclick="toggleMenu()">☰</span>
</div>

<div id="menuBox" class="menuBox">
  <div onclick="show('dash')">🏠 Dashboard</div>
  <div onclick="show('pid')">⚙ PID</div>
  <div onclick="show('tipcfg')">🔧 Tip Settings</div>
  <div onclick="show('templimit')">🌡 Temp Limit</div>
  <div onclick="show('sleep')">😴 Sleep</div>
  <div onclick="show('ota')">⬆ OTA Update</div>
</div>

<!-- DASHBOARD -->
<div id="dash">

<div class="card statusBar">
  <div>📶 WiFi: <span id="wifi">--</span></div>
  <div>🔧 Tip: <span id="tip">--</span></div>
  <div>⚡ Mode: <span id="mode">PID</span></div>
</div>

<div class="card">
  <div style="display:flex;justify-content:space-between;align-items:center">

    <div style="font-size:15px;line-height:1.9">
      <div>Temp Limit : <span id="maxTempVal">--</span>°C</div>
      <div>Temp Set : <span id="set">--</span>°C</div>
      <div>PWM : <span id="pwm">--</span>%</div>
    </div>

    <div class="big" id="temp"
    style="font-size:52px;font-weight:bold">
      --°C
    </div>

  </div>
</div>

<div class="card">
<h3>Set Temperature</h3>

<input type="range"
id="setSlider"
min="100"
max="450"
value="320"
oninput="setTemp(this.value)">

<div style="text-align:center">
Set: <span id="setVal">320</span>°C
</div>
</div>

<div class="card">
<h3>PWM Control</h3>

<input type="range" id="pwmSlider"
min="0" max="100"
value="0"
oninput="setPWM(this.value)">

<div style="text-align:center">
PWM: <span id="pwmVal">0</span> %
</div>

<button onclick="setPWM(15)">15</button>
<button onclick="setPWM(30)">30</button>
<button onclick="setPWM(50)">50</button>
<button onclick="setPWM(70)">70</button>
<button onclick="setPWM(90)">90</button>
<button onclick="boost()">BOOST</button>
</div>

</div>

<!-- TEMP LIMIT -->
<div id="templimit" style="display:none">
<div class="card">
<h3>Temperature Limit</h3>

<input type="range"
min="100"
max="450"
value="320"
id="tempLock"
oninput="setTempLock(this.value)">

<div style="text-align:center">
Max: <span id="maxTempVal2">320</span>°C
</div>
</div>
</div>

<!-- PID -->
<div id="pid" style="display:none">
<div class="card">
<h3>PID Tuning</h3>

Kp <input type="range" id="kp" min="0" max="40" step="0.1"><br>
Ki <input type="range" id="ki" min="0" max="2" step="0.01"><br>
Kd <input type="range" id="kd" min="0" max="80" step="0.1"><br>

<button onclick="sendPID()">SAVE PID</button>
</div>
</div>

<!-- TIP CONFIG -->
<div id="tipcfg" style="display:none">
<div class="card">
<h3>Tip Profile</h3>

<select id="tipSelect" onchange="setTip(this.value)">
  <option value="T12">T12</option>
  <option value="C210">C210</option>
  <option value="AUTO">AUTO</option>
</select>

<div style="margin-top:12px">
Current:
<b id="tipCurrent">T12 READY</b>
</div>

</div>
</div>

<!-- SLEEP -->
<div id="sleep" style="display:none">
<div class="card">
<h3>Sleep Timer</h3>

<button class="sleepBtn" id="s10" onclick="setSleepUI(10)">10s</button>
<button class="sleepBtn" id="s15" onclick="setSleepUI(15)">15s</button>
<button class="sleepBtn" id="s20" onclick="setSleepUI(20)">20s</button>
<button class="sleepBtn" id="s30" onclick="setSleepUI(30)">30s</button>

<div id="sleepText">SLEEP: OFF</div>
</div>
</div>

<!-- OTA -->
<div id="ota" style="display:none">

<div class="card">
<h3>OTA Firmware Update</h3>

<form id="uploadForm"
method="POST"
action="/update"
enctype="multipart/form-data">

<input type="file"
id="firmware"
name="update"
accept=".bin">

<button type="submit">UPLOAD</button>
</form>
</div>

<div class="card">
<h3>OTA Progress</h3>
<progress id="otabar" value="0" max="100"></progress>
<div id="otatext">Idle</div>
</div>

</div>

<script>
let ws;
let maxTemp = 320;

function toggleMenu(){
  menuBox.style.display =
  (menuBox.style.display=="block") ? "none" : "block";
}

function show(id){
  document.querySelectorAll("div[id]").forEach(e=>{
    if(["dash","pid","tipcfg","templimit","sleep","ota"].includes(e.id)){
      e.style.display="none";
    }
  });

  document.getElementById(id).style.display="block";
  menuBox.style.display="none";
}

function connect(){
  ws = new WebSocket("ws://" + location.hostname + ":81");

  ws.onopen = ()=>{
    console.log("WS CONNECTED");
  };

  ws.onmessage = (e)=>{
  let d = JSON.parse(e.data);

  temp.innerHTML = d.temp + "°C";

  set.innerHTML = d.set;
  setSlider.value = d.set;
  setVal.innerHTML = d.set;

  pwm.innerHTML = d.pwm;
  pwmSlider.value = d.pwm;
  pwmVal.innerHTML = d.pwm;

  wifi.innerHTML = d.wifi ? "ON" : "OFF";

  tip.innerHTML = d.tip;
  tipCurrent.innerHTML = d.tip + " READY";
  tipSelect.value = d.tip;

  mode.innerHTML = d.state;

  // Tambahan TipConfig
  if (d.maxTemp !== undefined) {
    maxTemp = d.maxTemp;
    maxTempVal.innerHTML = d.maxTemp;
    maxTempVal2.innerHTML = d.maxTemp;
    setSlider.max = d.maxTemp;
    tempLock.max = d.maxTemp;
  }

  if (d.kp !== undefined) kp.value = d.kp;
  if (d.ki !== undefined) ki.value = d.ki;
  if (d.kd !== undefined) kd.value = d.kd;
};
}

connect();

function safeSend(msg){
  if(ws && ws.readyState === WebSocket.OPEN){
    ws.send(msg);
  }
}

/* ================= TEMPERATURE ================= */

function setTemp(v){
  v = parseInt(v);

  setSlider.value = v;
  setVal.innerHTML = v;

  safeSend("SET:" + v);
}

/* ================= PWM ================= */

function setPWM(v){
  v = parseInt(v);

  pwmSlider.value = v;
  pwmVal.innerHTML = v;

  safeSend("PWM:" + v);
}

/* ================= BOOST ================= */

function boost(){
  safeSend("BOOST");
}

/* ================= TEMP LIMIT ================= */

function setTempLock(v){
  v = parseInt(v);

  maxTemp = v;

  maxTempVal.innerHTML = v;
  maxTempVal2.innerHTML = v;

  safeSend("MAXTEMP:" + v);
}

/* ================= PID ================= */

function sendPID(){

  safeSend(
      "PID:"
      + parseFloat(kp.value) + ","
      + parseFloat(ki.value) + ","
      + parseFloat(kd.value)
  );
}

/* ================= TIP ================= */

function setTip(name){

  tipCurrent.innerHTML = name + " READY";

  safeSend("TIP:" + name);
}

/* ================= SLEEP ================= */

function setSleepUI(sec){

  document.querySelectorAll(".sleepBtn").forEach(btn=>{
      btn.classList.remove("active");
  });

  let btn=document.getElementById("s"+sec);

  if(btn)
      btn.classList.add("active");

  sleepText.innerHTML =
      "SLEEP ACTIVE : " + sec + "s";

  safeSend("SLEEPTIME:" + sec);
}

</script>
</body>
</html>
)rawliteral";

#endif