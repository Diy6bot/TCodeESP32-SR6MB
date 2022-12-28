// Orginal Code Made by TempestMAx 5-3-22
// Please copy, share, learn, innovate, give attribution.
// Decodes T-code commands and uses them to control servos and vibration motors
// It can handle:
//   10x linear channels (L0, L1, L2... L9)
//   10x rotation channels (R0, R1, R2... L9) 
//   10x vibration channels (V0, V1, V2... V9)
//   10x auxilliary channels (A0, A1, A2... A9) 
// but is also able to drive the OSR2. See below for servo pin assignments
// Have fun, play safe!
// History:
// Alpha3 - First ESP32 release, 9-7-21
// Alpha4 - Support for T-wist 4 added - standard servo now default, parallax is an option, 5-3-22

// ----------------------------
//   Added features
// ----------------------------

// TCodeESP32-SR6MB v1.38b
// This code is a modedfied version by Crimzzon, of the orginal code from TempestMAx
// This code is for the "ESP32 DevKitC v4" and is designed to drive the SR6 stroker robot
// This code runs on a "ESP32 Dual Core" setup, whit the SR6-MB

// In this code there is additional functions added, see the list bellow

// #1 Internal case temp sensor reading
// #2 External sleeve temp sensor reading 
// #3 Squeeze servo channel
// #4 Case fan controlled by pwm, set by the internal case temp sensor
// #5 Support for 128x32 OLED display
// #6 Added 2 extra vibe channels
// #7 A Menu system making it posible to change settings

// ----------------------------
//   Settings
// ----------------------------

// Device IDs, for external reference
#define FIRMWARE_ID "TCodeESP32-SR6MB_v1.38b.ino"  // Device and firmware version
#define TCODE_VER "TCode v0.3"                           // Current version of TCode

// Turn Diffrent Functions On/Off
#define OSR2_MODE false       // (true/false) Switch servo outputs to OSR2 mode

// Servo microseconds per radian
// (Standard: 637 μs/rad)
// (LW-20: 700 μs/rad)
#define ms_per_rad ServoDEG  // (μs/rad) 954 = 120 deegre /  637 = 180 deegre / 425 = 270 deegre / 318 = 360 deegre 

// Pin assignments
// T-wist feedback goes on digital pin 2
#define LowerLeftServo_PIN 15    // Lower Left Servo (OSR2 Left Servo)
#define UpperLeftServo_PIN 2     // Upper Left Servo
#define LowerRightServo_PIN 13   // Lower Right Servo (OSR2 Right Servo)
#define UpperRightServo_PIN 12   // Upper Right Servo
#define LeftPitchServo_PIN 4     // Left Pitch Servo (OSR2 Pitch Servo)
#define RightPitchServo_PIN 14   // Right Pitch Servo
#define TwistServo_PIN 27        // Twist Servo
#define ValveServo_PIN 25        // Valve Servo
#define TwistFeedback_PIN 0      // Twist Servo Feedback (Not supported but can be used through the "Boot pin")
#define SqueezeServo_PIN 17      // Squeeze Servo
#define Vibe0_PIN 18             // Vibration motor 1
#define Vibe1_PIN 19             // Vibration motor 2
#define Vibe2_PIN 23             // Vibration motor 3
#define Vibe3_PIN 26             // Vibration motor 4
#define SENSOR1_PIN 5            // Temp sensor for HT temp
#define SENSOR2_PIN 32           // Temp sensor for Case temp
#define HT_PIN 33                // Arduino pin connected to Heater element
#define EXT1 35                  // Extra pin (Input only & need external pulupp resistor)
#define EXT2 34                  // Extra pin (Input only & need external pulupp resistor)
#define EXT3 39                  // Extra pin (Input only & need external pulupp resistor)
#define EXT4 36                  // Extra pin (Input only & need external pulupp resistor)

// Arm servo zeros
// Change these to adjust arm positions
// (1500 = centre, 1 complete step = 160)
// Right = (Lower nummer is forword)
// Left  = (Higher nummer is forword)

//----------------------Change the position of the arms-------------------------
/* 
How the arms should be positioned in different states, sen from the side
            Boot               Home
---------------------------------------------------  
Pitch       <|              <|
            |                |
           o                 o
---------------------------------------------------             
Upper       <|                 <|
             |                  |
             o                  o  
---------------------------------------------------            
Lower       <|                 <|
             |                  |
             o                  o
---------------------------------------------------               
*/
#define UpperLeftServo_ZERO LeftUpperServo      // Upper Left Servo
#define UpperRightServo_ZERO RightUpperServo    // Upper Right Servo

#define LowerLeftServo_ZERO LeftLowerServo      // Lower Left Servo (OSR2 Left Servo)
#define LowerRightServo_ZERO RightLowerServo    // Lower Right Servo (OSR2 Right Servo)

#define LeftPitchServo_ZERO LeftPitchServo      // Left Pitch Servo (OSR2 Pitch Servo)
#define RightPitchServo_ZERO RightPitchServo    // Right Pitch Servo

#define TwistServo_ZERO TwistServo              // Twist Servo
#define ValveServo_ZERO ValvServo               // Valve Servo
#define SqueezeServo_ZERO SqueezeServo          // Squeeze Servo

//--------------------------------------------------------------------------------

// Servo operating frequencies
#define PitchServo_Freq PitchFrequens           // Pitch Servos
#define MainServo_Freq MainFrequens             // Main Servos
#define TwistServo_Freq TwistFrequens           // Twist Servo
#define ValveServo_Freq ValvFrequens            // Valve Servo
#define SqueezeServo_Freq SqueezeFrequens       // Squeeze Servo
#define VibePWM_Freq VibeFrequens               // Vibe motor control PWM frequency

// Other functions
#define TWIST_PARALLAX TwistPax                 // (true/false) Parallax 360 feedback servo on twist (t-wist3)
#define REVERSE_TWIST_SERVO ReverseTwist        // (true/false) Reverse twist servo direction 
#define VALVE_DEFAULT 5000                      // Auto-valve default suction level (low-high, 0-9999) 
#define REVERSE_VALVE_SERVO ReverseValv         // (true/false) Reverse T-Valve direction
#define REVERSE_SQUEEZE_SERVO ReverseSqueeze
#define VIBE_TIMEOUT 2000                       // Timeout for vibration channels (milliseconds).
#define LUBE_V1 LubePump                           // (true/false) Lube pump installed instead of vibration channel 1
#define Lube_PIN 36                             // Lube manual input button pin (Connect pin to +5V for ON) Conect to EXT4
#define Lube_SPEED 255                          // Lube pump speed (0-255)
#define MIN_SMOOTH_INTERVAL 3                   // Minimum auto-smooth ramp interval for live commands (ms)
#define MAX_SMOOTH_INTERVAL 100                 // Maximum auto-smooth ramp interval for live commands (ms)

// T-Code Channels
#define CHANNELS 10                             // Number of channels of each type (LRVA)

// ----------------------------
//  Auto Settings
// ----------------------------
// Do not change
// Servo PWM channels
#define LowerLeftServo_PWM 0     // Lower Left Servo
#define UpperLeftServo_PWM 1     // Upper Left Servo
#define LowerRightServo_PWM 2    // Lower Right Servo
#define UpperRightServo_PWM 3    // Upper Right Servo
#define LeftPitchServo_PWM 4     // Left Pitch Servo
#define RightPitchServo_PWM 5    // Right Pitch Servo
#define TwistServo_PWM 6         // Twist Servo
#define ValveServo_PWM 7         // Valve Servo
#define TwistFeedback_PWM 8      // Twist Servo
#define SqueezeServo_PWM 14      // Squeeze Servo
#define Vibe0_PWM 9              // Vibration motor 1
#define Vibe1_PWM 10             // Vibration motor 2
#define Vibe2_PWM 13             // Vibration motor 2
#define Vibe3_PWM 12             // Vibration motor 2

// Servo Pulse intervals
#define MainServo_Int 1000000/MainServo_Freq
#define PitchServo_Int 1000000/PitchServo_Freq
#define TwistServo_Int 1000000/TwistServo_Freq
#define SqueezeServo_Int 1000000/SqueezeServo_Freq
#define ValveServo_Int 1000000/ValveServo_Freq

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Libraries used
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>        // OLED
#include <Adafruit_SSD1306.h>    // OLED
#include <OneWire.h>
#include <DallasTemperature.h>
#include <EEPROM.h>             // Permanent memory for Tempes TCode
#include <Preferences.h>        // Permanent memory for settings menu

//------Main Menu settings variables-------
int SLheater;
int SLmaxTemp;
int ServoDEG;
int LubePump;

//------Servo position Menu variables-------
int LeftPitchServo;
int RightPitchServo;
int LeftUpperServo;
int RightUpperServo;
int LeftLowerServo;
int RightLowerServo;
int TwistServo;
int SqueezeServo;
int ValvServo;

//------Advanced Servo Menu variables-------
int PitchFrequens;
int MainFrequens;
int TwistFrequens;
int SqueezeFrequens;
int ValvFrequens;
int VibeFrequens;
int TwistPax;
int ReverseTwist;
int ReverseSqueeze;
int ReverseValv;

//------Main menu settings-------
int menuitem = 1;
int frame = 1;
int page = 2;
int lastMenuItem = 1;

String menuItem1 = "<--DISPLAY INFO--";
String menuItem2 = "SL Max Temp";
String menuItem3 = "Servo Settings";
String menuItem4 = "Servo Angel";
String menuItem5 = "SL Heater:";
String menuItem6 = "Lube Pump:";
String menuItem7 = "Reset To Defult";

String Servodegree[4] = { "120 degrees", "180 degrees", "270 degrees", "360 degrees" };
int selectedServodegree = 1;

//------Servo position menu settings-------
int submenuitem = 1;
int subframe = 1;
int subpage = 1;
int sublastmenuitem = 1;

String submenuitem1 = "<---MAIN MENU---";
String submenuitem2 = "Pitch Left Center";
String submenuitem3 = "Pitch Right Center";
String submenuitem4 = "Upper Left Center";
String submenuitem5 = "Upper Right Center";
String submenuitem6 = "Lower Left Center";
String submenuitem7 = "Lower Right Center";
String submenuitem8 = "Twist Servo Center";
String submenuitem9 = "Squeeze Servo Center";
String submenuitem10 = "Valv Servo Center";
String submenuitem11 = "ADVANCED SETTINGS-->";

//------Servo Menu Advanced Settings-------
int ASsubmenuitem = 1;
int ASsubframe = 1;
int ASsubpage = 1;
int ASsublastmenuitem = 1;

String ASsubmenuitem1 = "<---SERVO MENU---";
String ASsubmenuitem2 = "Pitch Servo Freq";
String ASsubmenuitem3 = "Main Servo Freq";
String ASsubmenuitem4 = "Twist Servo Freq";
String ASsubmenuitem5 = "Squeese Servo Freq";
String ASsubmenuitem6 = "Valv Servo Freq";
String ASsubmenuitem7 = "Vibe Motor Freq";
String ASsubmenuitem8 = "Twist Paralax:";
String ASsubmenuitem9 = "Reverse Twist:";
String ASsubmenuitem10 = "Reverse Valv:";
String ASsubmenuitem11 = "Reverse Squeeze:";

//-----------------------------------------

volatile boolean up = false;
volatile boolean down = false;
volatile boolean middle = false;

int downButtonState = 0;
int upButtonState = 0;  
int selectButtonState = 0;          
int lastDownButtonState = 0;
int lastSelectButtonState = 0;
int lastUpButtonState = 0;

//--------PWM settings for case fan--------
const int freq = 25;        // Case Fan frequensy
const int FanChannel = 11;  // Case Fan chanmel
const int resolution = 10;  // Case Fan resolution
const int FanPin = 16;      // Case Fan Pin
//-----------------------------------------

String tempString1;
String tempString2;

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // create SSD1306 display object connected to I2C

OneWire oneWire1(SENSOR1_PIN);               // setup a oneWire instance
OneWire oneWire2(SENSOR2_PIN);               // setup a oneWire instance
DallasTemperature tempSensor1(&oneWire1);    // pass oneWire to DallasTemperature library
DallasTemperature tempSensor2(&oneWire2);    // pass oneWire to DallasTemperature library
Preferences preferences;
// -----------------------------
// Class to handle each axis
// -----------------------------
class Axis {
  public:
  // Setup function
  Axis() {

    // Set default dynamic parameters
    rampStartTime = 0;
    rampStart = 5000;
    rampStopTime = rampStart;
    rampStop = rampStart;

    // Set Empty Name
    Name = "";
    lastT = 0;

    // Live command auto-smooth
    minInterval = MAX_SMOOTH_INTERVAL; 
  }

  // Function to set the axis dynamic parameters
  void Set(int x, char ext, long y) {
    unsigned long t = millis(); // This is the time now
    x = constrain(x,0,9999);
    y = constrain(y,0,9999999);
    // Set ramp parameters, based on inputs
    // Live command
    if ( y == 0 || ( ext != 'S' && ext != 'I' ) ) {
      // update auto-smooth regulator
      int lastInterval = t - rampStartTime;
      if ( lastInterval > minInterval && minInterval < MAX_SMOOTH_INTERVAL ) { minInterval += 1; }
      else if ( lastInterval < minInterval && minInterval > MIN_SMOOTH_INTERVAL ) { minInterval -= 1; } 
      // Set ramp parameters
      rampStart = GetPosition();
      rampStopTime = t + minInterval;  
    } 
    // Speed command
    else if ( ext == 'S' ) {
      rampStart = GetPosition();  // Start from current position
      int d = x - rampStart;  // Distance to move
      if (d<0) { d = -d; }
      long dt = d;  // Time interval (time = dist/speed)
      dt *= 100;
      dt /= y; 
      rampStopTime = t + dt;  // Time to arrive at new position
      //if (rampStopTime < t + minInterval) { rampStopTime = t + minInterval; }
    }
    // Interval command
    else if ( ext == 'I' ) {
      rampStart = GetPosition();  // Start from current position
      rampStopTime = t + y;  // Time to arrive at new position
      //if (rampStopTime < t + minInterval) { rampStopTime = t + minInterval; }
    }
    rampStartTime = t;
    rampStop = x;
    lastT = t;
  }

  // Function to return the current position of this axis
  int GetPosition() {
    int x; // This is the current axis position, 0-9999
    unsigned long t = millis(); 
    if (t > rampStopTime) {
      x = rampStop;
    } else if (t > rampStartTime) { 
      x = map(t,rampStartTime,rampStopTime,rampStart,rampStop);
    } else {
      x = rampStart;
    }
    x = constrain(x,0,9999);
    return x;
  }

  // Function to stop axis movement at current position
  void Stop() {
    unsigned long t = millis(); // This is the time now
    rampStart = GetPosition();
    rampStartTime = t;
    rampStop = rampStart;
    rampStopTime = t;
  }

  // Public variables
  String Name;  // Function name of this axis
  unsigned long lastT;  //

  private:
  
  // Movement positions
  int rampStart;
  unsigned long rampStartTime;
  int rampStop;
  unsigned long rampStopTime;

  // Live command auto-smooth regulator
  int minInterval;
};

// -----------------------------
// Class to manage Toy Comms
// -----------------------------
class TCode {
  
  public:
  // Setup function
  TCode(String firmware, String tcode) {
    firmwareID = firmware;
    tcodeID = tcode;

    // Vibe channels start at 0
    for (int i = 0; i < CHANNELS; i++) { Vibration[i].Set(0,' ',0); }
    
  }

  // Function to name and activate axis
  void RegisterAxis(String ID, String axisName) {
    char type = ID.charAt(0);
    int channel = ID.charAt(1) - '0';
    if ((0 <= channel && channel < CHANNELS)) {
      switch(type) {
        // Axis commands
        case 'L': Linear[channel].Name = axisName; break;
        case 'R': Rotation[channel].Name = axisName; break;
        case 'V': Vibration[channel].Name = axisName; break;
        case 'A': Auxiliary[channel].Name = axisName; break;
      }
    }
  }

  // Function to read off individual bytes as input
  void ByteInput(byte inByte) {
    bufferString += (char)inByte;  // Add new character to string
    
    if (inByte=='\n') {  // Execute string on newline
      bufferString.trim();  // Remove spaces, etc, from buffer
      executeString(bufferString); // Execute string
      bufferString = ""; // Clear input string
    }
  }

  // Function to read off whole strings as input
  void StringInput(String inString) {
    bufferString = inString;  // Replace existing buffer with input string
    bufferString.trim();  // Remove spaces, etc, from buffer
    executeString(bufferString); // Execute string
    bufferString = ""; // Clear input string
  }

  // Function to set an axis
  void AxisInput(String ID, int magnitude, char extension, long extMagnitude) {
    char type = ID.charAt(0);
    int channel = ID.charAt(1) - '0';
    if ((0 <= channel && channel < CHANNELS)) {
      switch(type) {
        // Axis commands
        case 'L': Linear[channel].Set(magnitude,extension,extMagnitude); break;
        case 'R': Rotation[channel].Set(magnitude,extension,extMagnitude); break;
        case 'V': Vibration[channel].Set(magnitude,extension,extMagnitude); break;
        case 'A': Auxiliary[channel].Set(magnitude,extension,extMagnitude); break;
      }
    }
  }

  // Function to read the current position of an axis
  int AxisRead(String ID) {
    int x = 5000; // This is the return variable
    char type = ID.charAt(0);
    int channel = ID.charAt(1) - '0';
    if ((0 <= channel && channel < CHANNELS)) {
      switch(type) {
        // Axis commands
        case 'L': x = Linear[channel].GetPosition(); break;
        case 'R': x = Rotation[channel].GetPosition(); break;
        case 'V': x = Vibration[channel].GetPosition(); break;
        case 'A': x = Auxiliary[channel].GetPosition(); break;
      }
    }
    return x;
  }

  // Function to query when an axis was last commanded
  unsigned long AxisLast(String ID) {
    unsigned long t = 0; // Return time
    char type = ID.charAt(0);
    int channel = ID.charAt(1) - '0';
    if ((0 <= channel && channel < CHANNELS)) {
      switch(type) {
        // Axis commands
        case 'L': t = Linear[channel].lastT; break;
        case 'R': t = Rotation[channel].lastT; break;
        case 'V': t = Vibration[channel].lastT; break;
        case 'A': t = Auxiliary[channel].lastT; break;
      }
    }
    return t;
  }

  private:
  // Strings
  String firmwareID;
  String tcodeID;
  String bufferString; // String to hold incomming commands

  // Declare axes
  Axis Linear[CHANNELS];
  Axis Rotation[CHANNELS];
  Axis Vibration[CHANNELS];
  Axis Auxiliary[CHANNELS];

  // Function to divide up and execute input string
  void executeString(String bufferString) {
    int index = bufferString.indexOf(' ');  // Look for spaces in string
    while (index > 0) {
      readCmd(bufferString.substring(0,index));  // Read off first command
      bufferString = bufferString.substring(index+1);  // Remove first command from string
      bufferString.trim();
      index = bufferString.indexOf(' ');  // Look for next space
    }
    readCmd(bufferString);  // Read off last command
  }

  // Function to process the individual commands
  void readCmd(String command) {
    command.toUpperCase();
  
    // Switch between command types
    switch( command.charAt(0) ) {
      // Axis commands
      case 'L':
      case 'R':
      case 'V':
      case 'A':
        axisCmd(command);
      break;
  
      // Device commands
      case 'D':
        deviceCmd(command);
      break;
  
      // Setup commands
      case '$':
        setupCmd(command);
      break; 
    }
  }

  // Function to read and interpret axis commands
  void axisCmd(String command) {
  
    char type = command.charAt(0);  // Type of command - LRVA
    boolean valid = true;  // Command validity flag, valid by default
  
    // Check for channel number
    int channel = command.charAt(1) - '0';
    if (channel < 0 || channel >= CHANNELS) {valid = false;}
    channel = constrain(channel,0,CHANNELS);
  
    // Check for an extension
    char extension = ' ';
    int index = command.indexOf('S',2);
    if (index > 0) {
      extension = 'S';
    } else {
      index = command.indexOf('I',2);
      if (index > 0) {
        extension = 'I';
      }
    }
    if (index < 0) { index = command.length(); }
    
    // Get command magnitude
    String magString = command.substring(2,index);
    magString = magString.substring(0,4);
    while (magString.length() < 4) { magString += '0'; }
    int magnitude = magString.toInt();
    if (magnitude == 0 && magString.charAt(0) != '0') { valid = false; } // Invalidate if zero returned, but not a number
  
    // Get extension magnitude
    long extMagnitude = 0;
    if ( extension != ' ') {
      magString = command.substring(index+1);
      magString = magString.substring(0,8);
      extMagnitude = magString.toInt();
    }
    if (extMagnitude == 0) { extension = ' '; }

    // Switch between command types
    if (valid) {
      switch(type) {
        // Axis commands
        case 'L': Linear[channel].Set(magnitude,extension,extMagnitude); break;
        case 'R': Rotation[channel].Set(magnitude,extension,extMagnitude); break;
        case 'V': Vibration[channel].Set(magnitude,extension,extMagnitude); break;
        case 'A': Auxiliary[channel].Set(magnitude,extension,extMagnitude); break;
      }
    }
  }

  // Function to identify and execute device commands
  void deviceCmd(String command) {
    int i;
    // Remove "D"
    command = command.substring(1);

    // Look for device stop command
    if (command.substring(0,4) == "STOP") {
        for (i = 0; i < 10; i++) { Linear[i].Stop(); }
        for (i = 0; i < 10; i++) { Rotation[i].Stop(); }
        for (i = 0; i < 10; i++) { Vibration[i].Set(0,' ',0); }
        for (i = 0; i < 10; i++) { Auxiliary[i].Stop(); }  
    } else {
      // Look for numbered device commands
      int commandNumber = command.toInt();
      if (commandNumber==0 && command.charAt(0)!='0' ) { command = -1; }
      switch( commandNumber ) {
        case 0:
          Serial.println(firmwareID);
        break;
  
        case 1:
          Serial.println(tcodeID);
        break;
  
        case 2:
          for (i = 0; i < 10; i++) { axisRow("L" + String(i), 8*i, Linear[i].Name); }
          for (i = 0; i < 10; i++) { axisRow("R" + String(i), 8*i+80, Rotation[i].Name); }
          for (i = 0; i < 10; i++) { axisRow("V" + String(i), 8*i+160, Vibration[i].Name); }
          for (i = 0; i < 10; i++) { axisRow("A" + String(i), 8*i+240, Auxiliary[i].Name); }             
        break;
      }
    }   
  }

  // Function to modify axis preference values
  void setupCmd(String command) {
    int minVal,maxVal;
    String minValString,maxValString;
    boolean valid;
    // Axis type
    char type = command.charAt(1); 
    switch (type) {
      case 'L':
      case 'R':
      case 'V':
      case 'A':
      valid = true;
      break;

      default:
      type = ' ';
      valid = false;
      break;
    }
    // Axis channel number
    int channel = (command.substring(2,3)).toInt();
    if (channel == 0 && command.charAt(2) != '0') {
      valid = false;
    }
    // Input numbers
    int index1 = command.indexOf('-');  
    if (index1 !=3) { valid = false; }
    int index2 = command.indexOf('-',index1+1);  // Look for spaces in string
    if (index2 <=3) { valid = false; }
    if (valid) {
      // Min value
      minValString = command.substring(4,index2);
      minValString = minValString.substring(0,4);
      while (minValString.length() < 4) { minValString += '0'; }
      minVal = minValString.toInt();
      if ( minVal == 0 && minValString.charAt(0)!='0' ) { valid = false; }
      // Max value
      maxValString = command.substring(index2+1);
      maxValString = maxValString.substring(0,4);
      while (maxValString.length() < 4) { maxValString += '0'; }
      maxVal = maxValString.toInt();
      if ( maxVal == 0 && maxValString.charAt(0)!='0' ) { valid = false; }     
    }
    // If a valid command, save axis preferences to EEPROM
    if (valid) {
      int memIndex = 0;
      switch (type) {
        case 'L': memIndex = 0; break;
        case 'R': memIndex = 80; break;
        case 'V': memIndex = 160; break;
        case 'A': memIndex = 240; break;
      }
      memIndex += 8*channel;
      minVal = constrain(minVal,0,9999);
      EEPROM.put(memIndex, minVal-1);
      minVal = constrain(maxVal,0,9999);
      EEPROM.put(memIndex+4, maxVal-10000);
      // Output that axis changed successfully
      switch (type) {
        case 'L': axisRow("L" + String(channel), memIndex, Linear[channel].Name); break;
        case 'R': axisRow("R" + String(channel), memIndex, Rotation[channel].Name); break;
        case 'V': axisRow("V" + String(channel), memIndex, Vibration[channel].Name); break;
        case 'A': axisRow("A" + String(channel), memIndex, Auxiliary[channel].Name); break;             
      }
    }
  }
 
  // Function to print the details of an axis
  void axisRow(String axisID, int memIndex, String axisName) {
    int low, high;
    if (axisName != "") {
      EEPROM.get(memIndex,low);
      low = constrain(low,-1,9998);
      EEPROM.get(memIndex + 4,high);
      high = constrain(high,-10000,-1);
      Serial.print(axisID);
      Serial.print(" ");
      Serial.print(low + 1);
      Serial.print(" ");
      Serial.print(high + 10000);
      Serial.print(" ");
      Serial.println(axisName);
    }
  }    
};

// ----------------------------
//   SETUP
// ----------------------------
// This code runs once, on startup
// Declare classes
// This uses the t-code object above
TCode tcode(FIRMWARE_ID, TCODE_VER);

// Declare operating variables
// Position variables
int xLin,yLin,zLin;
// Rotation variables
int xRot,yRot,zRot;
// Vibration variables
int vibe0,vibe1,vibe2,vibe3;
// Lube variables
int lube;
// Valve variables
int valveCmd,suckCmd,squeezeCmd;
// Velocity tracker variables, for valve
int xLast;
unsigned long tLast;
float upVel,valvePos;
// Twist position monitor variables
volatile int twistPulseLength = 0;
volatile int twistPulseCycle = 1099;
volatile int twistPulseStart = 0;
float twistServoAngPos = 0.5;
int twistTurns = 0;
float twistPos;

//---------------------Dual core setup--------------------
TaskHandle_t task_loop1;
void esploop1(void* pvParameters) {
  setup1();

  for (;;)
    loop1();
}

void setup() {

  Serial.begin(115200);
  xTaskCreatePinnedToCore(
    esploop1,               /* Task function. */
    "loop1",                /* name of task. */
    10000,                  /* Stack size of task */
    NULL,                   /* parameter of the task */
    1,                      /* priority of the task */
    &task_loop1,            /* Task handle to keep track of created task */
    !ARDUINO_RUNNING_CORE); /* pin task to core */
    
  Setup();
}
void setup1() {
  preferences.begin("Settings", false);

  //-----------------Temp, Heat & Servo Deegre---------------
  
  SLmaxTemp = preferences.getInt("SLmaxTemp",  40);
  SLheater = preferences.getInt("SLheater",  0);
  ServoDEG = preferences.getInt("ServoDEG",  637);
  LubePump = preferences.getInt("LubePump",  0);

//-------------------------Position------------------------
  
  LeftPitchServo = preferences.getInt("LeftPitchServo",  1500);
  RightPitchServo = preferences.getInt("RightPitchServo",  1500);
  LeftUpperServo = preferences.getInt("LeftUpperServo",  1500);
  RightUpperServo = preferences.getInt("RightUpperServo",  1500);
  LeftLowerServo = preferences.getInt("LeftLowerServo",  1500);
  RightLowerServo = preferences.getInt("RightLowerServo",  1500);
  TwistServo = preferences.getInt("TwistServo",  1500);
  SqueezeServo = preferences.getInt("SqueezeServo",  1500);
  ValvServo = preferences.getInt("ValvServo",  1500);       
 
//-------------------------Frequens------------------------

  PitchFrequens = preferences.getInt("PitchFrequens",  330);
  MainFrequens = preferences.getInt("MainFrequens",  330);
  TwistFrequens = preferences.getInt("TwistFrequens",  50);
  SqueezeFrequens = preferences.getInt("SqueezeFrequens",  50);
  ValvFrequens = preferences.getInt("ValvFrequens",  50);
  VibeFrequens = preferences.getInt("VibeFrequens",  8000);
  TwistPax = preferences.getInt("TwistPax",  0);
  ReverseTwist = preferences.getInt("ReverseTwist",  0);
  ReverseSqueeze = preferences.getInt("ReverseSqueeze",  0);
  ReverseValv = preferences.getInt("ReverseValv",  0);

  if (TwistPax == 1){
  ASsubmenuitem8 = "Twist Paralax: ON";
  }else{
  ASsubmenuitem8 = "Twist Paralax: OFF"; 
  }
  
  if (ReverseTwist == 1){
  ASsubmenuitem9 = "Reverse Twist: ON";
  }else{
  ASsubmenuitem9 = "Reverse Twist: OFF"; 
  }

  if (ReverseValv == 1){
  ASsubmenuitem10 = "Reverse Valv: ON";
  }else{
  ASsubmenuitem10 = "Reverse Valv: OFF"; 
  }

  if (ReverseSqueeze == 1){
  ASsubmenuitem11 = "Reverse Squeeze: ON";
  }else{
  ASsubmenuitem11 = "Reverse Squeeze: OFF"; 
  }
  
  if (SLheater == 1){
  menuItem5 = "SL Heater: ON";
  }else{
  menuItem5 = "SL Heater: OFF"; 
  }

  if (LubePump == 1){
  menuItem6 = "Lube Pump: ON";
  }else{
  menuItem6 = "Lube Pump: OFF"; 
  }

  pinMode(HT_PIN, OUTPUT);
  pinMode(EXT1, INPUT);
  pinMode(EXT2, INPUT);
  pinMode(EXT3, INPUT);
  pinMode(EXT4, INPUT);

  bool gpio_35_state = digitalRead(EXT1);
  bool gpio_34_state = digitalRead(EXT2);
  bool gpio_39_state = digitalRead(EXT3);
  bool gpio_36_state = digitalRead(EXT4);
    
    // initialize OLED display with I2C address 0x3C
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("failed to start SSD1306 OLED"));
    while (1);
  }
  
  StartScreen();

  tempSensor1.begin(); // initialize the sensor
  tempSensor1.setResolution(9);
  tempSensor1.setWaitForConversion(false);
  tempString1.reserve(10); // to avoid fragmenting memory when using String

  tempSensor2.begin(); // initialize the sensor
  tempSensor2.setResolution(9);
  tempSensor2.setWaitForConversion(false);
  tempString2.reserve(10); // to avoid fragmenting memory when using String

  ledcSetup(FanChannel, freq, resolution);   // configure LED PWM functionalitites
  ledcAttachPin(FanPin, FanChannel);   // attach the channel to the GPIO to be controlled
}

void loop() {
  Kinematics();
}

void loop1() {
  Temp();
  Heater();   
  CaseFan();
  Menu();

//--------Keeps the Min & Max Temp Between 35 & 45 Degrees--------

  SLmaxTemp = preferences.getInt("SLmaxTemp",  SLmaxTemp);

  if (SLmaxTemp < 35){
  SLmaxTemp = preferences.putInt("SLmaxTemp",  45);
  } else if (SLmaxTemp > 45){
  SLmaxTemp = preferences.putInt("SLmaxTemp",  35);
  }

  }
