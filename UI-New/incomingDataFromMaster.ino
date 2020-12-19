void incomingDataFromMaster()
{
  for(byte i = 0; i<250;  i++)
  {
    if(radio.available(true))
    {
      radio.read(recieved_data);
      updateLcdData(recieved_data[0]);
      last_data_recieved_timer = millis();
      connection_status |= 2;
      Serial.print("Data Recv.= ");
      switch(recieved_data[0])
      {
      case 'p':
          person_count = recieved_data[1];
          Serial.print("PC = ");
          Serial.println(recieved_data[1],DEC);
          NOMINAL_DELAY
          sendDataToMaster('c','p');
          break;
      case 't':
          Serial.print("Temp = ");
          Serial.println(recieved_data[1],DEC);
          temperature = recieved_data[1];
          NOMINAL_DELAY
          sendDataToMaster('c','t');
          break;
      case 'a':
          Serial.print("AC = ");
          Serial.println(recieved_data[1],DEC);
          ac_status = recieved_data[1];
          NOMINAL_DELAY
          sendDataToMaster('c','a');
          break;
      case 'c':
          Serial.print("Conf = ");
          Serial.println(recieved_data[1]);
          if(recieved_data[1] == 'p')
              prev_person_count = person_count;
          else if(recieved_data[1] == 't')
              prev_temp = current_temp;
          else if(recieved_data[1] == 'i')
              prev_performance_index = performance_index;
          get_confirmation = false;
          connection_status |= 1;
          break;
          //Serial.println("Unknown Message");
      }
      break;
    }
  }
  if(millis() - last_data_recieved_timer > LAST_DATA_RECIEVED_TIME)
  {
    connection_status &= 0b11111101;
    last_data_recieved_timer = millis();
    Serial.println("No data Recieved in a while");
  }
  if(get_confirmation && (millis()-connection_status_timer > CONNECTION_STATUS_TIME))  // If a confirmation was not received
  {
     connection_status &= 0b11111110;
     connection_status_timer = millis();
     Serial.println("Cofirmation Recieve Timeout");
  }
}
