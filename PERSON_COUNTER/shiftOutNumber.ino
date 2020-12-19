void shiftOutNumber(int num)
{
  byte c;
  byte data = numbers[num/10];
  c = data&0b11000000;
  data <<=2;
  c >>= 6;
  data |= c;
  c = 0x80;
  while(c)
  {
    digitalWrite(CLOCK_PIN,LOW);
    digitalWrite(DATA_PIN,(data&c));
    digitalWrite(CLOCK_PIN,HIGH);
    c>>=1;
  }
  c=1;
  data = numbers[num%10];
  while(c)
  {
    digitalWrite(CLOCK_PIN,LOW);
    digitalWrite(DATA_PIN,(data&c));
    digitalWrite(CLOCK_PIN,HIGH);
    c<<=1;
  }
  digitalWrite(LATCH_PIN,HIGH);
  digitalWrite(LATCH_PIN,LOW);
}
