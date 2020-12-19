void incomingDataFromMaster()
{
  for(byte i = 0; i< 20; i++)
  {
    if(radio.available(true))
    {
      radio.read(recieved_data);
      Serial.print("Data Received = ");
      Serial.println(recieved_data);
      switch(recieved_data[0])
      {
      case 'p':
          person_count = recieved_data[1];
          Serial.print("Person Count Recv. = ");
          Serial.println(person_count);
          shiftOutNumber(person_count);
          delay(1);
          sendDataToMaster('c');
          break;
      case 'c':
           Serial.print("Conf. Recv. for ");
           if(recieved_data[1] == 'p')
           {
              prev_person_count = person_count;
              Serial.println("PC");
           }
           else if(recieved_data[1] == 't')
           {
             prev_temp = current_temp;
             Serial.println("Temp");
           }
          get_confirmation = false;
          break;
        /*
        * Any other cases that may arise from data transmissions
        * Like special commands sent by the master
        */
      default:
        Serial.println("Unknown Message");
      }
      break;
    }
  }

    if(get_confirmation && (millis()-connection_status_timer > CONNECTION_STATUS_TIME))  // If a confirmation was not received
    {
      Serial.println("Connection Timeout");
      connection_status = 0;
      get_confirmation = false;
    }
}
