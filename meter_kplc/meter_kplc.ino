#include "meterHeaders.h"
#include "MqttFunctions.h"
#include "GsmFunctions.h"
#include "setups.h"
#include "unitsCalculation.h"
#include "timeComparison.h"

void setup()     //when it boots, we read the current_units balance from eeprom
{
  setup_GPIO();
  //relays work with reverse logic, set them high to turn them off
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Initializing");
  
  xTaskCreatePinnedToCore(
    Task1Code,       //the function to implement this task
    "Task1",         //name of task
    100000,            //stack size in words
    NULL,            //Task input parameter
    1,               //Priority of task
    &Task1,          //Task handle
    0);              //Core where task should run

    delay(500);

  xTaskCreatePinnedToCore(
    Task2Code,
    "Task2",
    100000,
    NULL,
    1,
    &Task2,
    1);
    delay(500);
}

void Task1Code(void *parameters)
{
  Serial.print("Task1 running on core: ");
  Serial.println(xPortGetCoreID());
  cumulative_cons = 0;

  
  for (;;)
  {
    //calculate energy consumed only when current units greater than 0 and stop when the value falls to 0. disconnect the customer at this point
       
      while (current_units > 0.00)
      {
        current_units = get_Units();
        //save_to_eeprom(current_units);
        lcd.init();    //lcd is getting a lot of noise. so do this
        lcd.backlight();
        lcd.print(current_units);
        delay(500);
      }
      if(current_units < 0.00)
      {
        current_units = 0.00;  //set to 0 to avoid negatives
        digitalWrite(relayPin, LOW);
        digitalWrite(ledPin1, LOW);
        digitalWrite(ledPin, HIGH);
        lcd.init();
        lcd.backlight();
        lcd.print("Units used up");
        delay(700);
      }
  }
 }

void Task2Code(void *parameters)
{
  Serial.print("Task2 running on core: ");
  Serial.println(xPortGetCoreID());
  Serial.println("Initializing modem...");
  setup_GSM();
  // MQTT Broker setup
  mqtt.setServer(broker, 12702);
  mqtt.setCallback(mqttCallback);
  long int consumption_time = millis();

  for(;;)
  {
    Serial.println(current_units);
    if (!mqtt.connected())   //if units go below 0.00, task1 will disconnect customer
      {
        mqttConnect();
       // http_post_transmit_consumption_data("56");
      }
      mqtt.loop(); 

      if(millis() - consumption_time > 1000)  //3,600,000
      {
        consumption_time = millis();
        consumption_flag = true;
      }
  }
}


void loop()
{
  TIMERG0.wdt_wprotect=TIMG_WDT_WKEY_VALUE;
  TIMERG0.wdt_feed=1;
  TIMERG0.wdt_wprotect=0;
}
