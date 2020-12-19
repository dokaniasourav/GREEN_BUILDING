void sendDataToMaster(char header, char subHeader)
{
  radio.disableRX();
  radio.setTXaddress((void*)txaddr);
  send_data[1] = header;
  switch(header)
  {
    case 'p':
        send_data[2] = person_count;
        break;
    case 't':
        send_data[2] = current_temp;
        break;
    case 'i':
        send_data[2] = performance_index;
        break;
    default:
        send_data[2] = subHeader;
  }
  send_data[3] = 0;
  Serial.print("Data Sent = ");
  Serial.println(send_data);
  radio.print(send_data);
  radio.flush();
  connection_status_timer = millis();
  radio.setRXaddress((void*)rxaddr);
  radio.enableRX();
}
