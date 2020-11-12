#ifndef METERHEADS_H
#define METERHEADS_H

#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"

#include <stdlib.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <PubSubClient.h>
#include <EEPROM.h>
#include <String.h>
#define pass(void)
#define TX_Pin 25
#define RX_Pin 26
SoftwareSerial SerialAT(RX_Pin, TX_Pin);
const int BAUD_RATE = 9600;   //serial speed of sim800l and monitor

#define TINY_GSM_MODEM_SIM800
//define how you intend to connect to internet
#define TINY_GSM_USE_GPRS true
#define TINY_GSM_USE_WIFI false

// Your GPRS credentials, if any
const char apn[] = "";
const char gprsUser[] = "";
const char gprsPass[] = "";


// MQTT details
const char* broker = "tailor.cloudmqtt.com";
// if (mqtt.connect("ESP32Client", "qxthyopl" , "VcMajZtxlQVJ"))
const char* topicLed = "KPLC/14299";
const char* consumptionUpdate = "kplc/consumption_update";  //topic for sending consumption updates

const char* meterNumber = "14299";
const char* willTopic = "device/Fail";
int willQos = 1;
int willRetain = 1;
const char* willMessage = "Disconnected";
boolean cleanSession = false;
uint16_t counter = 0;
uint16_t counter_restart = 0;  //if rc = -1 for more than 10 times, restart the GSM
  

#include <TinyGsmClient.h>
#include <PubSubClient.h>

TinyGsm modem(SerialAT);
TinyGsmClient client(modem);
PubSubClient mqtt(client);

uint32_t lastReconnectAttempt = 0;


//tasks to be assigned to the two cores
TaskHandle_t Task1;
TaskHandle_t Task2;

//lcd display
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

const int relayPin = 16;
const int ledPin = 39;
const int ledPin1 = 23;
const int currentPin = 13;
const int ac_power = 14;

//current measurement
int mVperAmp = 185; // use 100 for 20A Module and 66 for 30A Module
double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;
const int consumption_Voltage = 240;
double power_consumed = 0;
double total_power = 0;
double kilowatt_hour_consumed = 0;
double current_units = 0;
double current_unit = 0;
double hours = 0;
double received_units = 0;
double consumption_time = 0;
int acounter = 0;
double consumption_update = 0;
char* meter_no = "143";
boolean consumption_flag = false;
double cumulative_cons = 0.000;
char packet_to_transmit[100];


//variables for comparison
int to = 0;
int from = 0;
String myString = "12.56/12:34:56";
String the_unit = "";
String the_time = "00:00:00";
String previous_time = "";
double new_units = 0; 
String units_from_comparison = "";

//EEPROM declaration
#define EEPROM_SIZE 300

//http variables
char packed_data_to_transmit[512] = {0};

#endif
