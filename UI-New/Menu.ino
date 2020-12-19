void performanceMenu()
{
  byte i=0;
  lcd.clear();
  lcd.print(p_menu[i][0]);
  lcd.setCursor(0,1);
  lcd.print(p_menu[i][1]);
  while(SELECT);
  menu_display_timer = millis();
  do{
    if(NEXT)
    {
      button_pressed_timer = millis();
      menu_display_timer = millis();
      i++;
      if(i == TOTAL_ITEMS_IN_PERFORMANCE_MENU)
      i=0;
        lcd.clear();
        lcd.print(p_menu[i][0]);
        lcd.setCursor(0,1);
        lcd.print(p_menu[i][1]);
      while(NEXT && millis() - button_pressed_timer < 1200);
    }
    if(millis() - menu_display_timer > MENU_TIMEOUT)
    {
      CLR
      lcd.setCursor(2,1);
      lcd.print(F("!!TIMEOUT!!"));
      delay(1000);
      return;
    }
  }while(!SELECT);
  button_pressed_timer = millis();
  while(SELECT || millis() - button_pressed_timer < BUTTON_PRESS_TIME);
    
    CLR
    lcd.print(F("PI = "));
    switch(i)
    {
      case 0:
        lcd.print(F("HIGH POWER"));
        break;
      case 1:
        lcd.print(F("MEDIUM"));
        break;
      case 2:
        lcd.print(F("LOW POWER"));
      case 3:
        return;
    }
    lcd.setCursor(0,1);
    lcd.print(F("SEND? YES or NO"));
    lcd.setCursor(0,1);
    menu_display_timer = millis();
    while(millis() - menu_display_timer < MENU_TIMEOUT)
    {
      if(SELECT)
      {
        lcd.print(F("   SENDING.."));
        performance_index = i;
        delay(1000);
        sendDataToMaster('i',0);
        return;
      }
      if(NEXT)
      {
        lcd.print(F("   CANCELLED"));
        delay(1000);
        return;
      }
    }
}


void setPersonCount()
{
    byte person_count_send=0;
    lcd.clear();
    lcd.print(F("SET NO OF PEOPLE"));
    lcd.setCursor(8,1);
    lcd.print("00");
    menu_display_timer = millis();
    while(SELECT);
    do{
        if(NEXT)
        {
          person_count_send++;
          button_pressed_timer = millis();
          if(person_count_send == 20)
          person_count_send = 0;
          lcd.setCursor(8,1);
          lcd.print(person_count_send/10);
          lcd.print(person_count_send%10);
          while(NEXT && millis() - button_pressed_timer < BUTTON_PRESS_TIME);
          menu_display_timer = millis();
        }
        if(millis() - menu_display_timer > MENU_TIMEOUT)
        {
          CLR
          lcd.setCursor(2,1);
          lcd.print(F("!!TIMEOUT!!"));
          delay(1500);
          return;
        }
    }while(!SELECT);
    button_pressed_timer = millis();
    while(SELECT || millis() - button_pressed_timer < BUTTON_PRESS_TIME);
      CLR
      lcd.print(F("NO OF PEOPLE= "));
      lcd.print(person_count_send/10);
      lcd.print(person_count_send%10);
      lcd.setCursor(0,1);
      lcd.print(F("SEND? YES/NO"));
      lcd.setCursor(0,1);
      menu_display_timer = millis();
      while(millis() - menu_display_timer < MENU_TIMEOUT)
      {
        if(SELECT)
        {
          lcd.print(F("   SENDING.."));
          person_count = person_count_send;
          delay(1000);
          sendDataToMaster('p',0);
          return;
        }
        if(NEXT)
        {
          lcd.print(F("   CANCELLED"));
          delay(1500);
          return;
        }
      }
}

byte mainMenu()
{
  byte i=1;
  while(SELECT || millis() - button_pressed_timer < BUTTON_PRESS_TIME);
    lcd.clear();
    lcd.print(m_menu[i][0]);
    lcd.setCursor(0,1);
    lcd.print(m_menu[i][1]);
    menu_display_timer = millis();
  
  do
  {
    if(NEXT)
    {
      button_pressed_timer = millis();
      i++;
      menu_display_timer = millis();
      if(i == TOTAL_ITEMS_IN_MAIN_MENU)
      i=0;
      lcd.clear();
      lcd.print(m_menu[i][0]);
      lcd.setCursor(0,1);
      lcd.print(m_menu[i][1]);
      while(NEXT && millis() - button_pressed_timer < 1500);
    }
    if(millis() - menu_display_timer > MENU_TIMEOUT)
    {
      return 0;
    }
  }while(!SELECT);
  button_pressed_timer = millis();
  while(SELECT || millis() - button_pressed_timer < BUTTON_PRESS_TIME);
  return i;
}
