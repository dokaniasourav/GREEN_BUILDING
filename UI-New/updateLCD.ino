void lcdInIt()
{
  delay(5);
  lcd.createChar(4, tower);
  delay(5);
  lcd.createChar(0, low_signal);
  delay(5);
  lcd.createChar(1, mid_signal1);
  delay(5);
  lcd.createChar(2, mid_signal2);
  delay(5);
  lcd.createChar(3, high_signal);
  delay(5);
  lcd.createChar(5, person);
  delay(5);
  lcd.begin(16, 2);
  delay(100);
  lcd.print("  WELCOME BACK");
  lcd.setCursor(0,1);
  lcd.print("UPDATING DATA");
  checkTime = millis();
  byte j = 0;
  while(millis() - checkTime < 2000)
  {
    Serial.println("Startup Request");
    
    while(++j)
    incomingDataFromMaster();
  }
  lcd.setCursor(16,0);
  lcd.autoscroll();
  char *s1 = "GREENOVATION TECHNOLADS";
  char *s2 = "SAVE ENERGY, SAVE EARTH";
  lcd.print(s1);
  lcd.setCursor(16,1);  
  lcd.print(s2);
  lcd.autoscroll();
   while(j<16){
    lcd.print(" ");
    delay(250);
    j++;
  }
  lcd.noAutoscroll();
  updateLcdData('x');
}
void updateLcdData(char header)
{
    switch(header)
    {
    case 't':
        lcd.setCursor(0,0);
        lcd.print(current_temp);
        lcd.setCursor(3,0);
        lcd.print((char)223);           //degree sign
        lcd.print("C");
        break;
    case 'p':
        lcd.setCursor(6,0);
        lcd.print(person_count/10);
        lcd.print(person_count%10);
        lcd.write(byte(5));
        break;
        
    case 'a':
        lcd.setCursor(10,0);
        lcd.print(ac_status%2);
        lcd.print(" ");
        lcd.print((ac_status/2)%2);
        lcd.print(" ");
        lcd.print(ac_status/4);
        break;
    case 'i':
        lcd.setCursor(0,1);
        for(byte i=0; i<=performance_index; i++)
        lcd.print("*");
        break;
    case 'h':
        signalStrength();
        break;
     default:
        lcd.clear();
        updateLcdData('t');
        updateLcdData('p');
        updateLcdData('a');
        updateLcdData('i');
        updateLcdData('h');
    }
}
