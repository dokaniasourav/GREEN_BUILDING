/*unsigned int i2c_eeprom_read_int(unsigned int eeaddress ) 
{
    unsigned int rdata = 0;
    Wire.beginTransmission(DEVICE_ADD);
    Wire.write((int)(eeaddress >> 8)); // MSB
    Wire.write((int)(eeaddress & 0xFF)); // LSB
    Wire.endTransmission();
    Wire.requestFrom(DEVICE_ADD,2);
    if (Wire.available()) rdata = Wire.read();
    rdata<<=8;
    if (Wire.available()) rdata |= Wire.read();
    return rdata;
 }
 */




