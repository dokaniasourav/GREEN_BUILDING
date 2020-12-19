void loop()
{
  checkNrfData();
  if(millis() - working > 5000)
  {
    working = millis();
    PRINTln("Master Module Running");
  }
  if(millis()<start)  // Millis RollBack
  {
    start = ON_SETTLING_TIME = OFF_SETTLING_TIME = millis();
    for(byte i=0;i<NO_OF_PIR;i++)
    {
      on_count[i]=off_count[i]=millis();
    }
  }
  if(millis()-start>CHECK_TIME)
  {
    gerneratePirStatus();
    generateAcStatus();
    readTemprature();
    if(acStatus[CURRENT] != acStatus[SENT])
    {
        moduleUpdate(UI_MODULE,'a',0);
        checkNrfData();
    }
    if(temperature[CURRENT]  != temperature[SENT])
    {
      moduleUpdate(UI_MODULE,'t',0);
      checkNrfData();
    }
    if(performanceIndex[CURRENT] != performanceIndex[SENT])
    {
      moduleUpdate(UI_MODULE,'i',0);
      checkNrfData();
    }
    /*if(personCount[SENT]  != personCount[CURRENT])
    {
      PRINTln("Done nothing");
      personCount[SENT] = personCount[CURRENT];
    }*/
    if(ui_update)
    {
        moduleUpdate(UI_MODULE,'p',0);
        checkNrfData();
    }
    if(pc_update)
    {
        moduleUpdate(PERSON_COUNTER,'p',0);
        checkNrfData();
    }
    if(personCount == 0)
        modifyPersonCount();
        
    if(temperature[CURRENT]  != temperature[OLD])
    {
      PRINT("TEMP NEW = ");
      PRINTln(temperature[CURRENT] );
      regulateAc();
      if(onIndex[CURRENT] != onIndex[OLD])
      {
        transmitAcData();
        onIndex[OLD] = onIndex[CURRENT];
      }
      temperature[OLD] = temperature[CURRENT];
    }
    start = millis();
  }
}
