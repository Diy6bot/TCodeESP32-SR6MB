void Display() {
//-------------------------------Bootom Text on OLED------------------------------------

 if ((SLheater == 1) && (tempSensor1.getTempCByIndex(0) < 0)){
  oled.setTextColor(WHITE);
  oled.setCursor(23, 20);
  oled.setTextSize(1);  // text size
  oled.print("No Tempsensor!");
  
  oled.setTextColor(WHITE);
  oled.setCursor(5, 0);
  oled.drawFastHLine(0,12,128,WHITE);
  oled.setTextSize(1);  // text size
  oled.print("INT ");
  oled.println(tempString2); // text to display

  oled.setTextColor(WHITE);  
  oled.setCursor(93, 0);
  oled.setTextSize(1);  // text size
  oled.print("READY");
  
 } else if (SLheater == 1){
  oled.setTextColor(WHITE);
  oled.setCursor(5, 18);
  oled.setTextSize(2);  // text size
  oled.print("SLT ");
  oled.println(tempString1); // text to display
  
  oled.setTextColor(WHITE);
  oled.setCursor(5, 0);
  oled.drawFastHLine(0,12,128,WHITE);
  oled.setTextSize(1);  // text size
  oled.print("INT ");
  oled.println(tempString2); // text to display
  
     if ((digitalRead(33) == HIGH) && (tempSensor1.getTempCByIndex(0) < SLmaxTemp)) {
  oled.setTextColor(WHITE);
  oled.setCursor(82, 0);
  oled.setTextSize(1);  // text size
  oled.print("HEATING");
   } else {
  oled.setTextColor(WHITE);  
  oled.setCursor(93, 0);
  oled.setTextSize(1);  // text size
  oled.print("READY");   
    }
  }

//-----------------------------------Top Text on OLED------------------------------------
else if (SLheater == 0){
  
  oled.setTextColor(WHITE);
  oled.setCursor(5, 0);
  oled.drawFastHLine(0,12,128,WHITE);
  oled.setTextSize(1);  // text size
  oled.print("INT ");
  oled.println(tempString2); // text to display

  oled.setTextColor(WHITE);  
  oled.setCursor(93, 0);
  oled.setTextSize(1);  // text size
  oled.print("READY");   
  }
  oled.display();
  oled.clearDisplay(); // clear display
  }
