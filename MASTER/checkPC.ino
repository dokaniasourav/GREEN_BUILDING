void modifyPersonCount()
{
  if(mofifyPersonCounterFlag>50)
  {
    personCount[CURRENT] = 1;
    pc_update = true;
    ui_update = true;
    mofifyPersonCounterFlag = 0;
    PRINTln("Modified Person Count");
  }
  if(pirStatus[CURRENT])
  {
    mofifyPersonCounterFlag++;
  }
}

void readTemprature()
{
  analogRead(TEMPSENSOR);
  int Temp=0;
  for(byte i=0; i<5; i++)
  {
    Temp += ((int32_t)analogRead(TEMPSENSOR)*27069 - 18169625) *10 >> 16;
    //Temp = 125;
    delay(1);
  }
  temperature[CURRENT] = (byte)(Temp/50);
  PRINT("Temp, ");
  PRINT(" PC=");
  PRINT(pcTemp);
  PRINT(" M=");
  PRINT(temperature[CURRENT]);
  PRINT(" UI=");
  PRINTln(uiTemp);
  //send_ui_update.temperature = currentTemp;
  averageTemp = (temperature[CURRENT] + pcTemp + uiTemp) / 3 ;
}
