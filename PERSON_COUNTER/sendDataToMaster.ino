void sendDataToMaster(char header)
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
  }
  send_data[3] = 0;
  Serial.print("Data Sent = ");
  Serial.println(send_data[2], DEC);
  radio.print(send_data);
  radio.flush();
  connection_status_timer = millis();
  get_confirmation = true;
  radio.setRXaddress((void*)rxaddr);
  radio.enableRX();
}
