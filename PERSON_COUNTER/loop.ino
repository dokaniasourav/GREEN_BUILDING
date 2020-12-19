void loop()
{
  // PERSON COUNTER CODE
  checkData();
  checkTimers();
  delay(1);
  if(millis() - update_timer > master_auto_update_time) // Send the person count every 2 Minutes
  {
    update_timer = millis();
    prev_person_count = 255;          // Just some bad value to trigger Update
    prev_temp = 255;                // Of master with current person count and Temperature
  }
  if(millis() - checkTime > 1000)
  {
    checkTime = millis();
    if(prev_person_count != person_count)                    //If person count changed
    {
        sendDataToMaster('p');
    }
    if(prev_temp != current_temp)                    //If Temperature changed
    {
        sendDataToMaster('t');
    }
    if (millis() - temperature_update_timer > TEMPERATURE_UPDATE_TIME)        //Read temperature every now and then
    {
      readTemprature();
      temperature_update_timer = millis();
    }  
    if(millis() < update_timer) // resets the timer variable after any millis overflows
    timers[0] = timers[1] = update_timer = checkTime = connection_status_timer = temperature_update_timer = millis(); 
    
    if(connection_status == 1) // for good connection slower update speed
    {
      digitalWrite(CONNECTION_STATUS_LED, LOW);
      master_auto_update_time = 120000;
    } 
    else // for poor connection faster update speed
    {
      digitalWrite(CONNECTION_STATUS_LED, HIGH);
      master_auto_update_time = 30000;
    }
    delay(PROGRAME_DELAY);
  }
  incomingDataFromMaster();
  /**/
}
