void signalStrength()
{
  lcd.setCursor(13,1);
  lcd.write(byte(4));
  lcd.write(byte(connection_status));
  master_auto_update_time = MASTER_AUTO_UPDATE_TIME/(5-connection_status);
/*  if(connection_status == 2 || connection_status == 3)
  {
    lcd.write(byte(1));
    lcd.setCursor(14,1);
    lcd.write(byte(3));
    lcd.setCursor(15,0);
    lcd.write(byte(4));
    //analogWrite(CONNECTION_STATUS_LED, 255);
    master_auto_update_time = MASTER_AUTO_UPDATE_TIME;
  }
  else if(connection_status == 1)
  {
    lcd.write(byte(1));
    lcd.setCursor(14,1);
    lcd.write(byte(3));
    lcd.setCursor(15,0);
    lcd.print(" ");
    //analogWrite(CONNECTION_STATUS_LED, 64);
    master_auto_update_time = MASTER_AUTO_UPDATE_TIME / 4;
  }
  else
  {
    lcd.write(byte(2));
    lcd.setCursor(14,1);
    lcd.write(byte(5));
    lcd.setCursor(15,0);
    lcd.print(" ");
    //analogWrite(CONNECTION_STATUS_LED, 0);
    master_auto_update_time = MASTER_AUTO_UPDATE_TIME / 10;
  }
  */
}
