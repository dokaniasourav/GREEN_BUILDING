void radioInIt()
{
  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
  radio.begin();
  radio.setTXaddress((void*)txaddr);
  radio.setRXaddress((void*)rxaddr);
}
