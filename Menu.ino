   void Menu() {
 
    drawMenu();

  downButtonState = digitalRead(EXT2);
  selectButtonState = digitalRead(EXT1);
  upButtonState =   digitalRead(EXT3);
 
  checkIfDownButtonIsPressed();
  checkIfUpButtonIsPressed();
  checkIfSelectButtonIsPressed();


// Need to Be As Many As Number of Menu Items
  if (up && page == 1 ) {   
    up = false;
    if(menuitem==2 && frame ==2)
    {
      frame--;
    }
     if(menuitem==4 && frame ==4)
    {
      frame--;
    }
     if(menuitem==5 && frame ==5)
    {
      frame--;
    }
      if(menuitem==3 && frame ==3)
    {
      frame--;
    }
    lastMenuItem = menuitem;
    menuitem--;
    if (menuitem==0)
    {
      menuitem=1;
    } 
  }
  else if (up && page == 2 && menuitem==2 ) {
    up = false;
    SLmaxTemp++;
    preferences.putInt("SLmaxTemp", SLmaxTemp);
    }
    else if (up && page == 2 && menuitem==3 ) {
    }
    else if (up && page == 2 && menuitem==4 ) {
    up = false;
    selectedServodegree--;
    if(selectedServodegree == -1)
    {
      selectedServodegree++;
    }
    if(selectedServodegree == 0)
    {
      preferences.putInt("ServoDEG", 954);
    }    
    if(selectedServodegree == 1)
    {
      preferences.putInt("ServoDEG", 637);
    }
    if(selectedServodegree == 2)
    {
      preferences.putInt("ServoDEG", 425); 
    }
    if(selectedServodegree == 3)
    {
      preferences.putInt("ServoDEG", 318);
    }
  }
  // Need to Be One Less Then The Number of Menu Items
  if (down && page == 1)
  {
    down = false;
    if(menuitem==3 && lastMenuItem == 2)
    {
      frame ++;
    }else  if(menuitem==4 && lastMenuItem == 3)
    {
      frame ++;
    }
     else  if(menuitem==5 && lastMenuItem == 4)
    {
      frame ++;
    }
     else  if(menuitem==6 && lastMenuItem == 5 && frame!=5)
    {
      frame ++;
    }
    lastMenuItem = menuitem;
    menuitem++;  
    if (menuitem==8) // Need to Be One More Then The Number of Menu Items
    {
      menuitem--;
    } 
  }
  else if (down && page == 2 && menuitem==2) {
    down = false;
    SLmaxTemp--;
    preferences.putInt("SLmaxTemp", SLmaxTemp);
  }
   else if (down && page == 2 && menuitem==3 ) {
   }
  else if (down && page == 2 && menuitem==4 ) {
    down = false;
    selectedServodegree++;  
    if(selectedServodegree == 4)
    {
      selectedServodegree--;
    }
    if(selectedServodegree == 0)
    {
      preferences.putInt("ServoDEG", 954);
    }    
    if(selectedServodegree == 1)
    {
      preferences.putInt("ServoDEG", 637);
    }
    if(selectedServodegree == 2)
    {
      preferences.putInt("ServoDEG", 425); 
    }
    if(selectedServodegree == 3)
    {
      preferences.putInt("ServoDEG", 318);
    }
  }

      preferences.getInt("SLheater", SLheater);
      
  if (middle) //Middle Button is Pressed
  {
    middle = false;   
    if (page == 1 && menuitem==5) // SLheater Control 
    {
      if (SLheater == 0)
      {
        SLheater = 1;
    preferences.putInt("SLheater", SLheater);
          menuItem5 = "SL Heater: ON";
        }
      else
      {
        SLheater = 0;
    preferences.putInt("SLheater", SLheater);
          menuItem5 = "SL Heater: OFF";
       }
    }

    if (page == 1 && menuitem==6) // Lube Pump Control 
    {
      if (LubePump == 0)
      {
        LubePump = 1;
    preferences.putInt("LubePump", LubePump);
          menuItem6 = "Lube Pump: ON";
        }
      else
      {
        LubePump = 0;
    preferences.putInt("LubePump", LubePump);
          menuItem6 = "Lube Pump: OFF";
       }
    }

    if(page == 1 && menuitem ==7) // Reset
    {
      resetDefaults();
    }
    else if (page == 1 && menuitem<=4) { // The Number of Menu Items With Their Own Subpage
      page=2;
     }
      else if (page == 2) 
     {
      page=1; 
     }
   }   
  }
  
  void checkIfDownButtonIsPressed()
  {
    if (downButtonState != lastDownButtonState) 
  {
    if (downButtonState == 0) 
    {
      down=true;
    }
    delay(50);
  }
   lastDownButtonState = downButtonState;
  }

void checkIfUpButtonIsPressed()
{
  if (upButtonState != lastUpButtonState) 
  {
    if (upButtonState == 0) {
      up=true;
    }
    delay(50);
  }
   lastUpButtonState = upButtonState;
}

void checkIfSelectButtonIsPressed()
{
   if (selectButtonState != lastSelectButtonState) 
  {
    if (selectButtonState == 0) {
      middle=true;
    }
    delay(50);
  }
   lastSelectButtonState = selectButtonState;
}
  
  void drawMenu()
  {  
  if (page==1) 
  {    
    oled.setTextSize(1);
    oled.clearDisplay();
    oled.setTextColor(WHITE);
    oled.setCursor(38, 0);
    oled.print("MAIN MENU");
    oled.drawFastHLine(0,10,128,WHITE);
    
//------------------FRAME1-----------------
    if     (menuitem == 1 && frame == 1)
    {   
      displayMenuItem(menuItem1, 15,true);
      displayMenuItem(menuItem2, 25,false);
    }
    else if(menuitem == 2 && frame == 1)
    {
      displayMenuItem(menuItem1, 15,false);
      displayMenuItem(menuItem2, 25,true);
    }
    else if(menuitem == 3 && frame == 1)
    {
      displayMenuItem(menuItem2, 15,false);
      displayMenuItem(menuItem3, 25,true);
    }
//------------------FRAME2-----------------

    else if(menuitem == 2 && frame == 2)
    {
      displayMenuItem(menuItem2, 15,true);
      displayMenuItem(menuItem3, 25,false);
    }
    else if(menuitem == 3 && frame == 2)
    {
      displayMenuItem(menuItem3, 15,true);
      displayMenuItem(menuItem4, 25,false);
    }
    else if(menuitem == 4 && frame == 2)
    {
      displayMenuItem(menuItem3, 15,false);
      displayMenuItem(menuItem4, 25,true);
    }
//------------------FRAME3-----------------
   else if(menuitem == 3 && frame == 3)
    {
      displayMenuItem(menuItem3, 15,true);
      displayMenuItem(menuItem4, 25,false);
    }
   else if(menuitem == 4 && frame == 3)
    {
      displayMenuItem(menuItem3, 15,false);
      displayMenuItem(menuItem4, 25,true);
    }
   else if(menuitem == 5 && frame == 3)
    {
      displayMenuItem(menuItem4, 15,false);
      displayMenuItem(menuItem5, 25,true);
    }
//------------------FRAME4-----------------
   else if(menuitem == 4 && frame == 4)
    {
      displayMenuItem(menuItem4, 15,true);
      displayMenuItem(menuItem5, 25,false);
    }
   else if(menuitem == 5 && frame == 4)
    {
      displayMenuItem(menuItem5, 15,true);
      displayMenuItem(menuItem6, 25,false);
    }
   else if(menuitem == 6 && frame == 4)
    {
      displayMenuItem(menuItem5, 15,false);
      displayMenuItem(menuItem6, 25,true);
    }
//------------------FRAME5-----------------
   else if(menuitem == 5 && frame == 5)
    {
      displayMenuItem(menuItem5, 15,true);
      displayMenuItem(menuItem6, 25,false);
    }
   else if(menuitem == 6 && frame == 5)
    {
      displayMenuItem(menuItem6, 15,true);
      displayMenuItem(menuItem7, 25,false);
    }
   else if(menuitem == 7 && frame == 5)
    {
      displayMenuItem(menuItem6, 15,false);
      displayMenuItem(menuItem7, 25,true);
    }

//------------------------------------------
   oled.display();
  }
  else if (page==2 && menuitem == 1) 
  {   
  oled.clearDisplay();   
  Display();
  }
  else if (page==2 && menuitem == 2) 
  {
   displayIntMenuPage(menuItem2, SLmaxTemp);
  }
   else if (page==2 && menuitem == 3) 
  {
  SubMenu();
  }
  else if (page==2 && menuitem == 4) 
  {
   displayStringMenuPage(menuItem4, Servodegree[selectedServodegree]);
  }
}

  void resetDefaults()
  {
    preferences.putInt("PitchFrequens", 330);
    preferences.putInt("MainFrequens", 330);
    preferences.putInt("TwistFrequens", 50);
    preferences.putInt("SqueezeFrequens", 50);
    preferences.putInt("ValvFrequens", 50);
    preferences.putInt("VibeFrequens", 8000);   
    preferences.putInt("LeftPitchServo", 1500);
    preferences.putInt("RightPitchServo", 1500);
    preferences.putInt("LeftUpperServo", 1500);
    preferences.putInt("RightUpperServo", 1500);
    preferences.putInt("LeftLowerServo", 1500);
    preferences.putInt("RightLowerServo", 1500);
    preferences.putInt("TwistServo", 1500);
    preferences.putInt("SqueezeServo", 1500);
    preferences.putInt("ValvServo", 1500);
    preferences.putInt("SLheater", 0);
         menuItem5 = "SL Heater: OFF";
    preferences.putInt("SLmaxTemp", 40);
    preferences.putInt("ServoDEG", 637);
    preferences.putInt("TwistPax", 0);
    ASsubmenuitem8 = "Twist Paralax: OFF"; 
    preferences.putInt("ReverseTwist", 0);
    ASsubmenuitem9 = "Reverse Twist: OFF";
    preferences.putInt("ReverseValv", 0);
    ASsubmenuitem10 = "Reverse Valv: OFF";
    preferences.putInt("ReverseSqueeze", 0);
    ASsubmenuitem11 = "Reverse Squeeze: OFF";
    preferences.putInt("LubePump", 0);
    menuItem6 = "Lube Pump: OFF";      

    ESP.restart();
  }

//-----------------------SLEEVE TEMP-----------------------
void displayIntMenuPage(String menuItem, int value)
{
    oled.setTextSize(1);
    oled.clearDisplay();
    oled.setTextColor(WHITE);
    oled.setCursor(30, 0);
    oled.print("SLEEVE TEMP");
    oled.drawFastHLine(0,10,128,WHITE);
    oled.setCursor(5, 18);
    oled.print("Max Temp:");
    oled.setTextSize(1);
    oled.setCursor(60, 18);
    oled.print(value);
    oled.print("C");
    oled.setTextSize(1);
    oled.display();
}
//---------------------SCREEN SIZE----------------------
void displayStringMenuPage(String menuItem, String value)
{
    oled.setTextSize(1);
    oled.clearDisplay();
    oled.setTextColor(WHITE);
    oled.setCursor(32, 0);
    oled.print("SERVO ANGEL");
    oled.drawFastHLine(0,10,128,WHITE);
    oled.setCursor(5, 18);
    oled.print("Type:");
    oled.setTextSize(1);
    oled.setCursor(35, 18);
    oled.print(value);
    oled.setTextSize(1);
    oled.display();
}

void displayMenuItem(String item, int position, boolean selected)
{
    if(selected)
    {
      oled.setTextColor(BLACK, WHITE);
    }else
    {
      oled.setTextColor(WHITE, BLACK);
    }
    oled.setCursor(0, position);
    oled.print(">"+item);
}
