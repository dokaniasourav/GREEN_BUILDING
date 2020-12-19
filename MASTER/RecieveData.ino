void checkNrfData()
{
    for(byte i = 0; i<250;  i++)
    {
      if(radio.available(true))
      {
        radio.read(recieved_data);
        PRINT("Data Received From ");
        if(recieved_data[0] == 'P')           // Data from person counter then UI must be updated with personCount
        {
            PRINT("PC = ");
            switch(recieved_data[1])
            {
              case 'p':
                PRINT("Person Count = ");
                PRINTln(recieved_data[2], DEC);
                personCount[CURRENT] = recieved_data[2];
                changePirTimers();
                ui_update = true;
                //delay(10);
                moduleUpdate(PERSON_COUNTER, 'c', 'p');
              break;
              case 't':
                PRINTln("Temp = ");
                PRINTln(recieved_data[2], DEC);
                pcTemp = recieved_data[2];
                moduleUpdate(PERSON_COUNTER, 'c', 't');
              break;
              case 'c':
                PRINTln("Confirmation from PC");
                pc_update = false;
                get_confirmation_pc = false;
              break;
              case 'r':                     // Request from Person counter for data
              PRINTln("Request");
              moduleUpdate(PERSON_COUNTER, 'p', 0);
              break;
            }
        }
        else                         // From the UI
        {
            PRINT("UI = ");
            PRINT(recieved_data[1]);
            switch(recieved_data[1])
            {
            case 'p':
                pc_update = true;
                personCount[CURRENT] = recieved_data[2];
                PRINT("Person Count = ");
                PRINTln(recieved_data[2],DEC);
                changePirTimers();
                moduleUpdate(UI_MODULE, 'c', 'p');
                break;
            case 't':
                uiTemp = recieved_data[2];
                moduleUpdate(UI_MODULE, 'c', 't');
                PRINT(recieved_data[2],DEC);
                break;
            case 'r':
                moduleUpdate(UI_MODULE,'p',0);
                moduleUpdate(UI_MODULE,'t',0);
                moduleUpdate(UI_MODULE,'a',0);
                moduleUpdate(UI_MODULE,'i',0);
                PRINTln("UI Updated");
                break;
            case 'i':
                setPerformanceIndex(recieved_data[2]);
                moduleUpdate(UI_MODULE, 'c', 'i');
                PRINT(recieved_data[2],DEC);
                break;
            case 'c':
                PRINT(recieved_data[2]);
                if(recieved_data[2] == 'p')                                              // Confirmation from user Interface
                {
                    ui_update = false;
                }
                else if(recieved_data[2] == 't')
                    temperature[SENT] = temperature[CURRENT];
                else if(recieved_data[2] == 'a')
                    acStatus[SENT] = acStatus[CURRENT];
                else if(recieved_data[2] == 'i')
                    performanceIndex[SENT] = performanceIndex[CURRENT];
                    
                get_confirmation_ui = false;
                break;
            default:
              PRINTln("Unknown Message from UI");
            }
            PRINTln();
        }
        break;
      }
    }
    if(get_confirmation_pc && (millis()-connection_status_timer_pc > CONNECTION_STATUS_TIME))  // If a confirmation was not received
        connection_status_pc = false;
    if(get_confirmation_ui && (millis()-connection_status_timer_ui > CONNECTION_STATUS_TIME))  // If a confirmation was not received
        connection_status_ui = false;
}

void setPerformanceIndex(char index)
{
    performanceIndex[CURRENT] = index;
    PRINT("PERFORMANCE_INDEX RECIEVED = ");
    PRINTln(performanceIndex[CURRENT]);
    if(performanceIndex[CURRENT] == 0) // HIGH PERFORMANCE
    {
        t_high = 26; //dummy
        t_med = 20;
        regulateAc();
    }
    else if(performanceIndex[CURRENT] == 1) // NORMAL MODE
    {
        t_high = 24;
        t_med = 20;
        regulateAc();
    }
    else if(performanceIndex[CURRENT] == 2) // ECONOMY MODE
    {
        t_high = 26;
        t_med = 22;
        regulateAc();
    }
    else
       PRINTln("Invalid P Data");
}
