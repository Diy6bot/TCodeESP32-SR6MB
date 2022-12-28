   void ASSubMenu() {
    
    drawASSubMenu();

  downButtonState = digitalRead(EXT2);
  selectButtonState = digitalRead(EXT1);
  upButtonState =   digitalRead(EXT3);
 
  ASSubcheckIfDownButtonIsPressed();
  ASSubcheckIfUpButtonIsPressed();
  ASSubcheckIfSelectButtonIsPressed();

// Need to Be As Many As Number of Menu Items
  if (up && ASsubpage == 1 ) {
     
    up = false;
      if(ASsubmenuitem==2 && ASsubframe ==2)
    {
      ASsubframe--;
    }
      if(ASsubmenuitem==3 && ASsubframe ==3)
    {
      ASsubframe--;
    }
      if(ASsubmenuitem==4 && ASsubframe ==4)
    {
      ASsubframe--;
    }
      if(ASsubmenuitem==5 && ASsubframe ==5)
    {
      ASsubframe--;
    }
      if(ASsubmenuitem==6 && ASsubframe ==6)
    {
      ASsubframe--;
    }
      if(ASsubmenuitem==7 && ASsubframe ==7)
    {
      ASsubframe--;
    }
      if(ASsubmenuitem==8 && ASsubframe ==8)
    {
      ASsubframe--;
    }
      if(ASsubmenuitem==9 && ASsubframe ==9)
    {
      ASsubframe--;
    }
    ASsublastmenuitem = ASsubmenuitem;
    ASsubmenuitem--;
    if (ASsubmenuitem==0)
    {
      ASsubmenuitem=1;
    } 
  }
  else if (up && ASsubpage == 2 && ASsubmenuitem==2) {
    up = false;
    PitchFrequens = PitchFrequens+10;
    preferences.putInt("PitchFrequens", PitchFrequens);
  }
   else if (up && ASsubpage == 2 && ASsubmenuitem==3 ) {
    up = false;
    MainFrequens = MainFrequens+10;
    preferences.putInt("MainFrequens", MainFrequens);
   }   
  else if (up && ASsubpage == 2 && ASsubmenuitem==4 ) {
    up = false;
    TwistFrequens = TwistFrequens+10;
    preferences.putInt("TwistFrequens", TwistFrequens);    
  }
    else if (up && ASsubpage == 2 && ASsubmenuitem==5 ) {
    up = false;
    SqueezeFrequens = SqueezeFrequens+10;
    preferences.putInt("SqueezeFrequens", SqueezeFrequens);
  }
    else if (up && ASsubpage == 2 && ASsubmenuitem==6 ) {
    up = false;
    ValvFrequens = ValvFrequens+10;
    preferences.putInt("ValvFrequens", ValvFrequens);    
  }
    else if (up && ASsubpage == 2 && ASsubmenuitem==7 ) {
    up = false;
    VibeFrequens = VibeFrequens+10;
    preferences.putInt("VibeFrequens", VibeFrequens);
  }

// Need to Be One Less Then The Number of Menu Items
  if (down && ASsubpage == 1) 
  {
    down = false;
    if(ASsubmenuitem==3 && ASsublastmenuitem== 2)
    {
      ASsubframe ++;
    }else  if(ASsubmenuitem==4 && ASsublastmenuitem== 3)
    {
      ASsubframe ++;
    }
     else  if(ASsubmenuitem==5 && ASsublastmenuitem== 4)
    {
      ASsubframe ++;
    }
     else  if(ASsubmenuitem==6 && ASsublastmenuitem== 5)
    {
      ASsubframe ++;
    }
     else  if(ASsubmenuitem==7 && ASsublastmenuitem== 6)
    {
      ASsubframe ++;
    }
     else  if(ASsubmenuitem==8 && ASsublastmenuitem== 7)
    {
      ASsubframe ++;
    }
     else  if(ASsubmenuitem==9 && ASsublastmenuitem== 8)
    {
      ASsubframe ++;
    }
     else  if(ASsubmenuitem==10 && ASsublastmenuitem== 9 && ASsubframe!=9 )
    {
      ASsubframe ++;
    }
    ASsublastmenuitem = ASsubmenuitem;
    ASsubmenuitem++;  
    if (ASsubmenuitem==12) // Need to Be One More Then The Number of Menu Items
    {
      ASsubmenuitem--;
    }
  
  }
    else if (down && ASsubpage == 2 && ASsubmenuitem==2) {
    down = false;
    PitchFrequens = PitchFrequens-10;
    preferences.putInt("PitchFrequens", PitchFrequens);
  }
    else if (down && ASsubpage == 2 && ASsubmenuitem==3 ) {
    down = false;
    MainFrequens = MainFrequens-10;
    preferences.putInt("MainFrequens", MainFrequens);
  }   
    else if (down && ASsubpage == 2 && ASsubmenuitem==4 ) {
    down = false;
    TwistFrequens = TwistFrequens-10;
    preferences.putInt("TwistFrequens", TwistFrequens);    
  }
    else if (down && ASsubpage == 2 && ASsubmenuitem==5 ) {
    down = false;
    SqueezeFrequens = SqueezeFrequens-10;
    preferences.putInt("SqueezeFrequens", SqueezeFrequens);
  }
    else if (down && ASsubpage == 2 && ASsubmenuitem==6 ) {
    down = false;
    ValvFrequens = ValvFrequens-10;
    preferences.putInt("ValvFrequens", ValvFrequens);    
  }
    else if (down && ASsubpage == 2 && ASsubmenuitem==7 ) {
    down = false;
    VibeFrequens = VibeFrequens-10;
    preferences.putInt("VibeFrequens", VibeFrequens);
  }
  
  if (middle) //If Middle Button is Pressed
  {
    middle = false;

    if(ASsubpage == 1 && ASsubmenuitem ==1)
    {
      subpage=1;
    }
    
//----------------------------------------------------------

    if (ASsubpage == 1 && ASsubmenuitem==8) // TwistParalax Control
    {
      if (TwistPax == 0)
      {
        TwistPax = 1;
    preferences.putInt("TwistPax", TwistPax);
          ASsubmenuitem8 = "Twist Paralax: ON";
        }
      else
      {
        TwistPax = 0;
    preferences.putInt("TwistPax", TwistPax);
          ASsubmenuitem8 = "Twist Paralax: OFF";
       }
    }
//----------------------------------------------------------

    if (ASsubpage == 1 && ASsubmenuitem==9) // ReverseTwist Control
    {
      if (ReverseTwist == 0)
      {
        ReverseTwist = 1;
    preferences.putInt("ReverseTwist", ReverseTwist);
          ASsubmenuitem9 = "Reverse Twist: ON";
        }
      else
      {
        ReverseTwist = 0;
    preferences.putInt("ReverseTwist", ReverseTwist);
          ASsubmenuitem9 = "Reverse Twist: OFF";
       }
    }
//----------------------------------------------------------

    if (ASsubpage == 1 && ASsubmenuitem==10) // ReverseTwist Control
    {
      if (ReverseValv == 0)
      {
        ReverseValv = 1;
    preferences.putInt("ReverseValv", ReverseValv);
          ASsubmenuitem10 = "Reverse Valv: ON";
        }
      else
      {
        ReverseValv = 0;
    preferences.putInt("ReverseValv", ReverseValv);
          ASsubmenuitem10 = "Reverse Valv: OFF";
       }
    }
//----------------------------------------------------------

    if (ASsubpage == 1 && ASsubmenuitem==11) // ReverseTwist Control
    {
      if (ReverseSqueeze == 0)
      {
        ReverseSqueeze = 1;
    preferences.putInt("ReverseSqueeze", ReverseSqueeze);
          ASsubmenuitem11 = "Reverse Squeeze: ON";
        }
      else
      {
        ReverseSqueeze = 0;
    preferences.putInt("ReverseSqueeze", ReverseSqueeze);
          ASsubmenuitem11 = "Reverse Squeeze: OFF";
       }
    }
//----------------------------------------------------------

    else if (ASsubpage == 1 && ASsubmenuitem<=11) { // The Number of Menu Items With Their Own Subpage
      ASsubpage=2;
     }
      else if (ASsubpage == 2) 
     {
      ASsubpage=1; 
     }
   }   
  }

  void ASSubcheckIfDownButtonIsPressed()
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

void ASSubcheckIfUpButtonIsPressed()
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

void ASSubcheckIfSelectButtonIsPressed()
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
  
  void drawASSubMenu()
  {
    
  if (ASsubpage==1) 
  {    
    oled.setTextSize(1);
    oled.clearDisplay();
    oled.setTextColor(WHITE);
    oled.setCursor(13, 0);
    oled.print("ADVANCED SETTINGS");
    oled.drawFastHLine(0,10,128,WHITE);
    
//------------------FRAME1-----------------
    if     (ASsubmenuitem == 1 && ASsubframe == 1)
    {   
      ASSubdisplayMenuItem(ASsubmenuitem1, 15,true);
      ASSubdisplayMenuItem(ASsubmenuitem2, 25,false);
    }
    else if(ASsubmenuitem == 2 && ASsubframe == 1)
    {
      ASSubdisplayMenuItem(ASsubmenuitem1, 15,false);
      ASSubdisplayMenuItem(ASsubmenuitem2, 25,true);
    }
    else if(ASsubmenuitem == 3 && ASsubframe == 1)
    {
      ASSubdisplayMenuItem(ASsubmenuitem2, 15,false);
      ASSubdisplayMenuItem(ASsubmenuitem3, 25,true);
    }
//------------------FRAME2------------------

    else if(ASsubmenuitem == 2 && ASsubframe == 2)
    {
      ASSubdisplayMenuItem(ASsubmenuitem2, 15,true);
      ASSubdisplayMenuItem(ASsubmenuitem3, 25,false);
    }
    else if(ASsubmenuitem == 3 && ASsubframe == 2)
    {
      ASSubdisplayMenuItem(ASsubmenuitem3, 15,true);
      ASSubdisplayMenuItem(ASsubmenuitem4, 25,false);
    }
    else if(ASsubmenuitem == 4 && ASsubframe == 2)
    {
      ASSubdisplayMenuItem(ASsubmenuitem3, 15,false);
      ASSubdisplayMenuItem(ASsubmenuitem4, 25,true);
    }
//------------------FRAME3--------------------

   else if(ASsubmenuitem == 3 && ASsubframe == 3)
    {
      ASSubdisplayMenuItem(ASsubmenuitem3, 15,true);
      ASSubdisplayMenuItem(ASsubmenuitem4, 25,false);
    }
   else if(ASsubmenuitem == 4 && ASsubframe == 3)
    {
      ASSubdisplayMenuItem(ASsubmenuitem3, 15,false);
      ASSubdisplayMenuItem(ASsubmenuitem4, 25,true);
    }
   else if(ASsubmenuitem == 5 && ASsubframe == 3)
    {
      ASSubdisplayMenuItem(ASsubmenuitem4, 15,false);
      ASSubdisplayMenuItem(ASsubmenuitem5, 25,true);
    }
//------------------FRAME4--------------------

   else if(ASsubmenuitem == 4 && ASsubframe == 4)
    {
      ASSubdisplayMenuItem(ASsubmenuitem4, 15,true);
      ASSubdisplayMenuItem(ASsubmenuitem5, 25,false);
    }   
   else if(ASsubmenuitem == 5 && ASsubframe == 4)
    {
      ASSubdisplayMenuItem(ASsubmenuitem5, 15,true);
      ASSubdisplayMenuItem(ASsubmenuitem6, 25,false);
    }
   else if(ASsubmenuitem == 6 && ASsubframe == 4)
    {
      ASSubdisplayMenuItem(ASsubmenuitem5, 15,false);
      ASSubdisplayMenuItem(ASsubmenuitem6, 25,true);
    }
//------------------FRAME5--------------------

   else if(ASsubmenuitem == 5 && ASsubframe == 5)
    {
      ASSubdisplayMenuItem(ASsubmenuitem5, 15,true);
      ASSubdisplayMenuItem(ASsubmenuitem6, 25,false);
    }
   else if(ASsubmenuitem == 6 && ASsubframe == 5)
    {
      ASSubdisplayMenuItem(ASsubmenuitem5, 15,false);
      ASSubdisplayMenuItem(ASsubmenuitem6, 25,true);
    }
   else if(ASsubmenuitem == 7 && ASsubframe == 5)
    {
      ASSubdisplayMenuItem(ASsubmenuitem6, 15,false);
      ASSubdisplayMenuItem(ASsubmenuitem7, 25,true);
    }
//------------------FRAME6--------------------

   else if(ASsubmenuitem == 6 && ASsubframe == 6)
    {
      ASSubdisplayMenuItem(ASsubmenuitem6, 15,true);
      ASSubdisplayMenuItem(ASsubmenuitem7, 25,false);
    } 
   else if(ASsubmenuitem == 7 && ASsubframe == 6)
    {
      ASSubdisplayMenuItem(ASsubmenuitem7, 15,true);
      ASSubdisplayMenuItem(ASsubmenuitem8, 25,false);
    }
   else if(ASsubmenuitem == 8 && ASsubframe == 6)
    {
      ASSubdisplayMenuItem(ASsubmenuitem7, 15,false);
      ASSubdisplayMenuItem(ASsubmenuitem8, 25,true);
    }   
//------------------FRAME7--------------------

   else if(ASsubmenuitem == 7 && ASsubframe == 7)
    {
      ASSubdisplayMenuItem(ASsubmenuitem7, 15,true);
      ASSubdisplayMenuItem(ASsubmenuitem8, 25,false);
    }
   else if(ASsubmenuitem == 8 && ASsubframe == 7)
    {
      ASSubdisplayMenuItem(ASsubmenuitem7, 15,false);
      ASSubdisplayMenuItem(ASsubmenuitem8, 25,true);
    }
   else if(ASsubmenuitem == 9 && ASsubframe == 7)
    {
      ASSubdisplayMenuItem(ASsubmenuitem8, 15,false);
      ASSubdisplayMenuItem(ASsubmenuitem9, 25,true);
    }
//------------------FRAME8--------------------

   else if(ASsubmenuitem == 8 && ASsubframe == 8)
    {
      ASSubdisplayMenuItem(ASsubmenuitem8, 15,true);
      ASSubdisplayMenuItem(ASsubmenuitem9, 25,false);
    }
   else if(ASsubmenuitem == 9 && ASsubframe == 8)
    {
      ASSubdisplayMenuItem(ASsubmenuitem9, 15,true);
      ASSubdisplayMenuItem(ASsubmenuitem10, 25,false);
    }
   else if(ASsubmenuitem == 10 && ASsubframe == 8)
    {
      ASSubdisplayMenuItem(ASsubmenuitem9, 15,false);
      ASSubdisplayMenuItem(ASsubmenuitem10, 25,true);
    }
//------------------FRAME9--------------------

   else if(ASsubmenuitem == 9 && ASsubframe == 9)
    {
      ASSubdisplayMenuItem(ASsubmenuitem9, 15,true);
      ASSubdisplayMenuItem(ASsubmenuitem10, 25,false);
    }
   else if(ASsubmenuitem == 10 && ASsubframe == 9)
    {
      ASSubdisplayMenuItem(ASsubmenuitem9, 15,false);
      ASSubdisplayMenuItem(ASsubmenuitem10, 25,true);
    }
   else if(ASsubmenuitem == 11 && ASsubframe == 9)
    {
      ASSubdisplayMenuItem(ASsubmenuitem10, 15,false);
      ASSubdisplayMenuItem(ASsubmenuitem11, 25,true);
    }
//--------------------------------------------
   oled.display();
  }
  else if (ASsubpage==2 && ASsubmenuitem == 2)
  {
   ASSubdisplayIntMenuPagePitchFrequens(ASsubmenuitem2, PitchFrequens);
  }
   else if (ASsubpage==2 && ASsubmenuitem == 3) 
  {
   ASSubdisplayIntMenuPageMainFrequens(ASsubmenuitem3, MainFrequens);
  }
  else if (ASsubpage==2 && ASsubmenuitem == 4) 
  {
   ASSubdisplayIntMenuPageTwistFrequens(ASsubmenuitem4, TwistFrequens);
  }
  else if (ASsubpage==2 && ASsubmenuitem == 5) 
  {
   ASSubdisplayIntMenuPageSqueezeFrequens(ASsubmenuitem5, SqueezeFrequens);
  }
  else if (ASsubpage==2 && ASsubmenuitem == 6) 
  {
   ASSubdisplayIntMenuPageValvFrequens(ASsubmenuitem6, ValvFrequens);
  }
  else if (ASsubpage==2 && ASsubmenuitem == 7) 
  {
   ASSubdisplayIntMenuPageVibeFrequens(ASsubmenuitem7, VibeFrequens);
  }
    }

  //-----------------------PITCH SERVO FREQUENS-----------------------
void ASSubdisplayIntMenuPagePitchFrequens(String ASsubmenuitem, int value)
{
    oled.setTextSize(1);
    oled.clearDisplay();
    oled.setTextColor(WHITE);
    oled.setCursor(5, 0);
    oled.print("PITCH SERVO FREQUENS");
    oled.drawFastHLine(0,10,128,WHITE);
    oled.setCursor(5, 18);
    oled.print("FREQUENS:");
    oled.setTextSize(1);
    oled.setCursor(60, 18);
    oled.print(value);
    oled.print(" HZ");
    oled.setTextSize(1);
    oled.display();
}

//-----------------------MAIN SERVO FREQUENS-----------------------
void ASSubdisplayIntMenuPageMainFrequens(String ASsubmenuitem, int value)
{
    oled.setTextSize(1);
    oled.clearDisplay();
    oled.setTextColor(WHITE);
    oled.setCursor(8, 0);
    oled.print("MAIN SERVO FREQUENS");
    oled.drawFastHLine(0,10,128,WHITE);
    oled.setCursor(5, 18);
    oled.print("FREQUENS:");
    oled.setTextSize(1);
    oled.setCursor(60, 18);
    oled.print(value);
    oled.print(" HZ");
    oled.setTextSize(1);
    oled.display();
}
//-----------------------TWIST SERVO FREQUENS-----------------------
void ASSubdisplayIntMenuPageTwistFrequens(String ASsubmenuitem, int value)
{
    oled.setTextSize(1);
    oled.clearDisplay();
    oled.setTextColor(WHITE);
    oled.setCursor(5, 0);
    oled.print("TWIST SERVO FREQUENS");
    oled.drawFastHLine(0,10,128,WHITE);
    oled.setCursor(5, 18);
    oled.print("FREQUENS:");
    oled.setTextSize(1);
    oled.setCursor(60, 18);
    oled.print(value);
    oled.print(" HZ");
    oled.setTextSize(1);
    oled.display();
}

//-----------------------SQUEEZE SERVO FREQUENS-----------------------
void ASSubdisplayIntMenuPageSqueezeFrequens(String ASsubmenuitem, int value)
{
    oled.setTextSize(1);
    oled.clearDisplay();
    oled.setTextColor(WHITE);
    oled.setCursor(5, 0);
    oled.print("SQUEEZE SERVO FREQ..");
    oled.drawFastHLine(0,10,128,WHITE);
    oled.setCursor(5, 18);
    oled.print("FREQUENS:");
    oled.setTextSize(1);
    oled.setCursor(60, 18);
    oled.print(value);
    oled.print(" HZ");
    oled.setTextSize(1);
    oled.display();
}
//-----------------------VALV SERVO FREQUENS-----------------------
void ASSubdisplayIntMenuPageValvFrequens(String ASsubmenuitem, int value)
{
    oled.setTextSize(1);
    oled.clearDisplay();
    oled.setTextColor(WHITE);
    oled.setCursor(7, 0);
    oled.print("VALV SERVO FREQUENS");
    oled.drawFastHLine(0,10,128,WHITE);
    oled.setCursor(5, 18);
    oled.print("FREQUENS:");
    oled.setTextSize(1);
    oled.setCursor(60, 18);
    oled.print(value);
    oled.print(" HZ");
    oled.setTextSize(1);
    oled.display();
}
//-----------------------VIBE FREQUENS-----------------------
void ASSubdisplayIntMenuPageVibeFrequens(String ASsubmenuitem, int value)
{
    oled.setTextSize(1);
    oled.clearDisplay();
    oled.setTextColor(WHITE);
    oled.setCursor(25, 0);
    oled.print("VIBE FREQUENS");
    oled.drawFastHLine(0,10,128,WHITE);
    oled.setCursor(5, 18);
    oled.print("FREQUENS:");
    oled.setTextSize(1);
    oled.setCursor(60, 18);
    oled.print(value);
    oled.print(" HZ");
    oled.setTextSize(1);
    oled.display();
}

void ASSubdisplayMenuItem(String item, int position, boolean selected)
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
