 #ifndef GSMHEADS_H
#define GSMHEADS_H

void setup_GSM()
{
  //modem.restart();
  modem.init();
  String modemInfo = modem.getModemInfo();
  Serial.print("Modem Info: ");
  Serial.println(modemInfo);
  Serial.print("Waiting for network...");
    if(!modem.waitForNetwork()) 
    {
      Serial.println(" fail");
      delay(3000);
    }
    else
    {
      Serial.println(" success");
    } 
    if(modem.isNetworkConnected()) 
    {
      Serial.println("Network connected");
    }
    
    
#if TINY_GSM_USE_GPRS
  // GPRS connection parameters are usually set after network registration
    Serial.print(F("Connecting to "));
    Serial.print(apn);
    if (!modem.gprsConnect(apn, gprsUser, gprsPass)) 
    {
      Serial.println(" fail");
      delay(10000);
    }
    else
    {
      Serial.println(" success");
    }
    //Serial.println(" success");

  if (modem.isGprsConnected()) 
  {
    Serial.println("GPRS connected");
  }
#endif
}

void reconnect_Gprs()
{
  if (!modem.gprsConnect(apn, gprsUser, gprsPass)) 
  {
    Serial.println(" fail");
    delay(10000);
  }
  else
  {
    Serial.println(" success");
  }

}

void GSM_restart()
{
  modem.restart();
  setup_GSM();
}

#endif
