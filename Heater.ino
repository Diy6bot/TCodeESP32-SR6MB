void Heater() {
//--------------------------------HEATER CONTROL----------------------------------------
 
  if ((SLheater == 1) && (tempSensor1.getTempCByIndex(0) < 0)) {
  digitalWrite(HT_PIN, LOW);
  menuItem5 = "SL Heater: ON";
  } else if (tempSensor1.getTempCByIndex(0) > SLmaxTemp) {
  digitalWrite(HT_PIN, LOW); 
  } else {
  digitalWrite(HT_PIN, HIGH); 
  }   
    
  if (SLheater == 0){
  digitalWrite(HT_PIN, LOW);
   }
}
