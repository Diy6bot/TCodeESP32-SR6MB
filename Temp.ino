void Temp() {
//-------------------------------------TEMP---------------------------------------------
  if (SLheater == 1){
    
  tempSensor1.requestTemperatures();  // send the command to get temperatures
  float tempCelsius1 = tempSensor1.getTempCByIndex(0);  // read temperature in Celsius
  tempString1  = String(tempCelsius1, 2); // two decimal places
  tempString1 += ("C");

  tempSensor2.requestTemperatures();  // send the command to get temperatures
  float tempCelsius2 = tempSensor2.getTempCByIndex(0);  // read temperature in Celsius  
  tempString2  = String(tempCelsius2, 2); // two decimal places
  tempString2 += ("C |");
  }
  
  else if (SLheater == 0){
    
  tempSensor2.requestTemperatures();  // send the command to get temperatures
  float tempCelsius2 = tempSensor2.getTempCByIndex(0);  // read temperature in Celsius  
  tempString2  = String(tempCelsius2, 2); // two decimal places
  tempString2 += ("C |");
  
  }
}
