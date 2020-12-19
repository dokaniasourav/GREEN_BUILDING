void gerneratePirStatus() //millis() overflow is dangerous here
{
  byte whichPir;
  for(whichPir=0; whichPir<NO_OF_PIR; whichPir++)
  {
    //digitalWrite(14+whichPir,digitalRead(PIR_PINS+whichPir));
    if(digitalRead(PIR_PINS[whichPir]) && last_pir[whichPir] == false)
    {
      on_count[whichPir] = millis();
      last_pir[whichPir] = true;
    }
    else if(digitalRead(PIR_PINS[whichPir]) == 0 && last_pir[whichPir] == true)
    {
      off_count[whichPir] = millis();
      last_pir[whichPir] = false;
    }
    else if(millis()- on_count[whichPir] > ON_SETTLING_TIME && last_pir[whichPir] == true)
    {
      pirStatus[CURRENT] |= (1<<whichPir);
      on_count[whichPir] = millis();
    }
    else if(millis()- off_count[whichPir] > OFF_SETTLING_TIME && last_pir[whichPir] == false)
    {
      pirStatus[CURRENT] &= ~(1<<whichPir);
      off_count[whichPir] = millis();
    }
  }
  if(pirStatus[OLD] != pirStatus[CURRENT])
  {
    PRINT(F("Generated PIR STATUS = "));
    PRINT(pirStatus[CURRENT]%2);
    PRINT((pirStatus[CURRENT]/2)%2);
    PRINTln(pirStatus[CURRENT]/4);
  }
}

void changePirTimers()
{
  switch(personCount[CURRENT])
  {
    case 0:
    if(zeroPersonDataNotTransmitted)
    {
      acStatus[CURRENT] = 0;
      acStatus[OLD] = 7;
      transmitAcData();
      zeroPersonDataNotTransmitted = false;
    }
    break;
    
    case 1:
    ON_SETTLING_TIME = 3000;
    OFF_SETTLING_TIME = 4000;
    zeroPersonDataNotTransmitted = true;
    break;
    
    default:
    ON_SETTLING_TIME = 3000;
    //OFF_SETTLING_TIME =(unsigned long)(60000 + (30000*personCount));
    OFF_SETTLING_TIME = 4000;
    zeroPersonDataNotTransmitted = true;
    break;
  }
  PRINT("CHANGED PIR TIMERS = ");
  PRINTln(OFF_SETTLING_TIME);
}


