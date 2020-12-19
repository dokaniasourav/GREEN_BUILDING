/*
void transmitAcData()
{
  byte whichAc,index;
  for(whichAc = 0; whichAc <3; whichAc++)
  {
    index = acStatus[CURRENT]&(1<<whichAc)?1:0;
    if((acStatus[CURRENT]&(1<<whichAc))!=(acStatus[OLD]&(1<<whichAc)))
    digitalWrite(TX_PINS+whichAc,index);
  }
    PRINTln(F("TRANSMITED AC DATA SUCCESSFULLY"));
    
  acStatus[OLD]=acStatus[CURRENT];
}
/**/

/**/
void transmitAcData()
{
  byte whichAc,index;
  for(whichAc = 0; whichAc <NO_OF_AC; whichAc++)
  {
    if(((acStatus[CURRENT]&(1<<whichAc))!=(acStatus[OLD]&(1<<whichAc))) || ((onIndex[CURRENT] != onIndex[OLD]) && acStatus[CURRENT]&(1<<whichAc)))
    {
      index = acStatus[CURRENT]&(1<<whichAc)?(onIndex[CURRENT]):0;  //6128582 09102000
      //for(byte z=0; z <2; z++,delay(250))
      sendRemoteSignal((byte)(TX_PINS+whichAc), index);
      PRINT("TRANSMITED FOR AC NO. ");
      PRINTln(whichAc);
    }
  }
  acStatus[OLD]=acStatus[CURRENT];
}
/**/

void sendRemoteSignal(byte flash_pin, byte index)
{
  byte j = 0;
  uint64_t z = 2;
  
  digitalWrite(flash_pin, 1);
  delayMicroseconds(8500);        // Initial On Time (Little less given, actual time is 8564)
  digitalWrite(flash_pin, 0);
  delayMicroseconds(4200);       // Initial Off Time (Little less given, actual time is 4272)
  digitalWrite(flash_pin, 1);
  delayMicroseconds(500);             // 544 on time is fixed
  while(j < 28)
  {
    digitalWrite(flash_pin, 0);
    if(ac_remote_codes[index]&z)       // Off time may change accordingly
    {
      delayMicroseconds(1600);       // 1656 or 1632
    }
    else
    {
      delayMicroseconds(500);       // 544
    }
    digitalWrite(flash_pin, 1);
    delayMicroseconds(500);             // 544 on time is fixed
    z<<=2;
    j++;
  }
  digitalWrite(flash_pin, 0);
}
/**/
