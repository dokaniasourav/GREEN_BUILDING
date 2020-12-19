void radioInit()
{
  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
  radio.begin();
  radio.setRXaddress((void*)rxaddr);
}

void ioSetup()
{
  byte i;
  for(i=0; i<NO_OF_TX; i++)
  {
    pinMode(TX_PINS+i,OUTPUT);
  }
  for(i=0; i<NO_OF_PIR; i++)
  {
    pinMode(PIR_PINS[i],INPUT);
    digitalWrite(PIR_PINS[i],LOW);
  }
}
