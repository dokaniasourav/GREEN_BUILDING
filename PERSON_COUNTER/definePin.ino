void definePin()
{
  pinMode(RECIEVER_IN,INPUT);
  pinMode(RECIEVER_OUT,INPUT);
  pinMode(CONNECTION_STATUS_LED, OUTPUT);
  
  pinMode(DATA_PIN,OUTPUT);
  pinMode(CLOCK_PIN,OUTPUT);
  pinMode(LATCH_PIN,OUTPUT);
  pinMode(CLEAR_PIN,OUTPUT);
  digitalWrite(CLEAR_PIN,1);
}
