   void SubMenu() {
    
    drawSubMenu();

  downButtonState = digitalRead(EXT2);
  selectButtonState = digitalRead(EXT1);
  upButtonState =   digitalRead(EXT3);
 
  SubcheckIfDownButtonIsPressed();
  SubcheckIfUpButtonIsPressed();
  SubcheckIfSelectButtonIsPressed();

// Need to Be As Many As Number of Menu Items
  if (up && subpage == 1 ) {
     
    up = false;
      if(submenuitem==2 && subframe ==2)
    {
      subframe--;
    }
      if(submenuitem==3 && subframe ==3)
    {
      subframe--;
    }
      if(submenuitem==4 && subframe ==4)
    {
      subframe--;
    }
      if(submenuitem==5 && subframe ==5)
    {
      subframe--;
    }
      if(submenuitem==6 && subframe ==6)
    {
      subframe--;
    }
      if(submenuitem==7 && subframe ==7)
    {
      subframe--;
    }
      if(submenuitem==8 && subframe ==8)
    {
      subframe--;
    }
      if(submenuitem==9 && subframe ==9)
    {
      subframe--;
    }
    sublastmenuitem = submenuitem;
    submenuitem--;
    if (submenuitem==0)
    {
      submenuitem=1;
    } 
  }
  else if (up && subpage == 2 && submenuitem==2 ) {
    up = false;
    LeftPitchServo = LeftPitchServo+10;
    preferences.putInt("LeftPitchServo", LeftPitchServo);
  }
  else if (up && subpage == 2 && submenuitem==3 ) {
    up = false;
    RightPitchServo = RightPitchServo+10;
    preferences.putInt("RightPitchServo", RightPitchServo);
  }
    else if (up && subpage == 2 && submenuitem==4 ) {
    up = false;
    LeftUpperServo = LeftUpperServo+10;
    preferences.putInt("LeftUpperServo", LeftUpperServo);
  }
    else if (up && subpage == 2 && submenuitem==5 ) {
    up = false;
    RightUpperServo = RightUpperServo+10;
    preferences.putInt("RightUpperServo", RightUpperServo);
  }
    else if (up && subpage == 2 && submenuitem==6 ) {
    up = false;
    LeftLowerServo = LeftLowerServo+10;
    preferences.putInt("LeftLowerServo", LeftLowerServo);
  }
    else if (up && subpage == 2 && submenuitem==7 ) {
    up = false;
    RightLowerServo = RightLowerServo+10;
    preferences.putInt("RightLowerServo", RightLowerServo);
  }
    else if (up && subpage == 2 && submenuitem==8 ) {
    up = false;
    TwistServo = TwistServo+10;
    preferences.putInt("TwistServo", TwistServo);
  }
    else if (up && subpage == 2 && submenuitem==9 ) {
    up = false;
    SqueezeServo = SqueezeServo+10;
    preferences.putInt("SqueezeServo", SqueezeServo);
  }
    else if (up && subpage == 2 && submenuitem==10 ) {
    up = false;
    ValvServo = ValvServo+10;
    preferences.putInt("ValvServo", ValvServo);
  }

// Need to Be One Less Then The Number of Menu Items
  if (down && subpage == 1) 
  {
    down = false;
    if(submenuitem==3 && sublastmenuitem== 2)
    {
      subframe ++;
    }else  if(submenuitem==4 && sublastmenuitem== 3)
    {
      subframe ++;
    }
     else  if(submenuitem==5 && sublastmenuitem== 4)
    {
      subframe ++;
    }
     else  if(submenuitem==6 && sublastmenuitem== 5)
    {
      subframe ++;
    }
     else  if(submenuitem==7 && sublastmenuitem== 6)
    {
      subframe ++;
    }
     else  if(submenuitem==8 && sublastmenuitem== 7)
    {
      subframe ++;
    }
     else  if(submenuitem==9 && sublastmenuitem== 8)
    {
      subframe ++;
    }
     else  if(submenuitem==10 && sublastmenuitem== 9 && subframe!=9 )
    {
      subframe ++;
    }
    sublastmenuitem = submenuitem;
    submenuitem++;  
    if (submenuitem==12) // Need to Be One More Then The Number of Menu Items
    {
      submenuitem--;
    }
  
  }
  else if (down && subpage == 2 && submenuitem==2) {
    down = false;
    LeftPitchServo = LeftPitchServo-10;
    preferences.putInt("LeftPitchServo", LeftPitchServo);
  }
   else if (down && subpage == 2 && submenuitem==3 ) {
    down = false;
    RightPitchServo = RightPitchServo-10;
    preferences.putInt("RightPitchServo", RightPitchServo);
   }   
  else if (down && subpage == 2 && submenuitem==4 ) {
    down = false;
    LeftUpperServo = LeftUpperServo-10;
    preferences.putInt("LeftUpperServo", LeftUpperServo);
  }
    else if (down && subpage == 2 && submenuitem==5 ) {
    down = false;
    RightUpperServo = RightUpperServo-10;
    preferences.putInt("RightUpperServo", RightUpperServo);
  }
    else if (down && subpage == 2 && submenuitem==6 ) {
    down = false;
    LeftLowerServo = LeftLowerServo-10;
    preferences.putInt("LeftLowerServo", LeftLowerServo);
  }
    else if (down && subpage == 2 && submenuitem==7 ) {
    down = false;
    RightLowerServo = RightLowerServo-10;
    preferences.putInt("RightLowerServo", RightLowerServo);
  }
    else if (down && subpage == 2 && submenuitem==8 ) {
    down = false;
    TwistServo = TwistServo-10;
    preferences.putInt("TwistServo", TwistServo);
  }
    else if (down && subpage == 2 && submenuitem==9 ) {
    down = false;
    SqueezeServo = SqueezeServo-10;
    preferences.putInt("SqueezeServo", SqueezeServo);
  }
    else if (down && subpage == 2 && submenuitem==10 ) {
    down = false;
    ValvServo = ValvServo-10;
    preferences.putInt("ValvServo", ValvServo);
  }

  
  if (middle) //If Middle Button is Pressed
  {
    middle = false;

    if(subpage == 1 && submenuitem ==1)
    {
      page=1;
    }

    else if (subpage == 1 && submenuitem<=11) { // The Number of Menu Items With Their Own Subpage
      subpage=2;
     }
      else if (subpage == 2) 
     {
      subpage=1; 
     }
   }   
  }

  void SubcheckIfDownButtonIsPressed()
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

void SubcheckIfUpButtonIsPressed()
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

void SubcheckIfSelectButtonIsPressed()
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
  
  void drawSubMenu()
  {
    
  if (subpage==1) 
  {    
    oled.setTextSize(1);
    oled.clearDisplay();
    oled.setTextColor(WHITE);
    oled.setCursor(30, 0);
    oled.print("SERVO MENU");
    oled.drawFastHLine(0,10,128,WHITE);
    
//------------------FRAME1-----------------
    if     (submenuitem == 1 && subframe == 1)
    {   
      SubdisplayMenuItem(submenuitem1, 15,true);
      SubdisplayMenuItem(submenuitem2, 25,false);
    }
    else if(submenuitem == 2 && subframe == 1)
    {
      SubdisplayMenuItem(submenuitem1, 15,false);
      SubdisplayMenuItem(submenuitem2, 25,true);
    }
    else if(submenuitem == 3 && subframe == 1)
    {
      SubdisplayMenuItem(submenuitem2, 15,false);
      SubdisplayMenuItem(submenuitem3, 25,true);
    }
//------------------FRAME2------------------

    else if(submenuitem == 2 && subframe == 2)
    {
      SubdisplayMenuItem(submenuitem2, 15,true);
      SubdisplayMenuItem(submenuitem3, 25,false);
    }
    else if(submenuitem == 3 && subframe == 2)
    {
      SubdisplayMenuItem(submenuitem3, 15,true);
      SubdisplayMenuItem(submenuitem4, 25,false);
    }
    else if(submenuitem == 4 && subframe == 2)
    {
      SubdisplayMenuItem(submenuitem3, 15,false);
      SubdisplayMenuItem(submenuitem4, 25,true);
    }
//------------------FRAME3--------------------

   else if(submenuitem == 3 && subframe == 3)
    {
      SubdisplayMenuItem(submenuitem3, 15,true);
      SubdisplayMenuItem(submenuitem4, 25,false);
    }
   else if(submenuitem == 4 && subframe == 3)
    {
      SubdisplayMenuItem(submenuitem3, 15,false);
      SubdisplayMenuItem(submenuitem4, 25,true);
    }
   else if(submenuitem == 5 && subframe == 3)
    {
      SubdisplayMenuItem(submenuitem4, 15,false);
      SubdisplayMenuItem(submenuitem5, 25,true);
    }
//------------------FRAME4--------------------

   else if(submenuitem == 4 && subframe == 4)
    {
      SubdisplayMenuItem(submenuitem4, 15,true);
      SubdisplayMenuItem(submenuitem5, 25,false);
    }   
   else if(submenuitem == 5 && subframe == 4)
    {
      SubdisplayMenuItem(submenuitem5, 15,true);
      SubdisplayMenuItem(submenuitem6, 25,false);
    }
   else if(submenuitem == 6 && subframe == 4)
    {
      SubdisplayMenuItem(submenuitem5, 15,false);
      SubdisplayMenuItem(submenuitem6, 25,true);
    }
//------------------FRAME5--------------------

   else if(submenuitem == 5 && subframe == 5)
    {
      SubdisplayMenuItem(submenuitem5, 15,true);
      SubdisplayMenuItem(submenuitem6, 25,false);
    }
   else if(submenuitem == 6 && subframe == 5)
    {
      SubdisplayMenuItem(submenuitem5, 15,false);
      SubdisplayMenuItem(submenuitem6, 25,true);
    }
   else if(submenuitem == 7 && subframe == 5)
    {
      SubdisplayMenuItem(submenuitem6, 15,false);
      SubdisplayMenuItem(submenuitem7, 25,true);
    }
//------------------FRAME6--------------------

   else if(submenuitem == 6 && subframe == 6)
    {
      SubdisplayMenuItem(submenuitem6, 15,true);
      SubdisplayMenuItem(submenuitem7, 25,false);
    } 
   else if(submenuitem == 7 && subframe == 6)
    {
      SubdisplayMenuItem(submenuitem7, 15,true);
      SubdisplayMenuItem(submenuitem8, 25,false);
    }
   else if(submenuitem == 8 && subframe == 6)
    {
      SubdisplayMenuItem(submenuitem7, 15,false);
      SubdisplayMenuItem(submenuitem8, 25,true);
    }   
//------------------FRAME7--------------------

   else if(submenuitem == 7 && subframe == 7)
    {
      SubdisplayMenuItem(submenuitem7, 15,true);
      SubdisplayMenuItem(submenuitem8, 25,false);
    }
   else if(submenuitem == 8 && subframe == 7)
    {
      SubdisplayMenuItem(submenuitem7, 15,false);
      SubdisplayMenuItem(submenuitem8, 25,true);
    }
   else if(submenuitem == 9 && subframe == 7)
    {
      SubdisplayMenuItem(submenuitem8, 15,false);
      SubdisplayMenuItem(submenuitem9, 25,true);
    }
//------------------FRAME8--------------------

   else if(submenuitem == 8 && subframe == 8)
    {
      SubdisplayMenuItem(submenuitem8, 15,true);
      SubdisplayMenuItem(submenuitem9, 25,false);
    }
   else if(submenuitem == 9 && subframe == 8)
    {
      SubdisplayMenuItem(submenuitem9, 15,true);
      SubdisplayMenuItem(submenuitem10, 25,false);
    }
   else if(submenuitem == 10 && subframe == 8)
    {
      SubdisplayMenuItem(submenuitem9, 15,false);
      SubdisplayMenuItem(submenuitem10, 25,true);
    }
//------------------FRAME9--------------------

   else if(submenuitem == 9 && subframe == 9)
    {
      SubdisplayMenuItem(submenuitem9, 15,true);
      SubdisplayMenuItem(submenuitem10, 25,false);
    }
   else if(submenuitem == 10 && subframe == 9)
    {
      SubdisplayMenuItem(submenuitem9, 15,false);
      SubdisplayMenuItem(submenuitem10, 25,true);
    }
   else if(submenuitem == 11 && subframe == 9)
    {
      SubdisplayMenuItem(submenuitem10, 15,false);
      SubdisplayMenuItem(submenuitem11, 25,true);
    }
//--------------------------------------------

   oled.display();
  }
  else if (subpage==2 && submenuitem == 2)
  {
   SubdisplayIntMenuPageLeftPitchServo(submenuitem2, LeftPitchServo);
  }
   else if (subpage==2 && submenuitem == 3) 
  {
   SubdisplayIntMenuPageRightPitchServo(submenuitem3, RightPitchServo);
  }
  else if (subpage==2 && submenuitem == 4) 
  {
   SubdisplayIntMenuPageLeftUpperServo(submenuitem4, LeftUpperServo);
  }
  else if (subpage==2 && submenuitem == 5) 
  {
   SubdisplayIntMenuPageRightUpperServo(submenuitem5, RightUpperServo);
  }
  else if (subpage==2 && submenuitem == 6) 
  {
   SubdisplayIntMenuPageLeftLowerServo(submenuitem6, LeftLowerServo);
  }
  else if (subpage==2 && submenuitem == 7) 
  {
   SubdisplayIntMenuPageRightLowerServo(submenuitem7, RightLowerServo);
  }
  else if (subpage==2 && submenuitem == 8) 
  {
   SubdisplayIntMenuPageTwistServo(submenuitem8, TwistServo);
  }
  else if (subpage==2 && submenuitem == 9) 
  {
   SubdisplayIntMenuPageSqueezeServo(submenuitem9, SqueezeServo);
  }
  else if (subpage==2 && submenuitem == 10) 
  {
   SubdisplayIntMenuPageValvServo(submenuitem10, ValvServo);
  }
  else if (subpage==2 && submenuitem == 11) 
  {
   ASSubMenu();
  }
    }

  //-----------------------RIGHT PITCH SERVO-----------------------
void SubdisplayIntMenuPageRightPitchServo(String submenuitem, int value)
{
    oled.setTextSize(1);
    oled.clearDisplay();
    oled.setTextColor(WHITE);
    oled.setCursor(15, 0);
    oled.print("RIGHT PITCH CENTER");
    oled.drawFastHLine(0,10,128,WHITE);
    oled.setCursor(5, 18);
    oled.print("POSITION:");
    oled.setTextSize(1);
    oled.setCursor(60, 18);
    oled.print(value);
    oled.setTextSize(1);
    oled.display();
}

//-----------------------LEFT PITCH SERVO-----------------------
void SubdisplayIntMenuPageLeftPitchServo(String submenuitem, int value)
{
    oled.setTextSize(1);
    oled.clearDisplay();
    oled.setTextColor(WHITE);
    oled.setCursor(17, 0);
    oled.print("LEFT PITCH CENTER");
    oled.drawFastHLine(0,10,128,WHITE);
    oled.setCursor(5, 18);
    oled.print("POSITION:");
    oled.setTextSize(1);
    oled.setCursor(60, 18);
    oled.print(value);
    oled.setTextSize(1);
    oled.display();
}
//-----------------------LEFT UPPER SERVO-----------------------
void SubdisplayIntMenuPageLeftUpperServo(String submenuitem, int value)
{
    oled.setTextSize(1);
    oled.clearDisplay();
    oled.setTextColor(WHITE);
    oled.setCursor(16, 0);
    oled.print("LEFT UPPER CENTER");
    oled.drawFastHLine(0,10,128,WHITE);
    oled.setCursor(5, 18);
    oled.print("POSITION:");
    oled.setTextSize(1);
    oled.setCursor(60, 18);
    oled.print(value);
    oled.setTextSize(1);
    oled.display();
}

//-----------------------RIGHT UPPER SERVO-----------------------
void SubdisplayIntMenuPageRightUpperServo(String submenuitem, int value)
{
    oled.setTextSize(1);
    oled.clearDisplay();
    oled.setTextColor(WHITE);
    oled.setCursor(14, 0);
    oled.print("RIGHT UPPER CENTER");
    oled.drawFastHLine(0,10,128,WHITE);
    oled.setCursor(5, 18);
    oled.print("POSITION:");
    oled.setTextSize(1);
    oled.setCursor(60, 18);
    oled.print(value);
    oled.setTextSize(1);
    oled.display();
}
//-----------------------LOWER LEFT SERVO-----------------------
void SubdisplayIntMenuPageLeftLowerServo(String submenuitem, int value)
{
    oled.setTextSize(1);
    oled.clearDisplay();
    oled.setTextColor(WHITE);
    oled.setCursor(14, 0);
    oled.print("LEFT LOWER CENTER");
    oled.drawFastHLine(0,10,128,WHITE);
    oled.setCursor(5, 18);
    oled.print("POSITION:");
    oled.setTextSize(1);
    oled.setCursor(60, 18);
    oled.print(value);
    oled.setTextSize(1);
    oled.display();
}
//-----------------------LOWER RIGHT SERVO-----------------------
void SubdisplayIntMenuPageRightLowerServo(String submenuitem, int value)
{
    oled.setTextSize(1);
    oled.clearDisplay();
    oled.setTextColor(WHITE);
    oled.setCursor(14, 0);
    oled.print("RIGHT LOWER CENTER");
    oled.drawFastHLine(0,10,128,WHITE);
    oled.setCursor(5, 18);
    oled.print("POSITION:");
    oled.setTextSize(1);
    oled.setCursor(60, 18);
    oled.print(value);
    oled.setTextSize(1);
    oled.display();
}
//-----------------------TWIST SERVO-----------------------
void SubdisplayIntMenuPageTwistServo(String submenuitem, int value)
{
    oled.setTextSize(1);
    oled.clearDisplay();
    oled.setTextColor(WHITE);
    oled.setCursor(28, 0);
    oled.print("TWIST CENTER");
    oled.drawFastHLine(0,10,128,WHITE);
    oled.setCursor(5, 18);
    oled.print("POSITION:");
    oled.setTextSize(1);
    oled.setCursor(60, 18);
    oled.print(value);
    oled.setTextSize(1);
    oled.display();
}

//-----------------------SQUEESE SERVO-----------------------
void SubdisplayIntMenuPageSqueezeServo(String submenuitem, int value)
{
    oled.setTextSize(1);
    oled.clearDisplay();
    oled.setTextColor(WHITE);
    oled.setCursor(25, 0);
    oled.print("SQUEESE CENTER");
    oled.drawFastHLine(0,10,128,WHITE);
    oled.setCursor(5, 18);
    oled.print("POSITION:");
    oled.setTextSize(1);
    oled.setCursor(60, 18);
    oled.print(value);
    oled.setTextSize(1);
    oled.display();
}

//-----------------------VALV SERVO-----------------------
void SubdisplayIntMenuPageValvServo(String submenuitem, int value)
{
    oled.setTextSize(1);
    oled.clearDisplay();
    oled.setTextColor(WHITE);
    oled.setCursor(30, 0);
    oled.print("VALV CENTER");
    oled.drawFastHLine(0,10,128,WHITE);
    oled.setCursor(5, 18);
    oled.print("POSITION:");
    oled.setTextSize(1);
    oled.setCursor(60, 18);
    oled.print(value);
    oled.setTextSize(1);
    oled.display();
}

void SubdisplayMenuItem(String item, int position, boolean selected)
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
