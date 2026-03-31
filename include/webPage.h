#include <Arduino.h>

 const char webpage[] PROGMEM = R"rawliteral(

<!DOCTYPE html>
<html lang="en">
  <head>
    <meta name="theme-color" content="#474E65" />
    <meta name="mobile-web-app-capable" content="yes" />
    <meta name="application-name" content="Netatmo Relay" />

    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Netatmo Relay</title>
    <style type="text/css">* {
  margin: 0;
  padding: 0;
  box-sizing: border-box;
  font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, sans-serif;
}
.sparkline-container {
  width: 30px;
  height: 30px;
  display: flex;
  justify-content: center;
  align-items: center;
  margin: 5px 0;
  position: absolute;
  top: 5%;
  right: 17px;
  background-color: white;
  border-radius: 24px;
  border: solid 0.2px rgba(200, 200, 200, .6);
  overflow: hidden;
}
.sparkline-container svg{
  opacity: 0.7;
}
.valve-indicator {
  width: 8px;
  height: 8px;
  border-radius: 50%;
  background: #00a2ff;
  position: absolute;
  top: 184px;
  right: 40px;
  animation: pulse 0.9s infinite;
  border: solid 0.1px rgb(66, 102, 210);
}
.valve-indicator.secondary {
  animation: pulse 2s infinite;
  background:rgb(170, 192, 243);
  border: solid 0.1px rgb(66, 102, 210);
}

@keyframes pulse {
  0% {
    transform: scale(1);
    opacity: 1;
  }
  50% {
    transform: scale(1.5);
    opacity: 0.5;
  }
  100% {
    transform: scale(1);
    opacity: 1;
  }
}

/* Dark theme */
@media (prefers-color-scheme: dark) {
  :root {
    --l1: hsl(223, 10%, 50%);
    --l2: hsl(223, 10%, 45%);
    --l3: hsl(223, 10%, 40%);
    --l4: hsl(223, 10%, 35%);
    --l5: hsl(223, 10%, 30%);
    --l6: hsl(223, 10%, 25%);
    --green: hsla(78, 100%, 27%, 1);
    --text: hsl(223, 10%, 80%);
  }
}

@media (prefers-color-scheme: light) {
  :root {
    --green: hsla(78, 100%%, 27%%, 1);
  }
}

body {
  overflow: visible;
  background-image: linear-gradient(
    rgba(5, 5, 5, 0.2),
    rgba(5, 5, 5, 0.2) 0%,
    rgba(5, 5, 5, 0.2) 0%,
    rgba(5, 5, 5, 0.2) 0%,
    rgba(5, 5, 5, 0.2) 0%,
    rgba(5, 5, 5, 0.2)
  );
  transition: all ease 0.5s;
  min-height: 100vh;
  transition: background-color 0.5s ease;
}

/* no select class */

.no-select {
  -webkit-touch-callout: none; /* iOS Safari */
  -webkit-user-select: none; /* Safari */
  -khtml-user-select: none; /* Konqueror HTML */
  -moz-user-select: none; /* Old versions of Firefox */
  -ms-user-select: none; /* Internet Explorer/Edge */
  user-select: none; /* Non-prefixed version, currently supported by Chrome, Edge, Opera and Firefox */
}

/* no select for br, button, li, ul, body */
body,
button,
ul,
li,
br,
a {
  -webkit-touch-callout: none; /* iOS Safari */
  -webkit-user-select: none; /* Safari */
  -khtml-user-select: none; /* Konqueror HTML */
  -moz-user-select: none; /* Old versions of Firefox */
  -ms-user-select: none; /* Internet Explorer/Edge */
  user-select: none; /* Non-prefixed version, currently supported by Chrome, Edge, Opera and Firefox */
}

@keyframes fadeIn {
  from {
    opacity: 0;
  }
  to {
    opacity: 1;
  }
}
.quick-actions .eco-button {
  display: none;
}

.swiper-wrapper{

  display: flex;

}
.swiper-wrapper .swiper-slide{

  margin: 20px;

}
.nextHours{
  overflow: hidden;
}
#thermostat-list{

  max-width: 60%;
}


.container .imageBack_container {
  position: fixed;
  z-index: 0;
  right: -24%;
  bottom: 0px;
  width: 80%;
  overflow: hidden;
  opacity: 0.05;
  transform: scale(0.9);
  overflow: hidden;
}

.priority-display {
  opacity: 0.2;
  font-size: 10px !important;
  margin-top: -430px !important;
}
body.heating::before {
  content: "";
  background: rgba(255, 174, 0, 1);
  position: absolute;
  top: 0px;
  right: 0px;
  bottom: -201px;
  left: 0px;
  opacity: 1;
  transition: all ease 1s;
  background-image: -webkit-linear-gradient(
    #fd8000,
    #fe8a00 20%,
    #fe9300 40%,
    #ff9c00 60%,
    orange 80%,
    #ffae00
  );
  background-image: -moz-linear-gradient(
    #fd8000,
    #fe8a00 20%,
    #fe9300 40%,
    #ff9c00 60%,
    orange 80%,
    #ffae00
  );
  background-image: -o-linear-gradient(
    #fd8000,
    #fe8a00 20%,
    #fe9300 40%,
    #ff9c00 60%,
    orange 80%,
    #ffae00
  );
  background-image: linear-gradient(
    #fd8000,
    #fe8a00 20%,
    #fe9300 40%,
    #ff9c00 60%,
    orange 80%,
    #ffae00
  );
  background-position: 106px;
}

body::before {
  content: "";
  background: rgba(255, 174, 0, 1);
  position: absolute;
  opacity: 0;
  top: 0px;
  right: 0px;
  bottom: 0px;
  left: 0px;
  transition: all ease 1s;
  background-image: -webkit-linear-gradient(
    #fd8000,
    #fe8a00 20%,
    #fe9300 40%,
    #ff9c00 60%,
    orange 80%,
    #ffae00
  );
  background-image: -moz-linear-gradient(
    #fd8000,
    #fe8a00 20%,
    #fe9300 40%,
    #ff9c00 60%,
    orange 80%,
    #ffae00
  );
  background-image: -o-linear-gradient(
    #fd8000,
    #fe8a00 20%,
    #fe9300 40%,
    #ff9c00 60%,
    orange 80%,
    #ffae00
  );
  background-image: linear-gradient(
    #fd8000,
    #fe8a00 20%,
    #fe9300 40%,
    #ff9c00 60%,
    orange 80%,
    #ffae00
  );
  background-position: 100px;
}

.container {
  display: flex;
  max-width: 780px !important;
  margin: 0 auto;
  /* padding: 20px !important; */
  /* min-height: 100vh; */
  position: relative;
  /* overflow: scroll; */
  /* padding-bottom: 0px; */
  /* margin-bottom: 0px; */
  /* padding-bottom: 0px !important; */
  align-content: flex-start;
  flex-wrap: nowrap;
  justify-content: center;
  flex-direction: row;
}

.thermostat-list {
  padding: 20px 0;
  display: flex;
  flex-direction: column;
  gap: 16px;
  max-height: calc(100vh - 140px);
  /* overflow-; */
  scroll-behavior: smooth;
}
.thermostat-card {
  margin-top: 20px;
  transition: transform all 0.5s ease;
  animation: fadeIn 1s;
}

.thermostat-card.expanded {
  /* width: 95vw; */
  height: 449px;
  /*    left: -20vh; */
}

/* .thermostat-card.expanded {
  position: fixed !important;
width: 100%;
z-index: 10000;
height: 100%;
top: 0;
left: 0;
animation: expandToFullScreen 0.5s forwards;

} */
@keyframes shrinkToNormal {
  0% {
    transform: scale(1);
  }
  100% {
    transform: scale(0.4);
  }
}
@keyframes expandToFullScreen {
  0% {
    transform: scale(0.4);
    opacity: 0;
  }
  50% {
    opacity: 1;
  }
  100% {
    transform: scale(1);
    opacity: 1;
  }
}

.thermostat-card .a_fire .manifoldTemp {
  display: none;
}

footer .a_fire .manifoldTemp {
  position: absolute;
  color: #ffe1e1;
  font-size: 10px;
  margin-top: 34px;
  margin-left: 8px;
  background-color: rgba(200, 200, 200, 0.3);
  border-radius: 30px;
  padding: 3px;
}

.thermostat-card {
  border-top: 3px solid #66666687;
  background: white;
  padding: 29px;
  border-radius: 20px;
  /* border-bottom: 0.6px darkred solid; */

  box-shadow: 16px 26px 70px 30px rgba(0, 0, 0, 0.1);
  cursor: pointer;
  transition: all 0.4s cubic-bezier(0.4, 0, 0.2, 1);
  position: relative;
  transform-origin: center;
  height: 210px;
  z-index: 1;
  overflow: hidden;
  /* animation: shrinkToNormal 0.5s backwards; */
}

.thermostat-list .battery_indicator {
}
.thermostat-card .battery_indicator {
  opacity: 0;
  position: relative;
  top: -200px;
  transform: scale(0.5) scaleY(0.7);
  left: 365px;
  width: 46px;
  transition: all 0s ease !important;
}
.thermostat-card.expanded .battery_indicator {
  opacity: 1;
  position: relative;
  top: -329px;
  transform: scale(0.5) scaleY(0.7);
  left: 365px;
  width: 46px;
  transition: all ease 0.3s !important;
}
.thermostat-card h2 {
  font-size: 20px;
  margin-bottom: 12px;
  color: #333;
  transition: all 0.4s ease;
  padding-right: 24px;
  max-width: 50%;
}

.expanded h2 {
  /* font-size: 24px; */
  margin-left: -15px;
  background: #c7c6c6;
  max-width: 50%;
  padding: 12px;
  margin-top: -14px;
  color: white;
  text-align: left;
  border-radius: 30px;
  box-shadow: inset 0px 0px 13px 4px rgba(0, 0, 0, 0.1);
  font-weight: 900;
  padding-left: 43px;
}

.temperatures {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin: 20px 0;
  transition: all 2s ease;
}

.temperature {
  text-align: center;
}

.temperature-value {
  font-size: 32px;
  font-weight: 300;
  color: #1a1a1a;
  font-family: lcd;
}

.temperature-label {
  font-size: 12px;
  color: #666;
  margin-top: 4px;
  text-align: left;
}


.oc, .percent{
  font-size: 0.5em !important;
  margin-top: 4px;
  position: absolute;
  font-family: lcd;
  margin-left: 13px;
}
.AMPM{

  position: absolute;
  margin-top: -16px;
  font-size: 0.8em !important;
  margin-left: 46px;


}
.time_dis {
  background-color: rgba(230, 230, 230, .500);
  margin-left: -19px;
  position: absolute;
  width: 44px;
  padding-right: 1px;
  height: 19px;
  line-height: 0px;
  margin-top: -19px !important;
  text-align: center;
  color: gray;
  font-size: 14px !important;
  padding-top: 0px !important;
  border-radius: 29px;
}

.noselect {

  user-select: none;


}
.expanded .temperatures {
  flex-direction: row;
  gap: 20px;
  margin: 40px 0;
}

.expanded .temperature-label {
  /* font-size: 14px; */
}

.controls {
  height: 0;
  opacity: 0;
  transform: translateY(-20px);
  transition: all 0.8s ease;
  overflow: hidden;
}

.expanded .controls {
  height: auto;
  opacity: 1;
  transform: translateY(0);
  padding-top: 20px;
}

.temperature-slider {
  width: 100%;
  margin: 20px 0;
  height: 20px;
  -webkit-appearance: none;
  background: #f0f0f0;
  border-radius: 10px;
  outline: none;
}

.temperature-slider::-webkit-slider-thumb {
  -webkit-appearance: none;
  width: 28px;
  height: 28px;
  background: #ff6b00;
  border-radius: 50%;
  cursor: pointer;
  box-shadow: 0 2px 6px rgba(255, 107, 0, 0.3);
}

.quick-actions {
  display: flex;
  gap: 8px;
  margin-top: 12px;
}

.action-button {
  padding: 8px 16px;
  border: 1px solid #e0e0e0;
  border-radius: 20px;
  background: transparent;
  color: #666;
  font-size: 12px;
  cursor: pointer;
  transition: all 0.2s ease;
}

.action-button:hover {
  background: #f5f5f5;
  border-color: #ccc;
}

.action-button.a_fire svg path {
  fill: #b9b9b9;
  stroke: #111111;
  stroke-width: 4px;
}
.action-button.a_fire svg {
  width: 20px;
}
.action-button.active {
  background-color: #3c97bf;
}
.action-button.active.a_fire svg path {
  fill: #f6f5f5;
  stroke: #f8f8f8;
  stroke-width: 4px;
}

footer button {
  color: white;
}

footer .iconHeat {
  width: 30px;
  height: 30px;
  position: absolute;
  right: 120px;
  top: 15px;
  opacity: 0.3;
  transition: opacity 0.3s ease;
}

footer p.heatState {
  opacity: 0.3;
  transition: opacity 0.3s ease;
}

footer .heatState.active {
  opacity: 0.7;
  transition: opacity 0.3s ease;
}

footer button {
  /* color: white !important; */
}

footer ion-icon {
  padding: 11px;

  color: white !important;
  align-self: flex-start;
  display: flex;
  transition: all ease 0.5s;
}

footer ion-icon:hover {
  transform: rotate(20deg);
}

footer {
  display: flex;
  background: #222;
background: linear-gradient(180deg,rgba(34, 34, 34, 1) 0%, rgba(17, 52, 59, 1) 80%, rgba(34, 34, 34, 1) 100%);
  color: #fff;
  font-size: 14px;
  bottom: 0;
  position: fixed;
  left: 0;
  right: 0;
  text-align: center;
  z-index: 2000;
}

footer {
  height: 50px;
  height: 3;
}
footer .left{
transition: all ease 1s;
    display: flex;
    border-radius: 0px 0px 20px 20px;
    margin-left: 10px;
    background: #f5a402;
    background: linear-gradient(180deg, rgba(245, 164, 2, 1) 0%, rgba(232, 155, 2, 1) 30%, rgba(156, 104, 0, 1) 100%);
    flex-direction: row;
    width: 42px;
    overflow: hidden;
    color: white;
    height: 44px;

  
}
footer #ws-status {
  display: none !important;
}

footer #ws-status svg .st1_wsConnect {
  fill: #ccc;
  opacity: 0.6;
}
footer #ws-status.connected svg .st1_wsConnect {
  fill: #fb8725;
  opacity: 1;
}
footer #ws-status svg .st0_wsConnect {
  fill: #fb8725;
  opacity: 0.5;
}

footer #ws-status.ws-connected svg .st1_wsConnect {
  fill: #fb8725;
  opacity: 0.8;
}

footer i {
  color: red;
}

footer button {
  text-align: center;
  transition: all 0.3s ease-in;
  position: relative;
  text-decoration: none;
  height: 40px;
  width: 53px;
  background-color: transparent;
  margin: 0px;
  padding: 0px;
}

footer button:hover {
  background-color: rgba(185, 66, 67, 1);
}
footer .right {
  display: flex;
  position: fixed;
  right: -30px;
  flex-direction: row;
  justify-content: flex-start;

  p {
    margin-left: 12px;
  }
}

footer button:active {
  background-color: rgba(185, 66, 67, 1);
}
footer p {
  width: 30px;
  height: 30px;
  float: right !important;
  margin: 10px 0;
  svg {
    width: 30px;
    height: 30px;
  }
}

footer button svg,
footer p svg {
  transition: all ease 0.5s !important;
}

footer .a_fire svg {
  transform: scale(0.8);
}

footer button:hover svg,
footer p:hover svg {
  transform: rotate(10deg);
}

footer .a_weather img {
  width: 39px;
  margin-top: 4px;
}

footer .a_qrcode svg {
  transform: scale(0.8);
}
footer .a_qrcode svg rect {
  fill: #fff;
  stroke-linejoin: round;
}
footer .a_qrcode svg rect.ionicon-fill-none {
  stroke-width: 1;
  fill: none;
  stroke: #fff;
}

footer button svg {
  width: 41px;
  height: 35px;
  /* margin: -5px -12px; */
}
footer .usegaz svg {
  width: 35px;
  height: 35px;
  margin: 7px 2px;
}
footer .usegaz svg rect {
  stroke: #fff;
  fill: none;
  outline: #f5f5f5;
  stroke-linejoin: round;
  stroke-width: 22px;
}

footer a svg path {
  fill: rgba(250, 250, 250, 0.8);
}

footer a.usegaz {
}

footer a.usegaz.active {
  background-color: rgba(185, 66, 67, 1);
}

footer a.usegaz svg {
  width: 24px;
}

footer a:hover:after {
  position: absolute;
  background-color: red;
}

/* Loader styles */
.loader {
  position: fixed;           /* fixed zamiast absolute – zostaje w miejscu przy scrollu */
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%);
  
  width: 13%;                /* lub konkretna wartość np. 200px */
  height: 2%;                /* lub konkretna wartość np. 40px */
  
  /* margin: auto; NIE działa przy absolute/fixed bez left/right/top/bottom */
  
  z-index: 9999;             /* nie trzeba aż tylu dziewiątek, 9999 w zupełności
}

.loader svg {
  /* animation: rotate 2s linear infinite; */
}

.loader svg circle {
  /* fill: none; */
  /* stroke: #333; */
  /* stroke-width: 24; */
  /* stroke-dasharray: 383; */
  /* stroke-dashoffset: 430; */
  /* animation: dash 1.5s ease-in-out infinite; */
}

loader.loader {
  width: 65px;
  height: 30px;
  position: relative;
}
.loader:before {
  content: "";
  position: absolute;
  border-radius: 28px;
  box-shadow: 0 0 0 20px inset #2d2d2d;
  animation: l3 0.75s infinite alternate;
  fill: azure;
  /* color: gold; */
  opacity: 0.25;
}
@keyframes l3 {
  0% {
    inset: 0 35px 0 0;
  }
  50% {
    inset: 0 0 0 0;
  }
  100% {
    inset: 0 0 0 35px;
  }
}

.status-bar {
  position: fixed;
  bottom: 0;
  left: 0;
  right: 0;
  height: 80px;
  background: rgba(20, 20, 20, 0.649);
  box-shadow: 0 -2px 10px rgba(0, 0, 0, 0.1);
  display: flex;
  justify-content: flex-start;
  align-items: center;
  padding: 0 20px;
  z-index: 1000;
  flex-direction: row;
}

.status-item {
  width: 8%;
  display: flex;
  flex-direction: column;
  align-items: center;
  gap: 4px;
  font-size: 12px;
  color: #666;
  cursor: pointer;
  margin-left: 12px;
}

.status-item svg {
  outline: #ccc;
}

.status-item span {
  transition: all 0.2s ease;
}
.status-item:hover span {
  color: white;
}

.status-item.active {
  color: #ff6b00;
}

.status-item .status-icon {
  font-size: 20px;
  margin-bottom: 4px;
}

/*  */
/* .expanded .heating-indicator { */
/* top: 184px; */
/* right: 24px; */
/* } */
.heating-indicator {
  width: 8px;
  height: 8px;
  border-radius: 50%;
  background: #ff6b00;
  position: absolute;
  top: 184px;
  right: 24px;
  animation: pulse 0.9s infinite;
}

@keyframes pulse {
  0% {
    transform: scale(1);
    opacity: 1;
  }
  50% {
    transform: scale(1.5);
    opacity: 0.5;
  }
  100% {
    transform: scale(1);
    opacity: 1;
  }
}

.back-button {
  position: absolute;
  top: 15px;
  left: 17px;
  width: 32px;
  height: 32px;
  border: none;
  background: none;
  cursor: pointer;
  opacity: 0;
  transform: translateX(-10px);
  transition: all 0.3s ease;
  display: flex;
  align-items: center;
  justify-content: center;
  color: #333;
  font-size: 24px;
}

.expanded .back-button {
  opacity: 1;
  transform: translateX(0);
  color: white;
  font-weight: 900;
}

.weather-panel {
  position: fixed;
  top: 0;
  left: 0;
  right: 0;
  bottom: 80px;
  background: white;
  z-index: 200;
  padding: 24px;
  transform: translateY(100%);
  transition: transform 0.3s ease;
}

.weather-panel.visible {
  transform: translateY(0);
}

.weather-content {
  text-align: center;
  padding: 40px 20px;
}

.weather-temp {
  font-size: 72px;
  font-weight: 300;
  margin: 20px 0;
}

.weather-desc {
  font-size: 24px;
  color: #666;
  margin-bottom: 40px;
}

@keyframes expandToFullScreen {
  0% {
    transform: scale(0.4);
    opacity: 0;
  }
  50% {
    opacity: 1;
  }
  100% {
    transform: scale(1);
    opacity: 1;
  }
}

.expandToFullScreen {
  animation: expandToFullScreen 1s forwards;
}

.contractFromFullScreen {
  animation: expandToFullScreen 1s reverse forwards;
}

.box {
  width: 80px;
  height: 80px;
  background: red;
  cursor: pointer;
  transition: 1s ease-in-out;
  margin: 0 auto;
  margin-top: 100px;
}

.fullscreen {
  width: 100vw;
  height: 100vh;
  position: absolute;
  top: 0 !important;
  left: 0 !important;
  background: red;
  transition: 1s ease-in-out;
}

.contract {
  width: 80px;
  height: 80px;
  position: absolute;
  top: 100px !important;
  left: 50% !important;
  transform: translateX(-50%);
  background: red;
  transition: 1s ease-in-out;
}

.modal {
  display: none;
  position: fixed;
  z-index: 1000;
  left: 0;
  top: 0;
  width: 100%;
  height: 100%;
  background-color: rgba(0, 0, 0, 0.4);
}

.modal-content {
  background-color: #fefefe;
  margin: 15% auto;
  padding: 20px;
  border: 1px solid #888;
  width: 80%;
  max-width: 500px;
}

.close {
  color: #aaa;
  float: right;
  font-size: 28px;
  font-weight: bold;
  cursor: pointer;
}

.close:hover,
.close:focus {
  color: black;
  text-decoration: none;
  cursor: pointer;
}

#roomList div {
  margin: 10px 0;
  display: flex;
  justify-content: space-between;
  align-items: center;
}

#roomList select {
  margin-left: 10px;
  padding: 5px;
}



.scrollHandle {
  font-family: 'lcd';
}

.labelTemp {
  font-family: 'lcd';
  font-size: 10px !important;
  /* position: absolute; */
  margin-right: 4px;

}

.temp_primary {
  font-size: 1.4em;
  font-family: 'lcd';
}

.temp_secondary {
  font-family: 'lcd';
  display: flex;
  /* width: 27px; */
  font-size: 0.7em !important;

  margin-left: 2px;


}
.weather_widget .lcd {
  font-family: 'lcd', Fallback, sans-serif !important;
}
.weather_widget .ring-white{

overflow: hidden;


}
.text-3xl{
  font-family: 'lcd';
}
.upperTop {
  position: absolute;
  margin-top: -6px;
  margin-left: -7px;
  font-family: 'lcd';
  font-size: 15px;
}
@font-face {
  font-family: 'lcd';
  src: url(data:application/x-font-woff;charset=utf-8;base64,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AAAAAAAAADQAAAABAAAAAAABAAsAOwABAAAAAAACAAcANAABAAAAAAADABgAOwABAAAAAAAEAAsAOwABAAAAAAAFADAAUwABAAAAAAAGAAoAgwABAAAAAAAKAD8AjQADAAEEAwACAAwC0AADAAEEBQACABAAzAADAAEEBgACAAwA3AADAAEEBwACABAA6AADAAEECAACABAA+AADAAEECQAAAGgBCAADAAEECQABABYBfgADAAEECQACAA4BcAADAAEECQADADABfgADAAEECQAEABYBfgADAAEECQAFAGABrgADAAEECQAGABQCDgADAAEECQAKAH4CIgADAAEECgACAAwC0AADAAEECwACABACoAADAAEEDAACAAwC0AADAAEEDgACAAwC7gADAAEEEAACAA4CsAADAAEEEwACABICvgADAAEEFAACAAwC0AADAAEEFQACABAC0AADAAEEFgACAAwC0AADAAEEGQACAA4C4AADAAEEGwACABAC7gADAAEEHQACAAwC0AADAAEEHwACAAwC0AADAAEEJAACAA4C/gADAAEELQACAA4DDAADAAEICgACAAwC0AADAAEIFgACAAwC0AADAAEMCgACAAwC0AADAAEMDAACAAwC0FR5cGVmYWNlIKkgKHlvdXIgY29tcGFueSkuIDIwMTIuIEFsbCBSaWdodHMgUmVzZXJ2ZWRSZWd1bGFyYWxhcm0gY2xvY2s6VmVyc2lvbiAxLjAwVmVyc2lvbiAxLjAwIFNlcHRlbWJlciAxOSwgMjAxMiwgaW5pdGlhbCByZWxlYXNlYWxhcm1jbG9ja1RoaXMgZm9udCB3YXMgY3JlYXRlZCB1c2luZyBGb250Q3JlYXRvciA2LjUgZnJvbSBIaWdoLUxvZ2ljLmNvbQBvAGIAeQENAGUAagBuAOkAbgBvAHIAbQBhAGwAUwB0AGEAbgBkAGEAcgBkA5oDsQO9A78DvQO5A7oDrABUAHkAcABlAGYAYQBjAGUAIACpACAAKAB5AG8AdQByACAAYwBvAG0AcABhAG4AeQApAC4AIAAyADAAMQAyAC4AIABBAGwAbAAgAFIAaQBnAGgAdABzACAAUgBlAHMAZQByAHYAZQBkAFIAZQBnAHUAbABhAHIAYQBsAGEAcgBtACAAYwBsAG8AYwBrADoAVgBlAHIAcwBpAG8AbgAgADEALgAwADAAVgBlAHIAcwBpAG8AbgAgADEALgAwADAAIABTAGUAcAB0AGUAbQBiAGUAcgAgADEAOQAsACAAMgAwADEAMgAsACAAaQBuAGkAdABpAGEAbAAgAHIAZQBsAGUAYQBzAGUAYQBsAGEAcgBtAGMAbABvAGMAawBUAGgAaQBzACAAZgBvAG4AdAAgAHcAYQBzACAAYwByAGUAYQB0AGUAZAAgAHUAcwBpAG4AZwAgAEYAbwBuAHQAQwByAGUAYQB0AG8AcgAgADYALgA1ACAAZgByAG8AbQAgAEgAaQBnAGgALQBMAG8AZwBpAGMALgBjAG8AbQBOAG8AcgBtAGEAYQBsAGkATgBvAHIAbQBhAGwAZQBTAHQAYQBuAGQAYQBhAHIAZABOAG8AcgBtAGEAbABuAHkEHgQxBEsERwQ9BEsEOQBOAG8AcgBtAOEAbABuAGUATgBhAHYAYQBkAG4AbwBBAHIAcgB1AG4AdABhAAIAAAAAAAD/JwCWAAAAAAAAAAAAAAAAAAAAAAAAAAAA7AAAAAEAAgADAAQABQAGAAcACAAJAAoACwAMAA0ADgAPABAAEQASABMAFAAVABYAFwAYABkAGgAbABwAHQAeAB8AIAAhACIAIwAkACUAJgAnACgAKQAqACsALAAtAC4ALwAwADEAMgAzADQANQA2ADcAOAA5ADoAOwA8AD0APgA/AEAAQQBCAEMARABFAEYARwBIAEkASgBLAEwATQBOAE8AUABRAFIAUwBUAFUAVgBXAFgAWQBaAFsAXABdAF4AXwBgAGEAowCEAIUAvQCWAOgAhgCOAIsAnQCpAKQAigDaAIMAkwECAQMAjQCXAIgAwwDeAQQAngCqAPUA9AD2AKIArQDJAMcArgBiAGMAkABkAMsAZQDIAMoAzwDMAM0AzgDpAGYA0wDQANEArwBnAPAAkQDWANQA1QBoAOsA7QCJAGoAaQBrAG0AbABuAKAAbwBxAHAAcgBzAHUAdAB2AHcA6gB4AHoAeQB7AH0AfAC4AKEAfwB+AIAAgQDsAO4AugDXANgA4QEFANsA3ADdAOAA2QDfALIAswC2ALcAxAC0ALUAxQCCAMIAhwCrAL4AvwC8APcBBgEHAQgBCQCMAJgAqACaAJkA7wClAJIAnACnAJQAlQEKAQsHdW5pMDBCMgd1bmkwMEIzB3VuaTAwQjkHdW5pMDJDOQRsaXJhBnBlc2V0YQRFdXJvCWFmaWk2MTM1Mgd1bmlGMDAxB3VuaUYwMDIAAAAAAAAB//8AAg==) format('woff');


}</style>
    <style type="text/css">/* Modal */
.modal {
  display: none;
  position: fixed;
  z-index: 1;
  left: 0;
  top: 0;
  width: 100%;
  height: 100%;
  overflow: auto;
  background-color: rgba(0, 0, 0, 0.4);

}

/* 
.modal-content {
  background-color: #fefefe;
  margin: 15% auto;
  padding: 20px;
  border: 1px solid #888;
  width: 80%;
  max-width: 500px;
} */



/* Style dla zakładek */
.config-tabs {
  display: flex;
  justify-content: center;
  margin-bottom: 15px;
}

.tab-button {
  padding: 8px 15px;
  margin: 0 5px;
  border: none;
  background-color: #f0f0f0;
  border-radius: 5px;
  cursor: pointer;
  transition: all 0.3s ease;
}

.tab-button.active {
  background-color: #474E65;
  color: white;
}

.tab-content {
  transition: all 0.3s ease;
}

/* Style dla edycji pokoi */



.modal-content {
    -webkit-box-shadow: 0px 0px 73px 15px rgba(66, 68, 90, 0.44);
    -moz-box-shadow: 0px 0px 73px 15px rgba(66, 68, 90, 0.44);
    box-shadow: 0px 0px 73px 15px rgba(66, 68, 90, 0.44);
    
    border-radius: 16px;
  background-color: #fefefeed;
  margin: 15% auto;
  padding: 20px;
  border: 1px solid #888;
  width: 80%;

  /* make opacity animation fade in  */
    animation: fadeIn 0.5s;

}


.close {
  color: #aaa;
  float: right;
  font-size: 28px;
  font-weight: bold;
}

.close:hover,
.close:focus {
  color: black;
  text-decoration: none;
  cursor: pointer;
}
hr {
  border: 1px solid #a5a5a510;
  margin-bottom: 20px;
}

button.cancel {
  background-color: #f44336;
  color: white;
  padding: 14px 20px;
  margin: 8px 0;
  border: none;
  cursor: pointer;
  width: 100%;
  border-radius: 12px;
  width: 25%;
}
button.confirm {
  background-color: #4CAF50;
  color: white;
  padding: 14px 20px;
  margin: 8px 0;
  border: none;
  cursor: pointer;
  width: 100%;
  border-radius: 12px;
  width: 25%;
  float: right;
}
button {
  background-color: #445A7D;
  color: white;
  padding: 14px 20px;
  margin: 8px 0;
  border: none;
  cursor: pointer;
  width: 100%;
  border-radius: 12px;
  width: 25%;
}</style>

    <!-- <script type="module" src="https://unpkg.com/ionicons@4.5.10-0/dist/ionicons/ionicons.esm.js"></script>
    <script nomodule="" src="https://unpkg.com/ionicons@4.5.10-0/dist/ionicons/ionicons.js"></script> -->

    <script src="//cdnjs.cloudflare.com/ajax/libs/qrcodejs/1.0.0/qrcode.min.js"></script>
    <script src="//cdn.jsdelivr.net/npm/dayjs@1/dayjs.min.js"></script>
    <script src="//cdn.jsdelivr.net/npm/dayjs@1/locale/pl.js"></script>
    <script>
      dayjs.locale("pl");
    </script>
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
    <script src="https://cdn.jsdelivr.net/npm/swiper@11/swiper-bundle.min.js"></script>
    <link
      href="//fonts.googleapis.com/css?family=Open+Sans:400,700,300,600|Open+Sans+Condensed:300,700"
      rel="stylesheet"
      type="text/css"
    />
    <link
      href="//cdn.jsdelivr.net/npm/swiper@11/swiper-bundle.min.css"
      rel="stylesheet"
    />
    <script src="https://cdn.tailwindcss.com"></script>

    <!-- FAVICON GENERATION  -->
    <link
      href="data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHZlcnNpb249IjEuMSIgeG1sbnM6eGxpbms9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkveGxpbmsiIHhtbG5zOnN2Z2pzPSJodHRwOi8vc3ZnanMuZGV2L3N2Z2pzIiB3aWR0aD0iNjY0LjAyIiBoZWlnaHQ9IjY2My43NyI+PHN2ZyBpZD0iU3ZnanNTdmcxMDAxIiBkYXRhLW5hbWU9ImZhdmljb25uIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHZpZXdCb3g9IjAgMCA2NjQuMDIgNjYzLjc3Ij4KICAKICA8cGF0aCBmaWxsPSIjZjM2ZDI0IiBkPSJNODkuMjksNTU4LjMzQy04NC40MiwzNzEuODgsOC4zMyw2Ny4wMSwyNTUuMTUsOS4wOWMyNTIuODYtNTkuMzQsNDczLjc3LDE4MS45NywzOTEuMzEsNDI4LjY5LTc5LjI5LDIzNy4yNy0zODUuNzQsMzA0LjU1LTU1Ny4xNywxMjAuNTZaTTEzOS4yNCw1MzkuNDFjMTU1LjIxLDE0My40Miw0MDcuNDQsNzIuNDEsNDY0LjY0LTEyOS45MUM2NjYuNiwxODcuNjIsNDUwLjY2LTEyLjk5LDIzMy45Miw2Ni41OCwzNy4wOCwxMzguODUtMTUuNiwzOTYuMzQsMTM5LjI0LDUzOS40MVoiPjwvcGF0aD4KICA8cGF0aCBmaWxsPSIjZjM2ZDI0IiBkPSJNMzcxLjc4LDExNC44OWMtMTYuMDMtMTUuNzMtNDMuNDYtMTQuMzMtNTcuNTEsMy4yOCw0LjU5LDUuOTksMTAuMDQsMTEuMTYsMTQuMzIsMTcuNDMsMTQuMTUsMjAuNzcsMjMuMTcsNTEuMjMsMjQuNiw3Ni4yOCw0LjQ4LDc4LjU1LTYzLjgzLDExNS44Ny04NS40NCwxODUuMzItMTMuMTIsNDIuMTctNi4wNSwxMDUuMjYsMTUuOTYsMTQzLjg1LDE0LjU3LDI1LjU2LDQ2LjA3LDMwLjkyLDY1LjM3LDcuNjEtMjMuNTEtMjMuMTUtMzYuODUtNTkuMjgtMzguODctOTIuMDQtNS41My04OS43Niw4NS42LTEzMC4xLDkxLjg3LTIxNy43NCwyLjI2LTMxLjYxLTYuODYtMTAwLjk3LTMwLjMtMTIzLjk5Wk00NjcuNzUsMTMxLjc2Yy03Ljc3LDEuMjEtMTYuNjIsNy4zNC0yMS42NywxMy4yNCwxOC45MywyMC4yOCwyOS43Nyw0OS4xMSwzMC45Niw3Ni44NywyLjIyLDUxLjQxLTQ2LjczLDg4LjE0LTY4LjE2LDEzMS42OS0xOS45NCw0MC41My0xOS4xNCw5MS4yNy0xLjI3LDEzMi41MSwxMi42OCwyOS4yNSw0Mi44MywzNy4zOCw2NS4zMiwxMy4zOC0xOC4yNS0yMC44OS0yOC4yOC00OC4wNy0yOS44OC03NS43OC0zLjY4LTYzLjkyLDYzLjY3LTEwMy41Nyw3OS4xOC0xNjQuNTEsOS4zOS0zNi45MiwyLjMyLTEzNi4yMy01NC40OC0xMjcuMzlaTTIzMi4wOSwxMzIuODFjLTguODMuNzYtMTcuNTEsNS4wMy0yMy42MywxMS4zMiw4LjQxLDEyLjcyLDE1LjMxLDI0LjQsMTkuMzQsMzkuMzMsOS45NiwzNi45LDUuMDIsNjQuMzktMTcuMDYsOTQuNzktMjUuMywzNC44My01OS42NCw2Mi4zMi03MS44MywxMDUuOTYtNy45LDI4LjI5LTcuMDksODUuNTMsOS4wNywxMTAuNzgsMTIuNDIsMTkuNDEsNDMuNDIsMjIuNDcsNTguMjgsNC40NC0xOS43My0yNC40NS0yNS40MS01Ni44Ny0yMi44OS04Ny43NCw0LjAxLTQ5LjA0LDcwLjcyLTk0LjAxLDg5LjY0LTE0NC4wOCwxMy4xOS0zNC45LDE1Ljk4LTEzOS42OC00MC45My0xMzQuODFaIj48L3BhdGg+CiAgPHBhdGggZmlsbD0iI2YzNmQyNCIgZD0iTTM3MS43OCwxMTQuODljMjMuNDQsMjMuMDEsMzIuNTYsOTIuMzgsMzAuMywxMjMuOTktNi4yNiw4Ny42NS05Ny40LDEyNy45OC05MS44NywyMTcuNzQsMi4wMiwzMi43NSwxNS4zNiw2OC44OCwzOC44Nyw5Mi4wNC0xOS4zMSwyMy4zMi01MC44LDE3Ljk1LTY1LjM3LTcuNjEtMjItMzguNTktMjkuMDgtMTAxLjY4LTE1Ljk2LTE0My44NSwyMS42MS02OS40Niw4OS45Mi0xMDYuNzcsODUuNDQtMTg1LjMyLTEuNDMtMjUuMDUtMTAuNDUtNTUuNTEtMjQuNi03Ni4yOC00LjI4LTYuMjgtOS43My0xMS40NC0xNC4zMi0xNy40MywxNC4wNC0xNy42MSw0MS40OC0xOS4wMSw1Ny41MS0zLjI4WiI+PC9wYXRoPgogIDxwYXRoIGZpbGw9IiNmMzZkMjQiIGQ9Ik0yMzIuMDksMTMyLjgxYzU2LjkxLTQuODcsNTQuMTEsOTkuOTEsNDAuOTMsMTM0LjgxLTE4LjkyLDUwLjA3LTg1LjY0LDk1LjA0LTg5LjY0LDE0NC4wOC0yLjUyLDMwLjg3LDMuMTUsNjMuMjksMjIuODksODcuNzQtMTQuODYsMTguMDMtNDUuODYsMTQuOTctNTguMjgtNC40NC0xNi4xNi0yNS4yNS0xNi45Ny04Mi40OS05LjA3LTExMC43OCwxMi4xOC00My42NCw0Ni41My03MS4xMyw3MS44My0xMDUuOTYsMjIuMDgtMzAuNCwyNy4wMi01Ny44OSwxNy4wNi05NC43OS00LjAzLTE0LjkzLTEwLjkzLTI2LjYxLTE5LjM0LTM5LjMzLDYuMTItNi4yOSwxNC44LTEwLjU2LDIzLjYzLTExLjMyWiI+PC9wYXRoPgogIDxwYXRoIGZpbGw9IiNmMzZkMjQiIGQ9Ik00NjcuNzUsMTMxLjc2YzU2LjgtOC44NCw2My44Nyw5MC40Nyw1NC40OCwxMjcuMzktMTUuNTEsNjAuOTQtODIuODYsMTAwLjU5LTc5LjE4LDE2NC41MSwxLjYsMjcuNzEsMTEuNjMsNTQuOSwyOS44OCw3NS43OC0yMi40OSwyNC01Mi42NCwxNS44Ny02NS4zMi0xMy4zOC0xNy44Ny00MS4yMy0xOC42OC05MS45OCwxLjI3LTEzMi41MSwyMS40My00My41NCw3MC4zOC04MC4yNyw2OC4xNi0xMzEuNjktMS4yLTI3Ljc2LTEyLjAzLTU2LjU5LTMwLjk2LTc2Ljg3LDUuMDUtNS45LDEzLjktMTIuMDQsMjEuNjctMTMuMjRaIj48L3BhdGg+Cjwvc3ZnPjxzdHlsZT5AbWVkaWEgKHByZWZlcnMtY29sb3Itc2NoZW1lOiBsaWdodCkgeyA6cm9vdCB7IGZpbHRlcjogbm9uZTsgfSB9CkBtZWRpYSAocHJlZmVycy1jb2xvci1zY2hlbWU6IGRhcmspIHsgOnJvb3QgeyBmaWx0ZXI6IG5vbmU7IH0gfQo8L3N0eWxlPjwvc3ZnPg=="
      rel="icon"
      type="image/svg+xml"
    />
    <!-- FAVICON GENERATION  -->
  </head>
  <body class="">
    <div id="loader" class="loader">
      <!-- <svg width="100" height="100" viewBox="0 0 100 100">
            <circle cx="50" cy="50" r="45"></circle>
        </svg> -->
    </div>

    <div class="container">
      <div id="thermostat-list"></div>

      <div class="imageBack_container">
        <svg xmlns="//www.w3.org/2000/svg" viewBox="0 0 88.02 64.13">
          <defs>
            <style>
              .cls-1 {
                fill: #fff;
                stroke-width: 0px;
              }
            </style>
          </defs>
          <path
            class="cls-1"
            d="m28.1,8.34c.26,0,.51-.1.71-.29l4.63-4.63v10.07c0,.42.27.8.67.94,1.41.5,3.33,1.19,3.33,1.91s-1.93,1.41-3.34,1.91c-2.19.78-4.66,1.66-4.66,3.79s2.48,3.01,4.67,3.79c1.41.5,3.33,1.19,3.33,1.9s-1.93,1.4-3.33,1.9c-2.19.78-4.67,1.66-4.67,3.79,0,1.9,1.98,2.81,3.83,3.49v6.01c0,.55.45,1,1,1s1-.45,1-1v-6.72c0-.42-.27-.8-.67-.94-1.18-.42-3.17-1.13-3.17-1.84s1.93-1.4,3.33-1.9c2.19-.78,4.67-1.66,4.67-3.79s-2.48-3.01-4.67-3.79c-1.41-.5-3.33-1.19-3.33-1.9s1.93-1.41,3.34-1.91c2.19-.78,4.66-1.66,4.66-3.79,0-1.92-2.01-2.82-4-3.55V3.41l4.62,4.62c.39.39,1.02.39,1.41,0s.39-1.02,0-1.41L35.14.29c-.09-.09-.2-.17-.33-.22-.24-.1-.52-.1-.76,0-.12.05-.23.12-.33.22l-6.33,6.34c-.39.39-.39,1.02,0,1.41.2.2.45.29.71.29Z"
          ></path>
          <path
            class="cls-1"
            d="m47.97,8.03l4.62-4.62v9.37c-1.99.73-4,1.64-4,3.55,0,2.13,2.48,3.01,4.66,3.79,1.41.5,3.34,1.19,3.34,1.91s-1.93,1.4-3.33,1.9c-2.19.78-4.67,1.66-4.67,3.79s2.48,3.01,4.67,3.79c1.41.5,3.33,1.19,3.33,1.9s-1.98,1.42-3.17,1.84c-.4.14-.67.52-.67.94v6.72c0,.55.45,1,1,1s1-.45,1-1v-6.01c1.85-.68,3.83-1.59,3.83-3.49,0-2.13-2.48-3.01-4.67-3.79-1.41-.5-3.33-1.19-3.33-1.9s1.93-1.4,3.33-1.9c2.19-.78,4.67-1.66,4.67-3.79s-2.48-3.01-4.66-3.79c-1.41-.5-3.34-1.19-3.34-1.91s1.93-1.41,3.33-1.91c.4-.14.67-.52.67-.94V3.41l4.63,4.63c.2.2.45.29.71.29s.51-.1.71-.29c.39-.39.39-1.02,0-1.41L54.3.29c-.09-.09-.2-.17-.33-.22-.24-.1-.52-.1-.76,0-.12.05-.23.12-.33.22l-6.33,6.32c-.39.39-.39,1.02,0,1.41s1.02.39,1.41,0Z"
          ></path>
          <g>
            <path
              class="cls-1"
              d="M50.43,62.22c-.48-.28-1.09-.11-1.37.37-.28.48-.11,1.09.37,1.37l.31.18h4l-3.31-1.91Z"
            ></path>
            <path
              class="cls-1"
              d="m.5,35.7l43.01,24.83c.15.09.33.13.5.13s.35-.04.5-.13l8.1-4.68,14.33,8.27h3.93c-.17-.13-.36-.25-.56-.36l-15.7-9.07,6.6-3.81,16.7,9.64c1.35.78,3.07,1.17,4.8,1.17s3.45-.39,4.8-1.17c.48-.28.64-.89.37-1.37-.28-.48-.89-.64-1.37-.37-2.06,1.19-5.54,1.19-7.6,0l-15.7-9.07,24.31-14.03c.31-.18.5-.51.5-.87s-.19-.69-.5-.87l-22.3-12.88c-.48-.28-1.09-.11-1.37.37-.28.48-.11,1.09.37,1.37l20.8,12.01-41.01,23.68L3,34.83l20-11.55c.48-.28.64-.89.37-1.37-.28-.48-.89-.64-1.37-.37L.5,33.97C.19,34.15,0,34.48,0,34.83s.19.69.5.87Z"
            ></path>
          </g>
          <g>
            <path
              class="cls-1"
              d="m17.7,55.57l14.83,8.56h4l-17.83-10.3c-.81-.47-1.28-1.06-1.28-1.62s.47-1.15,1.28-1.62c.48-.28.64-.89.37-1.37-.28-.48-.89-.64-1.37-.37-1.47.85-2.28,2.04-2.28,3.35s.81,2.5,2.28,3.35Z"
            ></path>
            <path
              class="cls-1"
              d="m1.5,60.53c2.06-1.19,5.54-1.19,7.6,0l6.23,3.6h4l-9.23-5.33c-2.69-1.55-6.91-1.55-9.6,0-.48.28-.64.89-.37,1.37.28.48.89.64,1.37.37Z"
            ></path>
          </g>
        </svg>
      </div>

      <footer>
        <button href="#" class="noselect configButton">
          <div class="icon-inner">
            <svg
              xmlns="http://www.w3.org/2000/svg"
              class="ionicon s-ion-icon"
              viewBox="0 0 512 512"
            >
              <title>Ustawienia</title>
              <path
                d="M456.7 242.27l-26.08-4.2a8 8 0 01-6.6-6.82c-.5-3.2-1-6.41-1.7-9.51a8.08 8.08 0 013.9-8.62l23.09-12.82a8.05 8.05 0 003.9-9.92l-4-11a7.94 7.94 0 00-9.4-5l-25.89 5a8 8 0 01-8.59-4.11q-2.25-4.2-4.8-8.41a8.16 8.16 0 01.7-9.52l17.29-19.94a8 8 0 00.3-10.62l-7.49-9a7.88 7.88 0 00-10.5-1.51l-22.69 13.63a8 8 0 01-9.39-.9c-2.4-2.11-4.9-4.21-7.4-6.22a8 8 0 01-2.5-9.11l9.4-24.75A8 8 0 00365 78.77l-10.2-5.91a8 8 0 00-10.39 2.21l-16.64 20.84a7.15 7.15 0 01-8.5 2.5s-5.6-2.3-9.8-3.71A8 8 0 01304 87l.4-26.45a8.07 8.07 0 00-6.6-8.42l-11.59-2a8.07 8.07 0 00-9.1 5.61l-8.6 25.05a8 8 0 01-7.79 5.41h-9.8a8.07 8.07 0 01-7.79-5.41l-8.6-25.05a8.07 8.07 0 00-9.1-5.61l-11.59 2a8.07 8.07 0 00-6.6 8.42l.4 26.45a8 8 0 01-5.49 7.71c-2.3.9-7.3 2.81-9.7 3.71-2.8 1-6.1.2-8.8-2.91l-16.51-20.34A8 8 0 00156.75 73l-10.2 5.91a7.94 7.94 0 00-3.3 10.09l9.4 24.75a8.06 8.06 0 01-2.5 9.11c-2.5 2-5 4.11-7.4 6.22a8 8 0 01-9.39.9L111 116.14a8 8 0 00-10.5 1.51l-7.49 9a8 8 0 00.3 10.62l17.29 19.94a8 8 0 01.7 9.52q-2.55 4-4.8 8.41a8.11 8.11 0 01-8.59 4.11l-25.89-5a8 8 0 00-9.4 5l-4 11a8.05 8.05 0 003.9 9.92L85.58 213a7.94 7.94 0 013.9 8.62c-.6 3.2-1.2 6.31-1.7 9.51a8.08 8.08 0 01-6.6 6.82l-26.08 4.2a8.09 8.09 0 00-7.1 7.92v11.72a7.86 7.86 0 007.1 7.92l26.08 4.2a8 8 0 016.6 6.82c.5 3.2 1 6.41 1.7 9.51a8.08 8.08 0 01-3.9 8.62L62.49 311.7a8.05 8.05 0 00-3.9 9.92l4 11a7.94 7.94 0 009.4 5l25.89-5a8 8 0 018.59 4.11q2.25 4.2 4.8 8.41a8.16 8.16 0 01-.7 9.52l-17.29 19.96a8 8 0 00-.3 10.62l7.49 9a7.88 7.88 0 0010.5 1.51l22.69-13.63a8 8 0 019.39.9c2.4 2.11 4.9 4.21 7.4 6.22a8 8 0 012.5 9.11l-9.4 24.75a8 8 0 003.3 10.12l10.2 5.91a8 8 0 0010.39-2.21l16.79-20.64c2.1-2.6 5.5-3.7 8.2-2.6 3.4 1.4 5.7 2.2 9.9 3.61a8 8 0 015.49 7.71l-.4 26.45a8.07 8.07 0 006.6 8.42l11.59 2a8.07 8.07 0 009.1-5.61l8.6-25a8 8 0 017.79-5.41h9.8a8.07 8.07 0 017.79 5.41l8.6 25a8.07 8.07 0 009.1 5.61l11.59-2a8.07 8.07 0 006.6-8.42l-.4-26.45a8 8 0 015.49-7.71c4.2-1.41 7-2.51 9.6-3.51s5.8-1 8.3 2.1l17 20.94A8 8 0 00355 439l10.2-5.91a7.93 7.93 0 003.3-10.12l-9.4-24.75a8.08 8.08 0 012.5-9.12c2.5-2 5-4.1 7.4-6.21a8 8 0 019.39-.9L401 395.66a8 8 0 0010.5-1.51l7.49-9a8 8 0 00-.3-10.62l-17.29-19.94a8 8 0 01-.7-9.52q2.55-4.05 4.8-8.41a8.11 8.11 0 018.59-4.11l25.89 5a8 8 0 009.4-5l4-11a8.05 8.05 0 00-3.9-9.92l-23.09-12.82a7.94 7.94 0 01-3.9-8.62c.6-3.2 1.2-6.31 1.7-9.51a8.08 8.08 0 016.6-6.82l26.08-4.2a8.09 8.09 0 007.1-7.92V250a8.25 8.25 0 00-7.27-7.73zM256 112a143.82 143.82 0 01139.38 108.12A16 16 0 01379.85 240H274.61a16 16 0 01-13.91-8.09l-52.1-91.71a16 16 0 019.85-23.39A146.94 146.94 0 01256 112zM112 256a144 144 0 0143.65-103.41 16 16 0 0125.17 3.47L233.06 248a16 16 0 010 15.87l-52.67 91.7a16 16 0 01-25.18 3.36A143.94 143.94 0 01112 256zm144 144a146.9 146.9 0 01-38.19-4.95 16 16 0 01-9.76-23.44l52.58-91.55a16 16 0 0113.88-8H379.9a16 16 0 0115.52 19.88A143.84 143.84 0 01256 400z"
              ></path>
            </svg>
          </div>
        </button>

        <button href="#" class="noselect usegaz" id="useGazButton">
          <div class="icon-inner">
            <svg
              xmlns="http://www.w3.org/2000/svg"
              class="ionicon s-ion-icon"
              viewBox="0 0 512 512"
            >
              <title>Włącz piecyk gazowy</title>
              <rect
                x="48"
                y="48"
                width="416"
                height="416"
                rx="96"
                stroke-linejoin="round"
                class="ionicon-fill-none ionicon-stroke-width"
              ></rect>
              <path
                d="M388.94 151.56c-24.46-22.28-68.72-51.4-132.94-51.4s-108.48 29.12-132.94 51.4a34.66 34.66 0 00-3.06 48.08l33.32 39.21a26.07 26.07 0 0033.6 5.21c15.92-9.83 40.91-21.64 69.1-21.64s53.18 11.81 69.1 21.64a26.07 26.07 0 0033.6-5.21L392 199.64a34.66 34.66 0 00-3.06-48.08z"
                stroke-linejoin="round"
                class="ionicon-fill-none ionicon-stroke-width"
              ></path>
            </svg>
          </div>
        </button>

        <button class="noselect a_fire">
          <div class="manifoldTemp">0.0</div>
          <div class="icon-inner">
            <svg
              xmlns="http://www.w3.org/2000/svg"
              class="ionicon s-ion-icon"
              viewBox="0 0 512 512"
            >
              <title>Kominek działa</title>
              <path
                d="M273.38 368.33c-.81-9.23-8.86-16.44-18.55-16.44a18.63 18.63 0 00-18.2 14.11l-18.2 88.38a35.75 35.75 0 00-.93 7.88c0 19.93 16.68 33.78 37.33 33.78s37.34-13.85 37.34-33.78a36.16 36.16 0 00-1.29-9.45zM411.05 407.86a41.78 41.78 0 00-5.95-4.35l-69.53-48.59c-6.77-4.25-14-4.13-19.25 1a13.53 13.53 0 00-2 17.2l52.5 69a36.57 36.57 0 004 4.69c9.1 10.17 29.28 10.73 40.37 0 10.94-10.91 10.81-30.35-.14-38.95zM463.3 335.88h-70.42c-4.55 0-8.88 3.35-8.88 8.16s2.95 7.85 6.92 9.16l66.43 20.55C467 376 480 367.4 480 356.66c0-13.66-7.6-20.78-16.7-20.78zM128.22 344c0-5-4.55-8.16-9.45-8.16H48.35c-8.87 0-16.35 9.58-16.35 20.32S44.62 376 54.3 373.75l67.43-20.55c4.39-1.31 6.49-4.2 6.49-9.2zM176.55 355L107 403.38a32.34 32.34 0 00-6 4.35 26.33 26.33 0 000 38.56 29.39 29.39 0 0040.36 0 30.75 30.75 0 004-4.68L197.9 373c3.5-5.58 2.92-12.49-2-17.06a15 15 0 00-19.35-.94z"
              ></path>
              <path
                d="M368 125.09c0-55.7-49.22-89.16-94.2-93.06a8 8 0 00-8.69 7.71c-3.12 76-109.38 110.69-119.87 178.68-7 45.4 16.65 72.37 34.31 85.78a15.94 15.94 0 0023.93-5.62c22.5-45.86 74.33-63.49 109.72-85.94 42.88-27.2 54.8-56.44 54.8-87.55z"
                stroke-linecap="round"
                stroke-miterlimit="10"
                class="ionicon-fill-none ionicon-stroke-width"
              ></path>
              <path
                d="M240 95.7c-12.82-23-30.51-31-59.16-31.63a3.86 3.86 0 00-4.06 3.51c-.95 34.22-32.78 44.85-32.78 73.15 0 19.37 5.39 29 17.16 39.28M352.45 178.76c8.6 14.31 15.55 30.08 15.55 48 0 52.52-42.47 93.1-94.86 93.1a94.42 94.42 0 01-65.14-26"
                stroke-linecap="round"
                stroke-miterlimit="10"
                class="ionicon-fill-none ionicon-stroke-width"
              ></path>
            </svg>
          </div>
        </button>

        <button href="#" class="noselect a_weather" style="position: relative">
          <div
            class="weather-temp"
            style="
              font-size: 10px;
              font-weight: bold;
              position: absolute;
              top: 2px;
              width: 100%;
              text-align: center;
              color: #fff;
              text-shadow: 1px 1px 2px black;
            "
          ></div>
          <img
            src="https://openweathermap.org/img/wn/04d@2x.png"
            alt="Prognoza pogody"
          />
        </button>
        <button href="#" class="noselect a_qrcode">
          <div class="icon-inner">
            <svg
              xmlns="http://www.w3.org/2000/svg"
              class="ionicon s-ion-icon"
              viewBox="0 0 512 512"
            >
              <title>Qr Code</title>
              <rect x="336" y="336" width="80" height="80" rx="8" ry="8"></rect>
              <rect x="272" y="272" width="64" height="64" rx="8" ry="8"></rect>
              <rect x="416" y="416" width="64" height="64" rx="8" ry="8"></rect>
              <rect x="432" y="272" width="48" height="48" rx="8" ry="8"></rect>
              <rect x="272" y="432" width="48" height="48" rx="8" ry="8"></rect>
              <rect x="336" y="96" width="80" height="80" rx="8" ry="8"></rect>
              <rect
                x="288"
                y="48"
                width="176"
                height="176"
                rx="16"
                ry="16"
                stroke-linecap="round"
                stroke-linejoin="round"
                class="ionicon-fill-none ionicon-stroke-width"
              ></rect>
              <rect x="96" y="96" width="80" height="80" rx="8" ry="8"></rect>
              <rect
                x="48"
                y="48"
                width="176"
                height="176"
                rx="16"
                ry="16"
                stroke-linecap="round"
                stroke-linejoin="round"
                class="ionicon-fill-none ionicon-stroke-width"
              ></rect>
              <rect x="96" y="336" width="80" height="80" rx="8" ry="8"></rect>
              <rect
                x="48"
                y="288"
                width="176"
                height="176"
                rx="16"
                ry="16"
                stroke-linecap="round"
                stroke-linejoin="round"
                class="ionicon-fill-none ionicon-stroke-width"
              ></rect>
            </svg>
          </div>
        </button>

        <div class="right">
          <p class="heatState">
            <svg
              class="iconHeat"
              version="1.1"
              xmlns="//www.w3.org/2000/svg"
              xmlns:xlink="//www.w3.org/1999/xlink"
              x="0px"
              y="0px"
              width="980px"
              height="778.2px"
              viewBox="0 0 980 778.2"
              style="overflow: visible; enable-background: new 0 0 980 778.2"
              xml:space="preserve"
            >
              <style type="text/css">
                .st0 {
                  fill: #fd8300;
                }
              </style>
              <defs></defs>
              <g>
                <g
                  transform="translate(0.000000,511.000000) scale(0.100000,-0.100000)"
                >
                  <path
                    class="st0"
                    d="M8845.3,4724.7c480.4-579.6,456.6-492.3,206.5-766.2c-369.2-397-500.2-913.1-369.2-1429.2
                   c75.4-301.7,246.2-678.9,412.9-921.1c345.3-504.2,619.3-1238.7,686.8-1854.1c71.5-623.3-75.4-1250.6-401-1742.9
                   c-166.8-246.2-611.4-698.8-670.9-674.9c-39.7,11.9-718.6,889.3-718.6,929c0,11.9,43.7,55.6,91.3,99.3
                   c170.7,131,381.1,484.4,448.6,750.4c131,516.1-15.9,1079.9-484.4,1869.9c-536,905.2-730.5,1679.4-603.4,2386
                   c75.4,412.9,202.5,726.5,408.9,1044.1c166.8,250.1,571.7,694.8,635.2,694.8C8511.9,5109.8,8670.7,4935.1,8845.3,4724.7z"
                  />
                  <path
                    class="st0"
                    d="M5184.9,4665.1l377.2-444.6l-198.5-222.3c-285.8-317.6-397-579.6-420.8-952.8
                   c-27.8-504.2,87.3-861.5,492.3-1516.6c258-420.9,412.8-762.3,539.9-1206.9c71.5-254.1,91.3-412.9,91.3-849.6
                   c0-619.3-71.5-913.1-325.6-1349.8c-150.9-254.1-639.2-794-718.6-794c-23.8,0-206.4,210.4-401,472.5l-357.3,468.5l178.7,174.7
                   c99.3,95.3,226.3,274,285.9,393.1c99.2,198.5,107.2,258.1,103.2,674.9c0,555.8-71.5,770.2-492.3,1468.9
                   c-488.3,821.8-663,1409.4-623.3,2124C3751.7,3780,3989.9,4308,4490.2,4840c138.9,146.9,270,270,289.8,270
                   C4795.9,5109.8,4982.4,4907.3,5184.9,4665.1z"
                  />
                  <path
                    class="st0"
                    d="M1441.1,4704.8c186.6-222.3,353.3-428.8,369.2-456.6c23.8-39.7-19.9-115.1-139-242.2
                   c-238.2-258.1-337.5-428.8-412.9-726.5c-123.1-484.3,7.9-1000.5,440.7-1707.1c484.4-794,667-1365.7,671-2100.2
                   c0-532-67.5-833.7-285.9-1250.6c-142.9-274-682.9-893.3-778.2-893.3c-35.7,0-595.5,702.7-706.7,893.3
                   c-15.9,27.8,43.7,123,154.8,238.2c337.5,353.4,464.5,813.9,373.2,1349.8c-63.5,365.3-186.6,655.1-512.1,1202.9
                   C158.8,1782.9,0,2283.1,0,2946.1c0,591.5,146.9,1056,496.3,1556.3c150.9,222.3,516.1,607.4,571.7,607.4
                   C1087.8,5109.8,1258.5,4927.2,1441.1,4704.8z"
                  />
                </g>
              </g>
            </svg>
          </p>

          <p id="ws-status">
            <svg
              class="ws_connect_icon"
              xmlns="http://www.w3.org/2000/svg"
              version="1.1"
              viewBox="0 0 63.54 63.65"
            >
              <path
                class="st0_wsConnect"
                d="M63.54,31.77c.23,22.22-22.28,37.65-43.12,29.62-2.68-1.03-5.15-2.52-7.51-4.12l-6.41,6.38-.48-.1-6.01-6.07,6.45-6.67C-6.35,33.61,1.32,8.71,21.57,1.77,24.8.67,28.1.27,31.49,0c.16-.04.46.2.46.28v8.61l-.32.26c-7.67.08-14.84,4.13-18.9,10.57-6.3,9.99-3.83,23.32,5.65,30.31,13.66,10.07,33.21,2.1,35.91-14.59.17-1.04.09-2.32.25-3.2.04-.21.1-.36.29-.48h8.71Z"
              />
              <path
                class="st1_wsConnect"
                d="M51.03,6.33c.17-.04.31-.06.45.07l5.84,5.84.07.45-13.1,13.15c.27,1.29.79,2.47,1,3.78,1.91,11.71-11.12,20.14-20.98,13.52-12.37-8.31-4.28-28.02,11.05-24.45.55.13,2.2.87,2.52.74l13.15-13.1ZM35.14,28.59c-2.31-2.31-6.57-1.37-7.53,1.8-1.47,4.81,4.58,8.11,7.79,4.34,1.45-1.7,1.31-4.58-.26-6.15Z"
              />
            </svg>
          </p>

          <p class="console noselect"></p>
        </div>
      </footer>
    </div>

    <!-- Weather Modal Structure (Restored from Old Version) -->
    <div class="ifdata">
      <div
        class="container-modal"
        style="
          display: none;
          position: fixed;
          top: 0;
          left: 0;
          width: 100%;
          height: 100%;
          z-index: 2000;
        "
      >
        <div
          class="modal-back"
          style="
            position: absolute;
            top: 0;
            left: 0;
            width: 100%;
            height: 100%;
            background: rgba(0, 0, 0, 0.5);
          "
        ></div>

        <div
          class="weather_widget weather_section flex flex-col items-center justify-center min-h-screen text-gray-700 p-10"
          style="position: relative; z-index: 2001; pointer-events: none"
        >
          <!-- Pointer events auto on children to allow clicking -->
          <div
            class="close noselect bg-white p-10 rounded-xl ring-8 ring-white ring-opacity-40"
            style="
              cursor: pointer;
              pointer-events: auto;
              margin-bottom: 20px;
              width: 50px;
              height: 50px;
              display: flex;
              align-items: center;
              justify-content: center;
              font-size: 30px;
            "
          >
            +
          </div>

          <div
            class="w-full max-w-screen-sm owHidden bg-white p-10 rounded-xl ring-8 ring-white ring-opacity-40"
            style="pointer-events: auto; max-height: 80vh; overflow-y: auto"
          >
            <div class="flex justify-between currentHour">
              <!-- Component currentHour -->
            </div>
            <hr class="my-4" />
            <div class="nextHours swiper">
              <!-- Component nextHours -->
            </div>
            <hr class="my-4" />
            <div class="scrollHandle nextDays">
              <!-- Component nextDays -->
            </div>
          </div>
        </div>
      </div>
    </div>

    <!-- Modal -->
    <div id="configModal" class="modal">
      <div class="modal-content">
        <span class="close no-select">&times;</span>
        <h2 class="no-select">Konfiguracja</h2>
        <br />

        <!-- Zakładki -->
        <div class="config-tabs">
          <button class="tab-button" data-tab="rooms">POKOJE</button>
          <button class="tab-button active" data-tab="settings">
            USTAWIENIA
          </button>
        </div>

        <hr />
        <br />

        <!-- Zawartość zakładki USTAWIENIA -->
        <div class="tab-content" id="settings-tab">
          <div class="settings-container">
            <div class="setting-item">
              <table cellspacing="0" cellpadding="0">
                <tr>
                  <td>
                    <label
                      >Minimalna temperatura na rozdzielaczu<br />
                      potrzebna do włączenia grzania:</label
                    >
                  </td>
                  <td><input type="number" class="manifoldMinTemp" /></td>
                </tr>
                <tr>
                  <td>
                    <label
                      >Róznica temperatur<br />do włączenia drugiego
                      obiegu:</label
                    >
                  </td>
                  <td><input type="number" class="boostThreshold" /></td>
                </tr>
                <tr>
                  <td><label>Tryb Boost (Drugi pokój):</label></td>
                  <td><input type="checkbox" class="boostEnabled" /></td>
                </tr>

                <tr>
                  <td><label>Tryb pracy ogrzewnia: priorytet</label></td>
                  <td>
                    <select class="workMode">
                      <option value="wood_gas">Kominek + Gaz</option>
                      <option value="wood_only">Kominek</option>
                      <option value="gas_only">Gaz</option>
                    </select>
                  </td>
                </tr>
              </table>
            </div>
          </div>
        </div>

        <!-- Zawartość zakładki POKOJE -->
        <div class="tab-content" id="rooms-tab" style="display: block">
          <div id="roomList"></div>
        </div>

        <br />
        <hr />
        <br />

        <button class="" id="wifiConfig">Wifi settings</button>
        <button class="confirm" id="saveConfig">Zapisz</button>
      </div>
    </div>

    <script type="text/javascript">// Funkcja generująca mały wykres (Sparkline) SVG
function createSparkline(data, width = 30, height = 30) {
  if (!data || data.length < 2) return "";

  const min = Math.min(...data);
  const max = Math.max(...data);
  const range = max - min || 1;

  const padding = 3;
  const drawHeight = height - 2 * padding;
  const step = width / (data.length - 1);

  const points = data
    .map((val, i) => {
      const x = i * step;
      const y = height - padding - ((val - min) / range) * drawHeight;
      return `${x},${y}`;
    })
    .join(" ");

  const isRising = data[data.length - 1] >= data[0];
  const strokeColor = isRising ? "#ff4444" : "#4444ff"; // Czerwony (rośnie) / Niebieski (spada)

  return `
      <svg width="${width}" height="${height}" viewBox="0 0 ${width} ${height}" style="overflow: visible;">
          <polyline points="${points}" fill="none" stroke="${strokeColor}" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" opacity="0.8"/>
          <circle cx="${width}" cy="${
    height - padding - ((data[data.length - 1] - min) / range) * drawHeight
  }" r="3" fill="${strokeColor}" />
      </svg>
  `;
}

class Room {
  /**
   * @param {string} id
   * @param {string} name
   * @param {number} currentTemperature
   * @param {number} targetTemperature
   * @param {boolean} forced
   * @param {string} battery_level
   * @param {string} battery_state
   * @param {number} priority
   * @param {boolean} valve
   * @param {string} valveMode
   * @param {number} pinNumber
   */
  constructor(
    id,
    name,
    currentTemperature,
    targetTemperature,
    forced,
    battery_level,
    battery_state,
    priority = 0,
    valve = false,
    valveMode = "off",
    pinNumber = 0
  ) {
    this.id = id;
    this.name = name;
    this.currentTemperature = currentTemperature;
    this.targetTemperatureNetatmo = targetTemperature; // Renamed for clarity
    this.targetTemperatureFireplace = targetTemperature; // Initialize fireplace temp, maybe update later if different
    this.forced = forced;
    this.battery_state = battery_state;
    this.battery_level = battery_level;
    this.priority = priority;
    this.valve = valve;
    this.valveMode = valveMode;
    this.pinNumber = pinNumber;
    this.element = this.createElement();
  }

  createElement() {
    // Dodajemy style dla valve-indicator jeśli jeszcze nie istnieją
    if (!document.getElementById("valve-indicator-style")) {
      const style = document.createElement("style");
      style.id = "valve-indicator-style";
      document.head.appendChild(style);
    }

    const card = document.createElement("div");
    card.classList.add("thermostat-card");
    card.dataset.id = this.id;
    card.dataset.pin = this.pinNumber;

    const backButton = document.createElement("button");
    backButton.classList.add("back-button");
    backButton.textContent = "←";
    backButton.addEventListener("click", (e) => {
      e.stopPropagation();
      this.closeCard();
    });

    const title = document.createElement("h2");
    title.textContent = this.name;

    const temperatures = document.createElement("div");
    temperatures.classList.add("temperatures");

    const currentTemp = document.createElement("div");
    currentTemp.classList.add("temperature");
    currentTemp.innerHTML = `<div class="temperature-value">${this.currentTemperature.toFixed(
      1
    )}°</div><div class="temperature-label">Aktualna</div>`; // Polish label

    const targetTempNetatmo = document.createElement("div");
    targetTempNetatmo.classList.add("temperature");
    targetTempNetatmo.innerHTML = `<div class="temperature-value">${this.targetTemperatureNetatmo.toFixed(
      1
    )}°</div><div class="temperature-label">Cel Netatmo</div>`; // Slider 1 Target

    const targetTempFireplace = document.createElement("div");
    targetTempFireplace.classList.add("temperature");
    targetTempFireplace.innerHTML = `<div class="temperature-value">${this.targetTemperatureFireplace.toFixed(
      1 // Initialize with fireplace temp
    )}°</div><div class="temperature-label">Cel Kominek</div>`; // Slider 2 Target

    temperatures.appendChild(currentTemp);
    temperatures.appendChild(targetTempNetatmo);
    temperatures.appendChild(targetTempFireplace); // Add fireplace temp display

    // Kontener na wykres
    const sparklineContainer = document.createElement("div");
    sparklineContainer.classList.add("sparkline-container");

    const quickActions = document.createElement("div");
    quickActions.classList.add("quick-actions");

    // Add fire button
    const fireButton = document.createElement("button");
    fireButton.classList.add("action-button", "a_fire");
    if (this.forced) {
      fireButton.classList.add("active");
    }
    fireButton.addEventListener("click", () => {
      const isActive = !fireButton.classList.contains("active");
      console.log(isActive);
      this.forced = isActive;
      this.sendCommand("forced", isActive);
      fireButton.classList.toggle("active");
    });

    // skopiuj ikonke svg a_fire
    /* const fireButtonSvgCopy = document
     .querySelector("footer .a_fire")
     .cloneNode(true); */

    // fireButton.classList.add("action-button", "a_fire");
    // fireButton.appendChild(fireButtonSvgCopy);
    // console.log(fireButtonSvgCopy);

    const ecoButton = document.createElement("button");
    ecoButton.classList.add("action-button");
    ecoButton.classList.add("eco-button");
    ecoButton.textContent = "Eco";
    ecoButton.addEventListener("click", () => this.sendCommand("eco"));

    const boostButton = document.createElement("button");
    boostButton.classList.add("action-button");
    boostButton.textContent = "Boost";
    boostButton.addEventListener("click", () => this.sendCommand("boost"));

    quickActions.appendChild(fireButton);
    quickActions.appendChild(ecoButton);
    // quickActions.appendChild(boostButton);

    const controls = document.createElement("div");
    controls.classList.add("controls");

    // --- Slider 1: Netatmo Target ---
    const sliderNetatmoLabel = document.createElement("label");
    sliderNetatmoLabel.textContent = "Cel Netatmo:";
    sliderNetatmoLabel.classList.add("slider-label");

    const sliderNetatmo = document.createElement("input");
    sliderNetatmo.type = "range";
    sliderNetatmo.classList.add("temperature-slider", "netatmo-slider");
    sliderNetatmo.min = 5; // Min temp for Netatmo
    sliderNetatmo.max = 30;
    sliderNetatmo.step = 0.5; // Step for Netatmo
    sliderNetatmo.value = this.targetTemperatureNetatmo;
    sliderNetatmo.addEventListener("input", (e) => {
      targetTempNetatmo.querySelector(
        ".temperature-value"
      ).textContent = `${parseFloat(e.target.value).toFixed(1)}°`;
      // Update internal value but don't send command yet
      this.targetTemperatureNetatmo = parseFloat(e.target.value);
      this.updateHeatingIndicator(); // Update indicator immediately
    });
    sliderNetatmo.addEventListener("mouseup", () => {
      // Send command only when user releases slider
      this.sendCommand("act_temperature");
    });

    // --- Slider 2: Fireplace Target ---
    const sliderFireplaceLabel = document.createElement("label");
    sliderFireplaceLabel.textContent = "Cel Kominek:";
    sliderFireplaceLabel.classList.add("slider-label");

    const sliderFireplace = document.createElement("input");
    sliderFireplace.type = "range";
    sliderFireplace.classList.add("temperature-slider", "fireplace-slider");
    sliderFireplace.min = 0; // Different range/step for fireplace?
    sliderFireplace.max = 28; 
    sliderFireplace.step = 0.5;
    sliderFireplace.value = this.targetTemperatureFireplace;
    sliderFireplace.addEventListener("input", (e) => {
      targetTempFireplace.querySelector(
        ".temperature-value"
      ).textContent = `${parseFloat(e.target.value).toFixed(1)}°`;
      // Update internal value
      this.targetTemperatureFireplace = parseFloat(e.target.value);
      this.updateHeatingIndicator(); // Update indicator immediately
    });
    sliderFireplace.addEventListener("mouseup", () => {
      // Send specific command for fireplace target
      this.sendFireplaceCommand();
    });

    controls.appendChild(sliderNetatmoLabel);
    controls.appendChild(sliderNetatmo);
    controls.appendChild(sliderFireplaceLabel);
    controls.appendChild(sliderFireplace);

    const batteryIndicator = this.createBatteryIndicator();

    // Create priority display
    const priorityDisplay = document.createElement("p");
    priorityDisplay.classList.add("priority-display");
    priorityDisplay.textContent = `Priority: ${this.priority}`;
    priorityDisplay.style.fontSize = "20px";
    priorityDisplay.style.color = "#666";
    priorityDisplay.style.marginTop = "-28px";
    priorityDisplay.style.textAlign = "center";

    card.appendChild(backButton);
    card.appendChild(title);
    card.appendChild(temperatures);
    card.appendChild(sparklineContainer); // Dodajemy wykres pod temperaturami
    card.appendChild(quickActions);
    card.appendChild(controls);
    card.appendChild(priorityDisplay);
    card.appendChild(batteryIndicator);

    this.element = card; // Ensure this.element is assigned before calling updateHeatingIndicator
    this.updateHeatingIndicator();
    this.updateValveIndicator();

    card.addEventListener("click", (e) => {
      if (e.target.closest(".action-button") || e.target === backButton) return;
      if (card.classList.contains("expanded")) {
        // Jeśli karta jest już rozwinięta, usuń klasę expanded
        card.classList.remove("expanded");
        document.body.style.overflow = "auto";
      } else {
        // Jeśli karta nie jest rozwinięta, rozwiń ją
        document
          .querySelectorAll(".thermostat-card.expanded")
          .forEach((expandedCard) => {
            expandedCard.classList.remove("expanded");
          });
        card.classList.add("expanded");
        // document.body.style.overflow = "hidden";
      }
    });
    return card;
  }

  createBatteryIndicator() {
    const batteryIndicator = document.createElement("div");
    batteryIndicator.classList.add("battery-indicator");

    const batterySvg = document.createElementNS(
      "http://www.w3.org/2000/svg",
      "svg"
    );
    batterySvg.setAttribute("class", "battery_indicator");
    batterySvg.setAttribute("viewBox", "0 0 167.64 101.93");

    const defs = document.createElementNS("http://www.w3.org/2000/svg", "defs");
    const style = document.createElementNS(
      "http://www.w3.org/2000/svg",
      "style"
    );
    style.textContent = `
    .ramka path, .ramka2 path, .bars path { 
         opacity: 1;
         }

     .bt1 { fill: #FF2F00; }
   @keyframes pulse-battery {
       0% {
           fill-opacity: 1;
       }
       50% {
           fill-opacity: 0.5;
       }
       100% {
           fill-opacity: 1;
       }
   }

   .pulsing {
       animation: pulse-battery 1s infinite;
   }
     .bt2 { fill: #FFAA00; }
  
     .bt4 { fill: #00FF00; }
     .hidden { display: none; }
   `;
    defs.appendChild(style);
    batterySvg.appendChild(defs);

    const ramka = document.createElementNS("http://www.w3.org/2000/svg", "g");
    ramka.setAttribute("class", "ramka");
    const ramkaPath = document.createElementNS(
      "http://www.w3.org/2000/svg",
      "path"
    );
    ramkaPath.setAttribute("class", "");
    ramkaPath.setAttribute(
      "d",
      "M75.57,101.92c-20.66,0-41.33.01-61.99,0-9.24,0-13.56-4.2-13.57-13.33C-.01,63.42,0,38.26.07,13.09.09,4.14,4.33.01,13.3,0,54.79,0,96.29,0,137.78.01c8.72,0,12.9,4.17,12.9,12.8.01,25.33.01,50.66,0,75.99,0,8.96-4.15,13.1-13.11,13.11-20.66.02-41.33,0-61.99,0ZM76.07,10.08c-20.15,0-40.3.15-60.44-.12-4.59-.06-5.49,1.44-5.45,5.66.2,23.64.22,47.29.06,70.93-.03,4.07.97,5.36,5.22,5.35,40.12-.16,80.25-.16,120.38,0,4.15.02,4.86-1.44,4.84-5.15-.14-23.81-.17-47.62.02-71.43.03-4.06-.92-5.38-5.18-5.33-19.81.23-39.63.1-59.44.09Z"
    );
    ramka.appendChild(ramkaPath);
    batterySvg.appendChild(ramka);

    const ramka2 = document.createElementNS("http://www.w3.org/2000/svg", "g");
    ramka2.setAttribute("class", "ramka2");
    const ramkaPath2 = document.createElementNS(
      "http://www.w3.org/2000/svg",
      "path"
    );
    ramkaPath2.setAttribute("class", "");
    ramkaPath2.setAttribute(
      "d",
      "M153.84,50.84c0-3.99-.07-7.98.01-11.97.09-4.69,2.39-6.32,6.79-4.61,4.25,1.65,6.65,4.98,6.84,9.53.2,4.81.24,9.65-.03,14.45-.27,4.74-2.85,8.1-7.44,9.53-4.07,1.27-6-.16-6.13-4.48-.13-4.15-.03-8.31-.03-12.46Z"
    );
    ramka2.appendChild(ramkaPath2);
    batterySvg.appendChild(ramka2);

    const bars = document.createElementNS("http://www.w3.org/2000/svg", "g");
    bars.setAttribute("class", "bars");

    const batteryLevels = [
      {
        class: "hidden",
        d: "M34.61,51.48c0,9.66-.11,19.31.05,28.97.07,4.11-1.63,5.68-5.63,5.6-15.29-.31-13.81,2.03-13.85-13.36-.04-16.81.12-33.63-.06-50.44-.05-4.78,1.67-6.47,6.44-6.39,14.69.24,12.99-1.36,13.06,13.15.02,3.83.01,7.66.01,11.49,0,3.66,0,7.32,0,10.99h-.02Z",
      },
      {
        class: "hidden",
        d: "M134.57,51.28c0,9.67-.1,19.33.05,28.99.06,4.01-1.49,5.82-5.56,5.75-14.88-.26-14.28,2.24-14.24-13.66.04-16.5,0-32.99.02-49.49,0-6.18.82-7.01,6.86-6.95,13.8.14,12.94-1.76,12.88,12.86-.03,7.5,0,15,0,22.5Z",
      },
      {
        class: "hidden",
        d: "M109.57,51.53c0,9.64-.09,19.28.04,28.92.05,4.03-1.54,5.68-5.62,5.6-14.8-.28-14.16,2.11-14.1-13.74.06-16.29,0-32.57.02-48.86,0-6.92.56-7.45,7.23-7.5,13.72-.1,12.43-1.23,12.43,12.65,0,7.64,0,15.29,0,22.93Z",
      },
      {
        class: "hidden",
        d: "M64.96,50.5c0-9.49.08-18.99-.04-28.48-.06-4.42,1.66-6.22,6.24-6.15,15.2.23,13.37-1.39,13.4,13.3.04,16.82-.11,33.64.09,50.46.06,4.78-1.63,6.57-6.4,6.44-13.91-.4-13.24,2.35-13.28-13.59-.02-7.33,0-14.65-.01-21.98Z",
      },
      {
        class: "hidden",
        d: "M59.59,51.1c0,9.82-.09,19.65.04,29.47.05,3.81-1.47,5.5-5.28,5.45-15.79-.21-14.17,2.01-14.24-13.49-.08-16.65-.04-33.3,0-49.96.01-5.95.71-6.64,6.55-6.63,14.35.02,12.92-1.49,12.94,12.68,0,7.49,0,14.99,0,22.48Z",
      },
    ];

    batteryLevels.forEach((level) => {
      const path = document.createElementNS(
        "http://www.w3.org/2000/svg",
        "path"
      );
      path.setAttribute("class", `${level.class} hidden`);
      path.setAttribute("d", level.d);
      bars.appendChild(path);
    });

    batterySvg.appendChild(bars);
    batteryIndicator.appendChild(batterySvg);

    this.updateBatteryIndicator(batterySvg);

    return batteryIndicator;
  }

  updateBatteryIndicator(batterySvg) {
    const battery_state = this.battery_state;
    /* const battery_level = this.battery_level; */
    const ramka = batterySvg.querySelector(".ramka path");
    const ramka2 = batterySvg.querySelector(".ramka2 path");
    const levels = batterySvg.querySelectorAll(".bars path");

    // Reset all levels to hidden
    levels.forEach((level) => level.classList.add("hidden"));

    if (battery_state === "full") {
      ramka.setAttribute("fill", "#00ff00");
      ramka2.setAttribute("fill", "#00ff00");
      levels.forEach((level) => {
        levels[0].classList.remove("hidden");
        levels[1].classList.remove("hidden");
        levels[2].classList.remove("hidden");
        levels[3].classList.remove("hidden");
        levels[4].classList.remove("hidden");
        level.setAttribute("fill", "#00ff00");
      });
    } else if (battery_state === "high") {
      ramka.setAttribute("fill", "#FFAA00");
      ramka2.setAttribute("fill", "#FFAA00");
      levels.forEach((level) => {
        levels[0].classList.remove("hidden");
        levels[3].classList.remove("hidden");
        levels[4].classList.remove("hidden");

        level.setAttribute("fill", "#FFAA00");
      });
    } else if (battery_state === "low") {
      ramka.setAttribute("fill", "#FF2F00");
      ramka2.setAttribute("fill", "#FF2F00");
      levels[0].classList.remove("hidden");
      levels[3].classList.remove("hidden");
      level.setAttribute("fill", "#FF2F00");
    } else if (battery_state === "very_low") {
      ramka.classList.add("pulsing");
      ramka2.classList.add("pulsing");
      ramka.setAttribute("fill", "#FF2F00");
      ramka2.setAttribute("fill", "#FF2F00");
      levels[0].classList.remove("hidden");
      level.setAttribute("fill", "#FF2F00");
      // dodaj do kazdego levels klase pulsing
      levels.forEach((level) => {
        level.classList.add("pulsing");
      });
    }
  }

  updateHeatingIndicator() {
    // Use global useGazState (defined later)
    let effectiveTarget;
    if (window.useGazState === true) {
      // Check global state
      effectiveTarget = Math.max(
        this.targetTemperatureNetatmo,
        this.targetTemperatureFireplace
      );
    } else {
      effectiveTarget = this.targetTemperatureFireplace;
    }

    if (this.currentTemperature < effectiveTarget) {
      this.element.dataset.heating = "true"; // Used for body class
      if (!this.element.querySelector(".heating-indicator")) {
        const indicator = document.createElement("div");
        indicator.classList.add("heating-indicator");
        this.element.appendChild(indicator);
      }
    } else {
      this.element.dataset.heating = "false";
      const indicator = this.element.querySelector(".heating-indicator");
      if (indicator) {
        indicator.remove();
      }
    }
  }

  updateValveIndicator() {
    if (this.valve) {
      this.element.dataset.valve = "true";
      let indicator = this.element.querySelector(".valve-indicator");
      if (!indicator) {
        indicator = document.createElement("div");
        indicator.classList.add("valve-indicator");
        this.element.appendChild(indicator);
      }

      if (this.valveMode === "secondary") {
        indicator.classList.add("secondary");
      } else {
        indicator.classList.remove("secondary");
      }
    } else {
      this.element.dataset.valve = "false";
      const indicator = this.element.querySelector(".valve-indicator");
      if (indicator) {
        indicator.remove();
      }
    }
  }

  closeCard() {
    this.element.classList.remove("expanded");
    document.body.style.overflow = "auto";
  }

  // Command for Slider 1 (Netatmo)
  sendCommand(command) {
    const message = {
      id: this.id,
      command: command, // e.g., "act_temperature", "forced"
      targetTemperature: parseFloat(this.targetTemperatureNetatmo).toFixed(1), // Send Netatmo target
      forced: this.forced,
      // priority: this.priority // Priority is calculated backend
    };

    console.log(message);
    console.log("Sending command:", message);
    ws.send(JSON.stringify(message));
  }

  // Command for Slider 2 (Fireplace)
  sendFireplaceCommand() {
    const message = {
      id: this.id,
      command: "set_fireplace_target", // New command
      targetTemperatureFireplace: parseFloat(
        this.targetTemperatureFireplace
      ).toFixed(1), // Send fireplace target
    };
    console.log("Sending fireplace command:", message);
    ws.send(JSON.stringify(message));
  }
  sendMinimalTemperature() {
    temp = document.querySelector("#configModal .manifoldMinTemp").value;
    if (temp != "") {
      ws.send(JSON.stringify({ command: "manifoldMinTemp", value: temp }));
    }
  }

  update(data) {
    this.currentTemperature = data.currentTemperature;
    // Update both target temperatures from backend data
    this.targetTemperatureNetatmo = data.targetTemperatureNetatmo;
    this.targetTemperatureFireplace = data.targetTemperatureFireplace;
    this.forced = data.forced;
    this.battery_state = data.battery_state;
    this.priority = data.priority || this.priority; // Update priority if available
    this.valve = data.valve || false; // Update valve status if available
    this.valveMode = data.valveMode || "off";
    this.pinNumber = data.pinNumber || this.pinNumber; // Update pin number if available

    // Aktualizacja wykresu (Sparkline)
    if (data.history) {
      const container = this.element.querySelector(".sparkline-container");
      if (container) {
        container.innerHTML = createSparkline(data.history);
      }
    }

    // Update UI elements
    this.element.querySelector(
      // Current Temp
      ".temperatures .temperature:nth-child(1) .temperature-value"
    ).textContent = `${this.currentTemperature.toFixed(1)}°`;
    this.element.querySelector(
      // Netatmo Target Display
      ".temperatures .temperature:nth-child(2) .temperature-value"
    ).textContent = `${this.targetTemperatureNetatmo.toFixed(1)}°`;
    this.element.querySelector(
      // Fireplace Target Display
      ".temperatures .temperature:nth-child(3) .temperature-value"
    ).textContent = `${this.targetTemperatureFireplace.toFixed(1)}°`;

    // Update slider positions
    const netatmoSlider = this.element.querySelector(".netatmo-slider");
    if (netatmoSlider && document.activeElement !== netatmoSlider)
      netatmoSlider.value = this.targetTemperatureNetatmo;
    const fireplaceSlider = this.element.querySelector(".fireplace-slider");
    if (fireplaceSlider && document.activeElement !== fireplaceSlider)
      fireplaceSlider.value = this.targetTemperatureFireplace;

    // Update forced button state
    const fireButton = this.element.querySelector(".action-button.a_fire");
    if (fireButton) {
      if (this.forced) {
        fireButton.classList.add("active");
      } else {
        fireButton.classList.remove("active");
      }
    }

    // Update priority display
    const priorityDisplay = this.element.querySelector(".priority-display");
    if (priorityDisplay) {
      priorityDisplay.textContent = `Priority: ${this.priority}`;
    }

    // Update data attributes
    this.element.dataset.pin = this.pinNumber;
    this.element.dataset.id = this.id;
    this.element.dataset.forced = this.forced;

    this.updateHeatingIndicator();
    this.updateValveIndicator();
    this.updateBatteryIndicator(
      this.element.querySelector(".battery_indicator")
    );
  }
}

let rooms = {};
window.useGazState = false; // Global state for useGaz

function updateBodyHeatingClass() {
  const thermostatList = document.getElementById("thermostat-list");
  if (!thermostatList) return; // Guard against null
  const thermostatCards =
    thermostatList.getElementsByClassName("thermostat-card");
  let isHeating = false;

  for (let card of thermostatCards) {
    // Check the data attribute set by updateHeatingIndicator
    // if heating and forced are both true, it's considered heating
    if (card.dataset.heating === "true" && card.dataset.forced === "true") {
      isHeating = true;
      break;
    }
  }

  if (isHeating) {
    document.body.classList.add("heating");
  } else {
    document.body.classList.remove("heating");
  }
}

function handleWebSocketMessage(data) {
  const parsedData = JSON.parse(data);
  console.log("Received parsed data:", parsedData); // Log received data

  const thermostatList = document.getElementById("thermostat-list");
  const loader = document.getElementById("loader");

  if (parsedData.meta && parsedData.meta.ahtStatus !== undefined) {
    const consoleEl = document.querySelector(".console");
    if (consoleEl) {
      if (parsedData.meta.ahtStatus !== "OK") {
        consoleEl.textContent = "AHT: " + parsedData.meta.ahtStatus;
        consoleEl.style.color = "#ff4444";
      } else {
        // Opcjonalnie: wyczyść komunikat błędu, jeśli status wrócił do normy
        // consoleEl.textContent = "";
        consoleEl.style.color = "";
      }
    }
  }
  // Check for meta field first to update global state
  if (parsedData.meta && parsedData.meta.usegaz !== undefined) {
    window.useGazState = parsedData.meta.usegaz === "true";
    const useGazButton = document.getElementById("useGazButton");
    if (useGazButton) {
      if (window.useGazState) {
        useGazButton.classList.add("active");
      } else {
        useGazButton.classList.remove("active");
      }
    }
    console.log("Updated useGazState:", window.useGazState);
  }

  if (parsedData.meta && parsedData.meta.manifoldTemp !== undefined) {
    const el = document.querySelector("footer .a_fire .manifoldTemp");
    if (el) {
      el.innerHTML = parsedData.meta.manifoldTemp + "°C";
    }
  }
  if (parsedData.meta && parsedData.meta.manifoldMinTemp !== undefined) {
    console.log("Min operating temperature:", parsedData.meta.manifoldMinTemp);
    const minTempInput = document.querySelector(
      "#configModal .manifoldMinTemp"
    );
    if (minTempInput)
      minTempInput.value = Number(parsedData.meta.manifoldMinTemp);
  }
  if (parsedData.meta && parsedData.meta.boostEnabled !== undefined) {
    const boostEnabledInput = document.querySelector(".boostEnabled");
    if (boostEnabledInput)
      boostEnabledInput.checked = parsedData.meta.boostEnabled === "true";
  }
  if (parsedData.meta && parsedData.meta.boostThreshold !== undefined) {
    const boostThresholdInput = document.querySelector(
      "#configModal .boostThreshold"
    );
    if (boostThresholdInput)
      boostThresholdInput.value = Number(parsedData.meta.boostThreshold);
  }
  if (parsedData.rooms) {
    const roomData = parsedData.rooms;
    roomData.forEach((room) => {
      // Make sure both target temperatures exist in the data
      const targetNetatmo =
        room.targetTemperatureNetatmo !== undefined
          ? room.targetTemperatureNetatmo
          : 18.0; // Default if missing
      const targetFireplace =
        room.targetTemperatureFireplace !== undefined
          ? room.targetTemperatureFireplace
          : 18.0; // Default if missing

      if (rooms[room.id]) {
        // Pass both targets to the update method
        rooms[room.id].update({
          ...room, // Spread other properties
          targetTemperatureNetatmo: targetNetatmo,
          targetTemperatureFireplace: targetFireplace,
        });
      } else {
        const newRoom = new Room(
          room.id,
          room.name,
          room.currentTemperature,
          targetNetatmo, // Pass Netatmo target to constructor
          room.forced,
          room.battery_level,
          room.battery_state,
          room.priority,
          room.valve,
          room.valveMode,
          room.pinNumber
        );
        // Set fireplace temp separately after creation if needed, or modify constructor
        newRoom.targetTemperatureFireplace = targetFireplace;

        rooms[room.id] = newRoom;
        if (thermostatList) {
          thermostatList.appendChild(newRoom.element);
        } else {
          console.error('Element with ID "thermostat-list" not found');
        }
      }
    });
    if (thermostatList && thermostatList.children.length > 0) {
      loader.style.display = "none";
    }
    // Update indicators for all rooms after processing batch, as useGazState might have changed
    Object.values(rooms).forEach((room) => room.updateHeatingIndicator());
  } else if (parsedData.command === "getRooms") {
    // Assuming this is for config modal
    const roomList = document.getElementById("roomList");
    if (!roomList) return;
    roomList.innerHTML = "";

    parsedData.rooms.forEach((room) => {
      const div = document.createElement("div");
      div.className = "room-item";
      div.innerHTML = `
       <input type="text" class="room-name" value="${
         room.name
       }" data-room-id="${room.id}" placeholder="Nazwa pokoju">
       <select class="room-pin" data-room-id="${room.id}">
         ${Array.from(
           { length: 54 },
           (_, i) =>
             `<option value="${i}" ${
               room.pin === i ? "selected" : ""
             }">Pin ${i}</option>`
         ).join("")}
       </select>
     `;
      roomList.appendChild(div);
    });
  } else if (parsedData.pinMappings) {
    // Aktualizuj listę w modalu
    const roomList = document.getElementById("roomList");
    roomList.innerHTML = "";

    parsedData.pinMappings.forEach((mapping) => {
      const div = document.createElement("div");
      div.className = "room-item";
      div.innerHTML = `
       <input type="text" class="room-name" value="${
         mapping.name
       }" data-room-id="${mapping.roomId}" placeholder="Nazwa pokoju">
       <select class="room-pin" data-room-id="${mapping.roomId}">
         ${Array.from(
           { length: 54 },
           (_, i) =>
             `<option value="${i}" ${
               mapping.pin === i ? "selected" : ""
             }>Pin ${i}</option>`
         ).join("")}
       </select>
     `;
      roomList.appendChild(div);
    });
  } else if (parsedData.response === "pinUpdated") {
    console.log(
      `Pin updated for room ${parsedData.roomId} to ${parsedData.pin}`
    );
  } else {
    //console.log("Received message:", data);
  }
  updateBodyHeatingClass();
}

let ws;
let shouldReloadOnReconnect = false;
const wsStatusElement = document.getElementById("ws-status");

function setWsStatus(status) {
  if (!wsStatusElement) return;
  wsStatusElement.classList.remove(
    "ws-connected",
    "ws-disconnected",
    "ws-error"
  );
  switch (status) {
    case "connected":
      wsStatusElement.classList.add("ws-connected");
      wsStatusElement.title = "Połączono z WebSocket";
      break;
    case "disconnected":
      wsStatusElement.classList.add("ws-disconnected");
      wsStatusElement.title =
        "Rozłączono WebSocket, próba ponownego połączenia...";
      break;
    case "error":
      wsStatusElement.classList.add("ws-error");
      wsStatusElement.title = "Błąd połączenia WebSocket";
      break;
    default:
      wsStatusElement.classList.add("ws-disconnected");
      wsStatusElement.title = "Rozłączono WebSocket";
  }
}

function connectWebSocket() {
  //  ws = new WebSocket("ws://192.168.8.47:81");
  ws = new WebSocket("ws://netatmo_relay.local:81"); // Use mDNS name

  ws.onopen = function (event) {
    console.log("WebSocket connection opened:", event);
    setWsStatus("connected");
    if (shouldReloadOnReconnect) {
      window.location.reload();
    }
    shouldReloadOnReconnect = true;
    // Send a message to the server if needed
    // ws.send(JSON.stringify({ message: "Hello Server!" }));
  };

  ws.onmessage = function (event) {
    console.log("Message from server:", event.data);
    handleWebSocketMessage(event.data);
  };

  ws.onclose = function (event) {
    console.log("WebSocket connection closed:", event);
    setWsStatus("disconnected");
    // Ponowne połączenie po 5 sekundach
    setTimeout(connectWebSocket, 5000); // Increased timeout to 5s
  };

  ws.onerror = function (error) {
    console.error("WebSocket error:", error);
    setWsStatus("error");
    // onclose will likely be called after onerror, attempting reconnect
  };
}

// Nawiązanie połączenia WebSocket przy całkowitym załadowaniu strony

document.addEventListener("DOMContentLoaded", function () {
  setWsStatus("disconnected"); // Set initial state
  connectWebSocket();
  console.log("DOM fully loaded and parsed");

  const configButton = document.querySelector(".configButton");
  const wifiConfigButton = document.querySelector("#wifiConfig");
  const modal = document.getElementById("configModal");
  const span = document.getElementsByClassName("close")[0];
  const saveButton = document.getElementById("saveConfig");
  const roomList = document.getElementById("roomList");
  const useGazButton = document.getElementById("useGazButton");
  const tabButtons = document.querySelectorAll(".tab-button");
  const tabContents = document.querySelectorAll(".tab-content");
  const saveMinimalTemp = document.querySelector(
    "#configModal .manifoldMinTemp"
  );
  const saveBoostThreshold = document.querySelector(
    "#configModal .boostThreshold"
  );
  const boostEnabledCheckbox = document.querySelector(".boostEnabled");

  // Obsługa zakładek
  tabButtons.forEach((button) => {
    button.addEventListener("click", () => {
      // Usuń klasę active ze wszystkich przycisków
      tabButtons.forEach((btn) => btn.classList.remove("active"));
      // Dodaj klasę active do klikniętego przycisku
      button.classList.add("active");

      // Ukryj wszystkie zakładki
      tabContents.forEach((content) => (content.style.display = "none"));

      // Pokaż odpowiednią zakładkę
      const tabId = button.getAttribute("data-tab");
      document.getElementById(`${tabId}-tab`).style.display = "block";
    });
  });

  // on change input trigger function
  saveMinimalTemp.addEventListener("change", function () {
    ws.send(JSON.stringify({ command: "manifoldMinTemp", value: this.value }));
  });

  if (saveBoostThreshold) {
    saveBoostThreshold.addEventListener("change", function () {
      ws.send(
        JSON.stringify({ command: "setBoostThreshold", value: this.value })
      );
    });
  }

  if (boostEnabledCheckbox) {
    boostEnabledCheckbox.addEventListener("change", function () {
      ws.send(
        JSON.stringify({ command: "setBoostEnabled", value: this.checked })
      );
    });
  }

  wsSendCommand = (command, value) => {
    ws.send(JSON.stringify({ command: command, value: value }));
  };

  useGazButton.addEventListener("click", () => {
    if (ws.readyState === ws.OPEN) {
      if (useGazButton.classList.contains("active")) {
        wsSendCommand("usegaz", "false");
      } else {
        wsSendCommand("usegaz", "true");
      }
      useGazButton.classList.toggle("active");
    } else {
      alert("Brak połączenia z serwerem, odczekaj na połączenie");
    }
  });

  configButton.onclick = function () {
    modal.style.display = "block";
    if (ws.readyState === ws.OPEN) {
      ws.send(JSON.stringify({ command: "getRooms" }));
    } else {
      alert("Brak połączenia z serwerem, odczekaj na połączenie");
    }
  };

  wifiConfigButton.onclick = function () {
    modal.style.display = "block";
    document.location.href = "/config";
  };

  span.onclick = function () {
    modal.style.display = "none";
  };

  window.onclick = function (event) {
    if (event.target == modal) {
      modal.style.display = "none";
    }
  };

  saveButton.onclick = function () {
    const roomConfigs = [];
    const roomItems = roomList.querySelectorAll(".room-item");

    roomItems.forEach((item) => {
      const nameInput = item.querySelector(".room-name");
      const pinSelect = item.querySelector(".room-pin");

      roomConfigs.push({
        id: nameInput.getAttribute("data-room-id"),
        name: nameInput.value,
        pinNumber: pinSelect.value,
      });
    });

    ws.send(
      JSON.stringify({
        command: "updateRooms",
        rooms: roomConfigs,
      })
    );

    // Pokaż komunikat o zapisaniu
    const saveMessage = document.createElement("div");
    saveMessage.className = "save-message";
    saveMessage.textContent = "Konfiguracja zapisana";
    saveMessage.style.position = "absolute";
    saveMessage.style.top = "50%";
    saveMessage.style.left = "50%";
    saveMessage.style.transform = "translate(-50%, -50%)";
    saveMessage.style.backgroundColor = "#4CAF50";
    saveMessage.style.color = "white";
    saveMessage.style.padding = "15px";
    saveMessage.style.borderRadius = "5px";
    saveMessage.style.zIndex = "1000";

    modal.appendChild(saveMessage);

    setTimeout(() => {
      saveMessage.remove();
      modal.style.display = "none";
    }, 1500);
  };
});
</script>
    <script type="text/javascript">let owapikey = '5d652f0bff80d46c6a9ce422c48e4296';
let lat = '49.88087';
let lon = '19.56303';
let data = {};
let srcOfImage = "";


function random(min, max) {
  return Math.floor(Math.random() * (max - min + 1) + min);
}

function convertTimestamp(timestamp, type) {
  let date = new Date(timestamp * 1000);
  let hours = date.getHours();
  let minutes = date.getMinutes();
  let seconds = date.getSeconds();
  let day = date.getDate();
  let month = date.getMonth() + 1;
  let year = date.getFullYear();

  if (type == "date") {
    return `${day}.${month}.${year}`;
  }
  else if (type == "time") {
    return `${hours}:${minutes}:${seconds}`;
  }
  else if (type == "day") {
    return day;
  }
  else if (type == "month") {
    return month;
  }
  else if (type == "year") {
    return year;
  }
  else if (type == "hours") {
    return hours;
  }
  else if (type == "minutes") {
    return minutes;
  }
  else if (type == "seconds") {
    return seconds;
  } else return false;
}

// get forecast
function getForecast() {
  fetch(
    // new API 
    "//api.openweathermap.org/data/3.0/onecall?lat=" + lat + "&lon=" + lon + "&appid=" + owapikey + "&units=metric"
  )
    .then((response) => response.json())
    .then((data_) => {

      // console.log(data_.current.temp);
      if (data_.current.temp == '-0') { data_.current.temp = 0 }
      //data = data_;
      srcOfImage = "https://openweathermap.org/img/wn/" + data_.current.weather[0].icon + "@2x.png";
    /*   document.querySelector('.ifdata').classList.toggle('active'); */
      $("footer .a_weather").append(`<img  src="${srcOfImage}" alt=""/>`)
      $("footer .a_weather, .modal-back").show();
      $('.container-modal').hide();
      $('.weather_widget .close, footer .a_weather,  .modal-back').bind('click', function () {
        $('.container-modal').toggle(300);
      });

      currentHour(data_);
      nextHours(data_['hourly']).then(() => {


          const swiper = new Swiper('.swiper', {
          grabCursor: true,
          watchSlidesProgress: true,
          slidesPerView: 3,
          autoplay: {
            delay: 4500,
            disableOnInteraction: true
          }

        });

      }).then( 
        nextDays(data_['daily'])
      );
    });
}

let x = 0;
let list;

// Component nextHours   
let nextHours = async (data) => {
  let html = `<div class="swiper-wrapper">`;
  if (data) {


    data.forEach(nexthour => {

      let el = `<div class="swiper-slide flex time_items flex-col items-center noSelect" style="margin-right:30px; padding-bottom: 20px;">
                <span class="font-semibold mt-1 text-sm lcd noSelect time_dis">${convertTimestamp(nexthour.dt, "hours")}:${convertTimestamp(nexthour.dt, "minutes")} </span>
                <span class="text-xs font-semibold text-gray-400 lcd noSelect AMPM">PM</span>       
                <img alt="" src="https://openweathermap.org/img/wn/${nexthour.weather[0].icon}@2x.png" width="120px" class="noSelect" style="pointer-events: none;"/>	 
                <span class="font-semibold text-lg lcd noSelect">${nexthour.temp.toFixed(1)}°C</span>      <span class="text-sm lcd noSelect">${nexthour.feels_like}</span></div>`;
      html = html + el;
    });
    $('.nextHours').html("").append(html + `</div>`);
    return true;
  }
}
// Component currentHour   
let currentHour = async (data) => {
  let html = "";
  if (data) {

  /*   console.log(data); */

    html = `<div class="flex flex-col">
            <span class="text-3xl font-bold lcd">${data.current.temp}<span class="text-3xl oc">°C</span></span>
            <span class="font-light mt-1 text-gray-500 odczuwalna">Odczuwalna : ${data.current.feels_like.toFixed(1)}</span>
            <!-- <span class="font-semibold mt-1 text-gray-500">${data.name}</span> -->
            </div>
            <div class="flex flex-col">
            <span class="text-3xl font-bold lcd">&nbsp${data.current.humidity.toFixed(0)}<span class="text-3xl percent"><span
              class="upperTop ">o</span>/o</span></span>

            <!-- <span class="font-semibold mt-1 text-gray-500">${data.name}</span> -->
            </div>
            <div class="h-24 w-24 ">
            <img  src="${srcOfImage}" alt="" class="currentWeatherIcon"/>
            </div>`;
    $('.currentHour').html("").append(html);
    return true;
  }
}


let nextDays = async (data) => {

  if (data) {
    let html;

    data.forEach(day => {
      el = `<div class="flex justify-between items-center">
              <span class="font-semibold text-sm w-1/4 firstLetterUp">
              ${dayjs.unix(day.dt).format('dddd')}<br>
              ${dayjs.unix(day.dt).locale('pl').format('D')} ${dayjs.unix(day.dt).format('MMM')}
              </span>
              <div class="flex items-center justify-end w-1/4 pr-10">
                <span class="font-semibold humidityForecast">
                ${day.humidity}%
                </span>
            <IconHumidity></IconHumidity>
            </div>
              <img alt="" src="https://openweathermap.org/img/wn/${day.weather[0].icon}@2x.png" width="" />	
              <span class="font-semibold text-lg w-1/4 text-right temp_primary">${day.temp.day}°</span>
              <span class="under">
              <span class="fontTemp w-1/2 text-right temp_secondary"><span class="labelTemp">min
              </span>${day.temp.min}°</span>
              <span class="fontTemp w-1/2 text-right temp_secondary"><span class="labelTemp">max
              </span>${day.temp.max}°</span>
              </span>
            </div>`
      html = html + el;
    })
    $('.nextDays').html("").append(html);
    return true;
  } else { return false }
}
// setInterval(getForecast, 20000) // 33,33 minuty 




// nowa wersja 

$(document).ready(function() {
  // Helper function to init swiper safely
  function initSwiper() {
      const swiperEl = document.querySelector('.swiper');
      if (swiperEl && swiperEl.swiper) {
          swiperEl.swiper.destroy(true, true);
      }

     const swiper = new Swiper('.swiper', {
          grabCursor: true,
          watchSlidesProgress: true,
          slidesPerView: 3,
          autoplay: {
            delay: 4500,
           disableOnInteraction: true
          },
          observer: true,
          observeParents: true
      });
      // tutaj ten element powinien miec fade in opacity wszystkie te elementy  .swiper-wrapper .swiper-slide
      $('.swiper-wrapper .swiper-slide').animate({ opacity: 1 }, 500);
  }

  // Override getForecast to handle UI correctly and update footer
  window.getForecast = function(showModal = false) {
      // Use variables from weather.js
      console.log("Rozpoczynam pobieranie pogody...");
      const url = "https://api.openweathermap.org/data/3.0/onecall?lat=" + lat + "&lon=" + lon + "&appid=" + owapikey + "&units=metric";
      console.log("URL zapytania:", url);

      fetch(url)
        .then((response) => response.json())
        .then((data_) => {
            console.log("Otrzymane dane pogodowe:", data_);
            if (data_.current.temp == '-0') { data_.current.temp = 0 }

            // Update Footer Temp
            $(".a_weather .weather-temp").text(Math.round(data_.current.temp) + "°C");

            // Update Footer Icon

            const iconUrl = "https://openweathermap.org/img/wn/" + data_.current.weather[0].icon + "@2x.png";
            $(".a_weather img").attr("src", iconUrl);

            // Update global variable for weather.js functions (currentHour uses it)
            srcOfImage = iconUrl;

            // Populate Modal using weather.js functions
            currentHour(data_);

            // nextHours in weather.js creates .swiper-wrapper inside .nextHours
            nextHours(data_['hourly']).then(() => {
                const isVisible = $('.container-modal').is(':visible');

                if (showModal) {
                    // Show modal first, then init swiper in the callback to ensure dimensions are calculated correctly
                    $('.container-modal').fadeIn(300);
                    initSwiper();
                } else if (isVisible) {
                    // If updating in background while modal is open, re-init swiper
                    initSwiper();
                }
            });

            nextDays(data_['daily']);
        })
        .catch(err => {console.error("Weather fetch error:", err); });
  };

  // Bind click event
  $('.a_weather').off('click').on('click', function(e) {
      e.preventDefault();
      getForecast(true);
  });

  // Close modal handlers
  $(document).on('click', '.close, .modal-back', function() {
      $('.container-modal').fadeOut(300);
  });

  // Load weather on start to show temp
  getForecast(false);

  // Auto-refresh weather every 30 minutes
  setInterval(function() {
      getForecast(false);
  }, 30 * 60 * 1000);
});</script>
    <script type="text/javascript">
var qrcode_=document.querySelector(".qr-code");
$(".qr-code").hide();




function generateQR(user_input){

  // Clear any existing QR code
  qrcode_.innerHTML = "";

var qrcode = new QRCode(qrcode_, {
    text: user_input,
    width: 256, //128
    height: 256,
    colorDark : "#000000",
    colorLight : "#ffffff",
    correctLevel : QRCode.CorrectLevel.H
});


// Make sure the QR code is visible
$(".qr-code").show();
/*
let ipc = document.createElement("p");
ipc.innerText = user_input;
document.querySelector(".qr-code").appendChild(ipc);


let close_qr = document.createElement("a");
close_qr.innerText = "+";
close_qr.classList.add("qr-close", "ring-8", "ring-white", "ring-opacity-40");
document.querySelector(".qr-code").appendChild(close_qr);


$("a.a_qrcode, .qr-code .qr-close").on("click", function(){
  $(".qr-code").toggle(400);
});
 */

}
</script>
  </body>
</html>


)rawliteral";