void StartScreen() { 
  oled.clearDisplay();
  oled.setTextSize(1);  // text size
  oled.setTextColor(WHITE);  // text color
  oled.setCursor(32, 0);  // position to display
  oled.print("diy6bot.com");
  oled.setCursor(35, 16);  // position to display
  oled.print("TCode v0.3");
  oled.setCursor(29, 25);  // position to display
  oled.print("SR6MB v1.38b");
  oled.display();
  delay(2000); // wait two seconds for initializing
  oled.clearDisplay();
}
