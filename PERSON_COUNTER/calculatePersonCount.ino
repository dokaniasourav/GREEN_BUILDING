void checkData()
{
  for(byte i=0; i<10; i++){
  if(!digitalRead(tsop_pins[TSOP_IN]))
  {
    timers[TSOP_IN] = millis();
  }
  if(!digitalRead(tsop_pins[TSOP_OUT]))
  {
    timers[TSOP_OUT] = millis();
  }
  }
}
void checkTimers()
{
  if(millis() - timers[TSOP_IN] > DATA_THRES)
    personCountCalculate(TSOP_IN);
  
  if(millis() - timers[TSOP_OUT] > DATA_THRES)
    personCountCalculate(TSOP_OUT); 
}

void personCountCalculate(byte current)
{
  /*Serial.print("Timers = ");
  Serial.print(timers[TSOP_IN]);
  Serial.print("  ");
  Serial.print(timers[TSOP_OUT]);
  Serial.print("  ");
  Serial.print(millis());
  Serial.print("  ");
  Serial.println(millis()-timers[current]);*/
  
  byte other;
  if(current == TSOP_IN)
    other = TSOP_OUT;
  else
    other = TSOP_IN;
    
   Serial.println("CALLED "+msg[current]);
    bool breakpoint = false;
    while(digitalRead(tsop_pins[current]) && breakpoint == false)
    {
      checkData();
      if(millis() - timers[other] > DATA_THRES)
      {
        while(1)
        {
          if(!digitalRead(tsop_pins[current]))
          {
            Serial.println("Person "+msg[current]);
            if(current == TSOP_IN)
            {
              if(person_count == 0)
                Serial.println("--NO--");
              else
                person_count--;
            }
            else
              person_count++;
            Serial.print("New Person Count = ");
            Serial.println(person_count);
            breakpoint = true;
            
            /**/
            for(int i=1;i<5;i++)
            {
              digitalWrite(CONNECTION_STATUS_LED,0);
              shiftOutNumber(0);
              delay(15);
              digitalWrite(CONNECTION_STATUS_LED,1);
              shiftOutNumber(person_count);
              delay(15);
            }
            break;
            /**/
          }
          if(!digitalRead(tsop_pins[other]))
          {
            breakpoint = true;
            break;
          }
        }
      }
      if(millis() - timers[current] > TOO_LONG)
      {
         Serial.println("LONG TIME NO DATA "+msg[current]);
         timers[current] = millis();
         breakpoint = true;
         break;
      }
    }
    timers[current] =  millis();
    timers[other] =  millis();
    //digitalWrite(CONNECTION_STATUS_LED,0);
    Serial.println("Function Exit");
}
/*
void person_countCalculate(byte current)
{
  byte other;
  if(current == TSOP_IN)
    other = TSOP_OUT;
  else
    other = TSOP_IN;
    
   Serial.println("CALLED "+msg[current]);
  bool breakpoint = false;
  while(digitalRead(tsop_pins[current]) && breakpoint == false)
  {
    checkData();
    delay(1);
    if(millis() - timers[other] > DATA_THRES)
    {
      while(1)
      {
        if(!digitalRead(tsop_pins[current]))
        {
          Serial.println("Person went "+msg[current]);
          if(current == TSOP_IN)
          {
            if(person_count == 0)
              Serial.println("--NO--");
            else
            {
              person_count--;
            }
          }
          else
          {
            person_count++;
          }
          Serial.print("New Person Count = ");
          Serial.println(person_count);
          breakpoint = true;

          for(int i=0;i<6;i++)
          {
            digitalWrite(CONNECTION_STATUS_LED,0);
            shiftOutNumber(0);
            delay(15);
            digitalWrite(CONNECTION_STATUS_LED,1);
            shiftOutNumber(person_count);
            delay(15);
          }
          break;
        }
        if(!digitalRead(tsop_pins[other]))
        {
          breakpoint = true;
          break;
        }
      }
    }
    /*if(millis() - timers[current] > TOO_LONG)
    {
       Serial.println("LONG TIME NO DATA "+msg[current]);
       timers[current] = millis();
       breakpoint = true;
       break;
    }
  }
  timers[current] = timers[other] =  millis();
  Serial.println("Function Exit");
  //digitalWrite(CONNECTION_STATUS_LED,0);
}*/
