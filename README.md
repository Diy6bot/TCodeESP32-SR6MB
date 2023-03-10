# TCodeESP32-SR6MB
This is a modified version of the Tempests TCode sketch (https://www.patreon.com/tempestvr) that includes a menu specifically for SR6MB. The menu can be easily accessed and navigated using just three buttons, so no coding skills are required for the user. The modified sketch also includes additional features such as a sleeve heater, a display, buttons, a menu, four vibration channels, and a squeeze servo channel.

# Prerequisites
<p>To open and compile this code, you will need to have the following libraries installed:</p>

<ul>
  <li>SPI.h</li>
  <li>Wire.h</li>
  <li>Adafruit_GFX.h</li>
  <li>Adafruit_SSD1306.h</li>
  <li>OneWire.h</li>
  <li>DallasTemperature.h</li>
  <li>EEPROM.h</li>
  <li>Preferences.h</li>
</ul>

<p>If you only want to install and use the code on your ESP32, you can find the latest binary file under the "Releases" section.</p>

# Installation

<ol>
  <li>Open the code in the Arduino IDE or any other compatible program that has the necessary libraries installed.</li>
  <li>Upload the code to your ESP32 by selecting the correct port and clicking the "Upload" button.</li>
  <li>Alternatively, you can download the binary file under the "Releases" section and use the included batch file named "flash." To do this, open the batch file and type in the COM port that your ESP32 is on, then press enter.</li>
  <li>To put the ESP32 into boot mode, press the "boot" button when prompted on the screen.</li>
</ol>

<p>Note: Make sure to follow any additional setup or configuration steps that may be necessary before uploading the code to your ESP32.</p>

# Usage
This code is specifically designed for the SR6 motherboard and will work optimally on it. It may also work on other ESP32 boards, but some features may not be fully functional.

This is the new features with their corresponding pin. On a 38-pin ESP32, some features will be missing if a 30-pin ESP32 is used.
<ul>
  <li>Pin 0: Twist feedback</li>
  <li>Pin 16: Case fan</li>
  <li>Pin 17: Squeeze servo</li>
  <li>Pin 18: Vibration channel 1</li>
  <li>Pin 21: OLED DSA</li>
  <li>Pin 22: OLED SCL</li>
  <li>Pin 26: Vibration channel 4</li>
  <li>Pin 33: Heater</li>
  <li>Pin 34: UP button</li>
  <li>Pin 35: ENT button</li>
  <li>Pin 39: DOWN button</li>
  <li>Pin 32: Internal temp sensor</li>
  <li>Pin 5: External temp sensor (Sleeve case)</li>
</ul>

# Contributing
If you encounter any bugs or errors while using this code, please let me know. Your assistance in identifying and resolving any issues is greatly appreciated.
