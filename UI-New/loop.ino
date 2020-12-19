void loop()
{
  /*
  if(millis() - update_timer > master_auto_update_time) // Send the data every 2 mins
  {
    //update_master = true;
    prev_person_count = 255;          // Just some bad value to trigger Update
    prev_temp = 255;                // Of master with current person count and Temperature
    update_timer = millis();
  }
  /**/
  if(SELECT)
  {
    button_pressed_timer = millis();
    command_to_send = mainMenu();
    if(command_to_send == 1)
    {
      setPersonCount();
    }
    else if(command_to_send == 2)
    {
      performanceMenu();
    }
    updateLcdData('x');
  }
  if(NEXT)
  {
    lcd.clear();
    lcd.print("  GREENOVATION");
    lcd.setCursor(3,1);
    lcd.print("TECHNOLADS");
    delay(500);
    while(NEXT);
    updateLcdData('x');
  }
  if(millis() - checkTime > 1000)
  {
    checkTime = millis();
    if(prev_person_count != person_count)
    {
      sendDataToMaster('p',0);
      updateLcdData('p');
      get_confirmation = true;
    }
    if(prev_performance_index != performance_index)
    {
        sendDataToMaster('i',0);
        updateLcdData('i');
        get_confirmation = true;
    }
    if(prev_temp != current_temp)
    {
      updateLcdData('t');
      sendDataToMaster('t',0);
      get_confirmation = true;
    }
    readTemperature();
    if(prev_connection_status != connection_status)
    {
      signalStrength();
      prev_connection_status = connection_status;
    }
  }
  incomingDataFromMaster();
  
  if(millis() < update_timer) // resets the timer variable after millis overflows
    resetAllTimers();
}
void resetAllTimers()
{
  update_timer = connection_status_timer = button_pressed_timer = master_auto_update_time = last_data_recieved_timer = checkTime = menu_display_timer = millis();
}
