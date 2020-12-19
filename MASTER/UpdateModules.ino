void moduleUpdate(byte module, char header, char subHeader)
{
    radio.disableRX();
    PRINT("Data sent to ");
    if(module == PERSON_COUNTER)                        //Select Module
    {
        PRINT("PC ");
        radio.setTXaddress((void*)txaddr[0]);
        connection_status_timer_pc = millis();         // Update connection status
    }
    else
    {
        PRINT("UI ");
        radio.setTXaddress((void*)txaddr[1]);
        connection_status_timer_ui = millis();         // Update connection status
    }
    send_data[0] = header;
    PRINT("Data = ");
    PRINT(header);
    switch(header)                                      //Select Data to send
    {
    case 'p':
        if(module == PERSON_COUNTER)
            get_confirmation_pc = true;
        else
            get_confirmation_ui = true;

        send_data[1] = personCount[CURRENT];
        break;
    case 'a':
        send_data[1] = acStatus[CURRENT];
        get_confirmation_ui = true;
        break;
    case 't':
        send_data[1] = averageTemp;
        get_confirmation_ui = true;
        break;
    case 'c':                    //Confirmation to send
        if(module == PERSON_COUNTER)
        {
          PRINT("Confirmation SENT to PC ");
          pc_update = false;
        }
        else
        {
          PRINT("Confirmation SENT to UI ");  
          ui_update = false;
        }
        PRINTln(subHeader);
        send_data[1] = subHeader;               //Attach required subHeader
        break;
    }
    radio.print(send_data);                     // Finally Send the data
    radio.flush();
    PRINT(send_data[1],DEC);
    PRINTln();
    radio.enableRX();
}
