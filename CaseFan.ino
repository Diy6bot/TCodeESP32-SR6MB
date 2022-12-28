void CaseFan() {
//---------------------------------------FAN PWM----------------------------------------
// For best noise to speed ratio keep the value between 50 & 1000 

auto temp = tempSensor2.getTempCByIndex(0);

if (temp >= 45) {
  ledcWrite(FanChannel, 800); 

} else if (temp >= 40) {
  ledcWrite(FanChannel, 500); 

} else if (temp >= 35) {
  ledcWrite(FanChannel, 200);

}else if (temp >= 30) {
  ledcWrite(FanChannel, 50);

} else {
  ledcWrite(FanChannel, 0);
  }
}