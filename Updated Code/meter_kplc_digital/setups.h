#ifndef setUpHEADS_H
#define setUpHEADS_H


void setup_GPIO()
{
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(currentPin,INPUT);
  pinMode(ac_power, INPUT);
  pinMode(relayPin, OUTPUT);
  Serial.begin(BAUD_RATE);
  SerialAT.begin(BAUD_RATE);
  digitalWrite(relayPin, HIGH);
  EEPROM.begin(EEPROM_SIZE);
  current_units = EEPROM.read(0);   //units last saved
  previous_time = read_time_from_EEPROM(30);
  Serial.print("Units saved: ");
  //Serial.println(current_units);
  Serial.print("Time saved: ");
 // Serial.print(previous_time);

  pinMode(interruptPin, INPUT_PULLUP);
}

#endif
