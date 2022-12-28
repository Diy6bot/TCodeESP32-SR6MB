void Setup() {

  // Start serial connection and report status
  tcode.StringInput("D0");
  tcode.StringInput("D1");

  // Set SR6 arms to startup positions
  if (!OSR2_MODE) { tcode.StringInput("R2750"); }

  // #ESP32# Enable EEPROM
  EEPROM.begin(320);

  // Register device axes
  tcode.RegisterAxis("L0", "Up");
  if (!OSR2_MODE) {
    tcode.RegisterAxis("L1", "Forward");
    tcode.RegisterAxis("L2", "Left");
  }
  tcode.RegisterAxis("R0", "Twist");
  tcode.RegisterAxis("R1", "Roll");
  tcode.RegisterAxis("R2", "Pitch");
  tcode.RegisterAxis("V0", "Vibe1");
  if (!LUBE_V1) { tcode.RegisterAxis("V1", "Vibe2"); }
  tcode.RegisterAxis("V2", "Vibe3");
  tcode.RegisterAxis("V3", "Vibe4");
  tcode.RegisterAxis("A0", "Valve");
  tcode.RegisterAxis("A1", "Suck");
  tcode.AxisInput("A1",VALVE_DEFAULT,'I',3000);
  if (LUBE_V1) {
    tcode.RegisterAxis("A2", "Lube");
    tcode.AxisInput("A2",0,' ',0);
    pinMode(Lube_PIN,INPUT);
  }
  tcode.RegisterAxis("A3", "Squeeze");  
  
  // Setup Servo PWM channels
  // Lower Left Servo
  ledcSetup(LowerLeftServo_PWM,MainServo_Freq,16);
  ledcAttachPin(LowerLeftServo_PIN,LowerLeftServo_PWM);
  // Upper Left Servo
  ledcSetup(UpperLeftServo_PWM,MainServo_Freq,16);
  ledcAttachPin(UpperLeftServo_PIN,UpperLeftServo_PWM);
  // Lower Right Servo
  ledcSetup(LowerRightServo_PWM,MainServo_Freq,16);
  ledcAttachPin(LowerRightServo_PIN,LowerRightServo_PWM);
  // Upper Right Servo
  ledcSetup(UpperRightServo_PWM,MainServo_Freq,16);
  ledcAttachPin(UpperRightServo_PIN,UpperRightServo_PWM);
  // Left Pitch Servo
  ledcSetup(LeftPitchServo_PWM,PitchServo_Freq,16);
  ledcAttachPin(LeftPitchServo_PIN,LeftPitchServo_PWM);
  // Right Pitch Servo
  ledcSetup(RightPitchServo_PWM,PitchServo_Freq,16);
  ledcAttachPin(RightPitchServo_PIN,RightPitchServo_PWM);
  // Twist Servo
  ledcSetup(TwistServo_PWM,TwistServo_Freq,16);
  ledcAttachPin(TwistServo_PIN,TwistServo_PWM);
  // Squeeze Servo
  ledcSetup(SqueezeServo_PWM,SqueezeServo_Freq,16);
  ledcAttachPin(SqueezeServo_PIN,SqueezeServo_PWM);
  // Valve Servo
  ledcSetup(ValveServo_PWM,ValveServo_Freq,16);
  ledcAttachPin(ValveServo_PIN,ValveServo_PWM);

  // Set vibration PWM pins
  // Vibe0 Pin
  ledcSetup(Vibe0_PWM,VibePWM_Freq,8);
  ledcAttachPin(Vibe0_PIN,Vibe0_PWM);
  // Vibe1 Pin
  ledcSetup(Vibe1_PWM,VibePWM_Freq,8);
  ledcAttachPin(Vibe1_PIN,Vibe1_PWM);
  // Vibe2 Pin
  ledcSetup(Vibe2_PWM,VibePWM_Freq,8);
  ledcAttachPin(Vibe2_PIN,Vibe2_PWM);
  // Vibe3 Pin
  ledcSetup(Vibe3_PWM,VibePWM_Freq,8);
  ledcAttachPin(Vibe3_PIN,Vibe3_PWM);

  // Initiate position tracking for twist
  if (TWIST_PARALLAX) {
    pinMode(TwistFeedback_PIN,INPUT);
    attachInterrupt(TwistFeedback_PIN, twistRising, RISING);
  }
  
  // Signal done
  Serial.println("Ready!");
  
}
