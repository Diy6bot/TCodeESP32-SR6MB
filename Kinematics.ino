void Kinematics() {
// ----------------------------
//   MAIN
// ----------------------------
// This loop runs continuously

  // Read serial and send to tcode class
  while (Serial.available() > 0) {
    // Send the serial bytes to the t-code object
    tcode.ByteInput(Serial.read());
  }

  // Collect inputs
  // These functions query the t-code object for the position/level at a specified time
  // Number recieved will be an integer, 0-9999
  xLin = tcode.AxisRead("L0");
  if (!OSR2_MODE) {
    yLin = tcode.AxisRead("L1");
    zLin = tcode.AxisRead("L2");
  }
  xRot = tcode.AxisRead("R0");
  yRot = tcode.AxisRead("R1");
  zRot = tcode.AxisRead("R2");
  vibe0 = tcode.AxisRead("V0");
  vibe2 = tcode.AxisRead("V2");
  vibe3 = tcode.AxisRead("V3");
  if (!LUBE_V1) { 
    vibe1 = tcode.AxisRead("V1"); 
  }
  valveCmd = tcode.AxisRead("A0");
  suckCmd = tcode.AxisRead("A1");
  if (LUBE_V1) { 
     lube = tcode.AxisRead("A2"); 
  }
  squeezeCmd = tcode.AxisRead("A3");
  
  // If you want to mix your servos differently, enter your code below:

  // If t-wist3, calculate twist position
  if (TWIST_PARALLAX) { 
    float dutyCycle = twistPulseLength;
    dutyCycle = dutyCycle/twistPulseCycle;
    float angPos = (dutyCycle - 0.029)/0.942;
    angPos = constrain(angPos,0,1) - 0.5;
    if (angPos - twistServoAngPos < - 0.8) { twistTurns += 1; }
    if (angPos - twistServoAngPos > 0.8) { twistTurns -= 1; }
    twistServoAngPos = angPos;
    twistPos = 1000*(angPos + twistTurns);
  }

  // Calculate valve position
  // Track receiver velocity
  unsigned long t = millis();
  float upVelNow;
  if (t > tLast) {
    upVelNow = xLin - xLast;
    upVelNow /= t - tLast;
    upVel = (upVelNow + 9*upVel)/10;
  }
  tLast = t;
  xLast = xLin;
  // Use suck command if most recent
  boolean suck;
  if (tcode.AxisLast("A1") >= tcode.AxisLast("A0")) {
    suck = true;
    valveCmd = suckCmd;
  } else {
    suck = false;
  }
  // Set valve position
  if (suck) {
    if (upVel < -5) {
      valveCmd = 0;  
    } else if ( upVel < 0 ) {
      valveCmd = map(100*upVel,0,-500,suckCmd,0);
    }
  }
  valvePos = (9*valvePos + map(valveCmd,0,9999,0,1000))/10;

  // OSR2 Kinematics
  if (OSR2_MODE) {
    // Calculate arm angles
    // Linear scale inputs to servo appropriate numbers
    int stroke,roll,pitch;
    stroke = map(xLin,0,9999,-350,350);
    roll   = map(yRot,0,9999,-180,180);
    pitch  = map(zRot,0,9999,-350,350);
    ledcWrite(LowerLeftServo_PWM, map(LowerLeftServo_ZERO + stroke + roll,0,MainServo_Int,0,65535));
    ledcWrite(LowerRightServo_PWM, map(LowerRightServo_ZERO - stroke + roll,0,MainServo_Int,0,65535));
    ledcWrite(LeftPitchServo_PWM, map(LeftPitchServo_ZERO - pitch,0,PitchServo_Int,0,65535));
    // Unused servo pins.
    ledcWrite(UpperLeftServo_PWM, map(UpperLeftServo_ZERO,0,MainServo_Int,0,65535));
    ledcWrite(RightPitchServo_PWM, map(RightPitchServo_ZERO,0,PitchServo_Int,0,65535));
    ledcWrite(UpperRightServo_PWM, map(UpperRightServo_ZERO,0,MainServo_Int,0,65535));
  }
  
  // SR6 Kinematics
  else {
    // Calculate arm angles
    int roll,pitch,fwd,thrust,side;
    int out1,out2,out3,out4,out5,out6;
    roll = map(yRot,0,9999,-3000,3000);
    pitch = map(zRot,0,9999,-2500,2500);
    fwd = map(yLin,0,9999,-3000,3000);
    thrust = map(xLin,0,9999,-6000,6000);
    side = map(zLin,0,9999,-3000,3000);
    // Main arms
    out1 = SetMainServo(16248 - fwd, 1500 + thrust + roll); // Lower left servo
    out2 = SetMainServo(16248 - fwd, 1500 - thrust - roll); // Upper left servo
    out5 = SetMainServo(16248 - fwd, 1500 - thrust + roll); // Upper right servo
    out6 = SetMainServo(16248 - fwd, 1500 + thrust - roll); // Lower right servo
    // Pitchers
    out3 = SetPitchServo(16248 - fwd, 4500 - thrust,  side - 1.5*roll, -pitch);
    out4 = SetPitchServo(16248 - fwd, 4500 - thrust, -side + 1.5*roll, -pitch);
    // Set Servos
    ledcWrite(LowerLeftServo_PWM, map(LowerLeftServo_ZERO - out1,0,MainServo_Int,0,65535));
    ledcWrite(UpperLeftServo_PWM, map(UpperLeftServo_ZERO + out2,0,MainServo_Int,0,65535));
    ledcWrite(LeftPitchServo_PWM, map(constrain(LeftPitchServo_ZERO - out3,LeftPitchServo_ZERO-600,LeftPitchServo_ZERO+1000),0,PitchServo_Int,0,65535));
    ledcWrite(RightPitchServo_PWM, map(constrain(RightPitchServo_ZERO + out4,RightPitchServo_ZERO-1000,RightPitchServo_ZERO+600),0,PitchServo_Int,0,65535));
    ledcWrite(UpperRightServo_PWM, map(UpperRightServo_ZERO - out5,0,MainServo_Int,0,65535));
    ledcWrite(LowerRightServo_PWM, map(LowerRightServo_ZERO + out6,0,MainServo_Int,0,65535));
  }

  // Twist, valve & squeeze
  int twist,valve,squeeze;
  
  if (TWIST_PARALLAX) { 
    twist  = (xRot - map(twistPos,-1500,1500,9999,0))/5;
    twist  = constrain(twist, -750, 750);
  } else {
    twist  = map(xRot,0,9999,1000,-1000);
    if (REVERSE_TWIST_SERVO) { twist = -twist; }
  }
  squeeze = map(squeezeCmd,0,9999,1000,-1000);
      if (REVERSE_SQUEEZE_SERVO) { squeeze = -squeeze; }
  valve  = valvePos - 500;
  valve  = constrain(valve, -500, 500);
  if (REVERSE_VALVE_SERVO) { valve = -valve; }
  // Set Servos
  ledcWrite(SqueezeServo_PWM, map(SqueezeServo_ZERO + squeeze,0,SqueezeServo_Int,0,65535));
  ledcWrite(TwistServo_PWM, map(TwistServo_ZERO + twist,0,TwistServo_Int,0,65535));
  ledcWrite(ValveServo_PWM, map(ValveServo_ZERO + valve,0,ValveServo_Int,0,65535));

  // Done with servo channels

  // Output vibration channels
  // These should drive PWM pins connected to vibration motors via MOSFETs or H-bridges.
  if (vibe0 > 0 && vibe0 <= 9999) {
    ledcWrite(Vibe0_PWM, map(vibe0,1,9999,31,255));
  } else {
    ledcWrite(Vibe0_PWM, 0);
  }
    if (!LUBE_V1 && vibe1 > 0 && vibe1 <= 9999) {
    ledcWrite(Vibe1_PWM, map(vibe1,1,9999,31,255));
  } else {
    ledcWrite(Vibe1_PWM, 0);
  }
  if (vibe2 > 0 && vibe2 <= 9999) {
    ledcWrite(Vibe2_PWM, map(vibe2,1,9999,31,255));
  } else {
    ledcWrite(Vibe2_PWM, 0);
  }
  if (vibe3 > 0 && vibe3 <= 9999) {
    ledcWrite(Vibe3_PWM, map(vibe3,1,9999,31,255));
  } else {
    ledcWrite(Vibe3_PWM, 0);
  }

  // Vibe timeout functions - shuts the vibne channels down if not commanded for a specified interval
  if (millis() - tcode.AxisLast("V0") > VIBE_TIMEOUT) { tcode.AxisInput("V0",0,'I',500); }
  if (!LUBE_V1 && millis() - tcode.AxisLast("V1") > VIBE_TIMEOUT) { tcode.AxisInput("V1",0,'I',500); }
  if (millis() - tcode.AxisLast("V2") > VIBE_TIMEOUT) { tcode.AxisInput("V2",0,'I',500); }
  if (millis() - tcode.AxisLast("V3") > VIBE_TIMEOUT) { tcode.AxisInput("V3",0,'I',500); }
  
  // Done with vibration channels

  // Lube functions
  if (LUBE_V1) {
    if (lube > 0 && lube <= 9999) {
      ledcWrite(Vibe1_PWM, map(lube,1,9999,127,255));
    } else if (digitalRead(Lube_PIN) == HIGH) {
      ledcWrite(Vibe1_PWM,Lube_SPEED);
    } else { 
      ledcWrite(Vibe1_PWM,0);
    }
    if (millis() - tcode.AxisLast("A2") > 500) { tcode.AxisInput("A2",0,' ',0); } // Auto cutoff
  }
  // Done with lube
}

// Function to calculate the angle for the main arm servos
// Inputs are target x,y coords of receiver pivot in 1/100 of a mm
int SetMainServo(float x, float y) {
  x /= 100; y /= 100;          // Convert to mm
  float gamma = atan2(x,y);    // Angle of line from servo pivot to receiver pivot
  float csq = sq(x) + sq(y);   // Square of distance between servo pivot and receiver pivot
  float c = sqrt(csq);         // Distance between servo pivot and receiver pivot
  float beta = acos((csq - 28125)/(100*c));  // Angle between c-line and servo arm
  int out = ms_per_rad*(gamma + beta - 3.14159); // Servo signal output, from neutral
  return out;
}

// Function to calculate the angle for the pitcher arm servos
// Inputs are target x,y,z coords of receiver upper pivot in 1/100 of a mm
// Also pitch in 1/100 of a degree
int SetPitchServo(float x, float y, float z, float pitch) {
  pitch *= 0.0001745; // Convert to radians
  x += 5500*sin(0.2618 + pitch);
  y -= 5500*cos(0.2618 + pitch);
  x /= 100; y /= 100; z /= 100;   // Convert to mm
  float bsq = 36250 - sq(75 + z); // Equivalent arm length
  float gamma = atan2(x,y);       // Angle of line from servo pivot to receiver pivot
  float csq = sq(x) + sq(y);      // Square of distance between servo pivot and receiver pivot
  float c = sqrt(csq);            // Distance between servo pivot and receiver pivot
  float beta = acos((csq + 5625 - bsq)/(150*c)); // Angle between c-line and servo arm
  int out = ms_per_rad*(gamma + beta - 3.14159); // Servo signal output, from neutral
  return out;
}

// T-wist3 parallax position detection functions
void twistRising() {
  attachInterrupt(TwistFeedback_PIN, twistFalling, FALLING);
  twistPulseCycle = micros()-twistPulseStart;
  twistPulseStart = micros();
}
void twistFalling() {
  attachInterrupt(TwistFeedback_PIN, twistRising, RISING);
  twistPulseLength = micros()-twistPulseStart;
}
