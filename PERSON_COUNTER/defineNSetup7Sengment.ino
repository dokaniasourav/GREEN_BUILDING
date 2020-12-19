void define7SengmentNos()
{
  numbers[0]=0b11100111;//012567
  numbers[1]=0b10000100;//05
  numbers[2]=0b11010011;//01367
  numbers[3]=0b11010110;//01356
  numbers[4]=0b10110100;//0235
  numbers[5]=0b01110110;//12356
  numbers[6]=0b01110111;//123567
  numbers[7]=0b11000100;//015   
  numbers[8]=0b11110111;//0123567
  numbers[9]=0b11110110;//012356
}
void sevenSegmentStartUp()
{
  define7SengmentNos();
  for(int i=50; i-- ;delay(70-i)){
    shiftOutNumber(i);
    digitalWrite(CONNECTION_STATUS_LED,!digitalRead(CONNECTION_STATUS_LED));
  }
}
