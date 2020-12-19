void definePin()
{
  pinMode(SELECT_PIN,INPUT);
  //pinMode(TEMPERATURE_PIN,INPUT);
  pinMode(NEXT_PIN,INPUT);
  //pinMode(CONNECTION_STATUS_LED,OUTPUT);
}

void radioInIt()
{
  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
  radio.begin();
  radio.setTXaddress((void*)txaddr);
  radio.setRXaddress((void*)rxaddr);
}
