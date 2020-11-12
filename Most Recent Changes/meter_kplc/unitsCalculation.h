#ifndef CalculationHEADS_H
#define calculationHEADS_H

float getVPP()
{
  float result;
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 4096;          // store min value here, vlue for 12bit ADC
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue = analogRead(currentPin);
       //Serial.println(readValue);
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           /*record the maximum sensor value*/
           minValue = readValue;
       }
   }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 3.3)/4096.0;
   return result;
}

double get_Units()
{
  consumption_time = millis();
  Voltage = getVPP();
  //Serial.println(Voltage);
  VRMS = (Voltage/2.000) *0.707;     //get RMS value of sampled voltage
  AmpsRMS = (VRMS * 1000)/mVperAmp;   //convert to current using sensor sensitivity
  power_consumed = AmpsRMS * consumption_Voltage;
  hours = (millis() - consumption_time)/3600;
  kilowatt_hour_consumed = (power_consumed * hours)/1000;
  current_units = current_units - kilowatt_hour_consumed;    //subtract power consumed from units available
  cumulative_cons = cumulative_cons + kilowatt_hour_consumed;   //add each unit consumed to cumulative consumption
  return current_units;
}

#endif
