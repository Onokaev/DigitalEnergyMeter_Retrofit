#ifndef writeToEepromHEADS_H
#define writeToEepromHEADS_H


void save_to_eeprom(float q)
{
  float in_mem;
  in_mem=EEPROM.read(0);
  if (abs(q-in_mem)>=0.1)
  {
      EEPROM.write(0, q);
      EEPROM.commit();
      Serial.print("Written: ");
      Serial.println(q);
  }
}

void save_time_to_EEPROM(int add, String time_to_write)
{
  int _size = time_to_write.length();
  int i;

  for(int i = 0; i<_size ; i++)
  {
    EEPROM.write(add+i, time_to_write[i]);
  }
  EEPROM.write(add+_size, '\0');  //add a null terminator for string
  EEPROM.commit();
  Serial.print("Saving time");
  Serial.println(time_to_write);
}


String read_time_from_EEPROM(int add)
{
  int i;
  float f = 0.00f;
  char the_data[100]; //maximum of 100 bytes
  int len = 0;
  unsigned char k;
  k = EEPROM.read(add);

  while(k != '\0' && len < 100)  //read until you get to the null character
  {
    k = EEPROM.read(add+len);
    the_data[len] = k;
    len++;
  }
  the_data[len] = '\0'; //add a null character to the data
  String pio = (String) the_data;
  Serial.print("Reading time: ");
  Serial.println(the_data);
  return String(the_data);  
}


#endif
