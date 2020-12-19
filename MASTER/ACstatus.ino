void generateAcStatus()
{
  if(pirStatus[OLD] != pirStatus[CURRENT] || flag!=0)
  {
    switch(personCount[CURRENT])
    {
        case 0:
        acStatus[CURRENT] = 0;
        break;
        
        case 1:
        if(pirStatus[CURRENT]==1 || pirStatus[CURRENT]==2 || pirStatus[CURRENT]==4 || acStatus[OLD] == 3 || acStatus[OLD] > 4)
        {
          if(pirStatus[CURRENT]==3 || pirStatus[CURRENT]>4)
          {
            flag++;
            acStatus[CURRENT] = acStatus[OLD];
          }
          else if(flag == 10)
          {
            acStatus[CURRENT] = pirStatus[CURRENT];
            flag = 0;
          }
          else
          acStatus[CURRENT] = pirStatus[CURRENT];
        }
        else if(pirStatus[CURRENT]==3||pirStatus[CURRENT]==5||pirStatus[CURRENT]==6)
        {
          if((pirStatus[CURRENT]^acStatus[OLD]) != 7)
          acStatus[CURRENT] = pirStatus[CURRENT]^acStatus[OLD];
          else
          acStatus[CURRENT] = pirStatus[CURRENT];
        }
        break;
        
        case 2:
        case 3:
        case 4:
        if(pirStatus[CURRENT])
        acStatus[CURRENT] = pirStatus[CURRENT];
        break;

        default:
        if(personCount[CURRENT] < 20)
        {
          if(pirStatus[CURRENT] == 3 || pirStatus[CURRENT] > 4)
          acStatus[CURRENT] = pirStatus[CURRENT];
        }
        else
        acStatus[CURRENT] = 7;
    }
    if(acStatus[OLD]!=acStatus[CURRENT])
    {
      PRINT("New AC status generated = ");
      PRINTln(acStatus[CURRENT],2);
      transmitAcData();                                                                    //If Commented here, don't forget to uncomment
    }
    pirStatus[OLD] = pirStatus[CURRENT];                                                      //PIR RENEWD
  }
}

void regulateAc()
{
      if(temperature[CURRENT] > t_high)
      {
        onIndex[CURRENT] = (performanceIndex[CURRENT] * 3) + 1;
      }
      else if(temperature[CURRENT] > t_med)
      {
        onIndex[CURRENT] = (performanceIndex[CURRENT] * 3) + 2;
      }
      else
      {
        onIndex[CURRENT] = (performanceIndex[CURRENT] * 3) + 3; 
      }
      if(onIndex[CURRENT] != onIndex[OLD])
      {
        PRINT("ON_INDEX New = ");
        PRINTln(onIndex[CURRENT]);
      }
}
