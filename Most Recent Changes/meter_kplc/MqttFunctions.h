#ifndef MQTTHEADS_H
#define MQTTHEADS_H
#include "GsmFunctions.h"
#include "timeComparison.h"

void mqttCallback(char* topic, byte* payload, unsigned int len) 
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.write(payload, len);
  Serial.println();
  String messageTemp;

  for (int i=0; i < len; i++)
  {
    Serial.print((char)payload[i]);
    messageTemp += (char)payload[i];
  }
  Serial.println();
  Serial.println();

  // Only proceed if incoming message's topic matches
  if (String(topic) == topicLed) 
  {
    Serial.print(messageTemp);

    //function to check the time and verify that it is a different transmission
    //pass messageTemp
    get_time_and_units(messageTemp);
    received_units = getUnits();  //returns the units received after verification
    //received_units = messageTemp.toDouble();
    Serial.print("Units: ");Serial.print(received_units);

    if(received_units > 0.00)
    {
      current_units = current_units + received_units;
    }
    else{pass();}
    
    
    Serial.println(current_units);

    if (current_units > 0)               //if new units is greater than 0, reconnect the customer
    {
      digitalWrite(relayPin, HIGH);
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin, LOW);
      //Serial.println(current_units);
    }
    else{pass();}
  }
  else
  {
    pass();
  }
  Serial.println(); 
    
  }


void mqttConnect() 
{
  Serial.print("Connecting to ");
  Serial.print(broker);
  // Connect to MQTT Broker
  char separator = '/';

  while(!mqtt.connected())
  {
    Serial.println("Attempting mqtt connection...");
    if (mqtt.connect("ESP32Client", "qxthyopl" , "VcMajZtxlQVJ", willTopic, willQos, willRetain, willMessage, cleanSession))
    {
      Serial.println("Connected");
      mqtt.subscribe(topicLed,1);

      if(consumption_flag == true)  ///for sending daily consumption update to the server 
      {
        //construct the payload to send
        //publish(const char* topic, const char* payload, boolean retained)
        double the_current_units = current_units;
        double the_consumption_data = cumulative_cons;
        
        for (int j = 0; j < sizeof(packet_to_transmit); j++)
        {
          packet_to_transmit[j] = 0;
        }
        // #message format is kplc/consumption_update/meter_number/consumption_update/units_remaining
        //pack the data to be transmitted
        sprintf(packet_to_transmit,"%s%c%f%c%f",meterNumber, separator, the_consumption_data, separator, the_current_units);
        mqtt.publish(consumptionUpdate, packet_to_transmit ,true);
        Serial.print("packet to transmit");
        Serial.println(packet_to_transmit);
        consumption_flag = false;
      }
      
    }
    else
    {
      Serial.print("Failed, rc = ");
      Serial.print(mqtt.state());
      Serial.println("Trying again in 5 seconds");
      Serial.println();
      delay(2000);
      counter++;
      counter_restart++;
    }
    if (counter > 4 && current_units < 5.00)  //connection is urgrent. Therefore restart to ensure it is connected
    {
      setup_GSM();
      counter = 0;
    }
    if (counter_restart > 10 && current_units > 1.500)
    {
      Serial.println("Restarting the GSM");
      counter_restart = 0;
      GSM_restart();
      //restart the modem
    }
  } 
  //return mqtt.connected();
}

#endif
