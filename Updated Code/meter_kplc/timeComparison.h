#ifndef ComparisonHEADS_H
#define ComparisonHEADS_H
#include "writeToEeprom.h"

//this function sets the global variables the_time and the_unit
//this function also decodes the units

void get_time_and_units(String message)
{
  char separator = '/';
  int to = 0;
  int from  = 14;  //the first 9 numbers are for the encryption
  int message_length = message.length();
  int i = 0;

  //for (i = 0; i<message_length; i++)
  while(!(message.charAt(i) == separator))  //
  {
    to++; 
    Serial.print("to: ");
    Serial.println(to);
    i++;
    if(to > 22){
      break;}
  }
  String meter_portion_from_unit = message.substring(0, 5);
  Serial.print("meter_portion_from_unit ");
  Serial.println(meter_portion_from_unit);
  meter_portion_from_unit.trim();
  String meter_portion =  "";

  for(int i=0; i<4 ;i++){
    meter_portion += (String) *(meterNumber + i);
  }
  meter_portion.trim();
  Serial.print("meter portion from code ");
  Serial.println(meter_portion);

  if(meter_portion_from_unit != meter_portion)  //check if the parts of the meter_number received resemble the actual meter number
  {
    the_unit = "0";
    Serial.println("Meter numbers don't match ");
    return;
  }
  
  the_unit = message.substring(from,to);
  Serial.print("Units extracted: ");
  Serial.println(the_unit);
  to = to + 1;
  the_time = message.substring(to, message_length);  //copy the time into this time variable
  Serial.print("the time: ");
  Serial.println(the_time);
}


double getUnits()
{
  if (previous_time == the_time)
  {
    Serial.println("They are the same");
    new_units = 0;
    return new_units;
  }
  else
  {
    //assign the_time to previous time
    previous_time = the_time;  //save this for the next comparison 
    
    save_time_to_EEPROM(30, previous_time);
    new_units = the_unit.toDouble();
    return new_units;
  }
}

#endif
