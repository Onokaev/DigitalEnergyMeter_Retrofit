#ifndef CalculationHEADS_H
#define calculationHEADS_H

//const byte interruptPin = 25;  //already defined in setupGPIO()
//volatile int interruptCounter = 0;
//int numberOfInterrupts = 0;
//double pulseUnit = 5;//0.000625;
//
//portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;
// 
//void IRAM_ATTR handleInterrupt() {
//  portENTER_CRITICAL_ISR(&mux);
//  interruptCounter++;
//  portEXIT_CRITICAL_ISR(&mux);
//}

//digital meter gives 1600pulses per kilowatt hour. So 1 pulse equals 0.000625kwH
//
//double getPulses()
//{
//  if(interruptCounter>0){
// 
//      portENTER_CRITICAL(&mux);
//      interruptCounter--;
//      portEXIT_CRITICAL(&mux); 
//     // numberOfInterrupts++;
//      current_units = current_units - pulseUnit; 
//
//      Serial.print("An interrupt has occurred. Total: ");
//  }
//  
//}
//
//
//double get_Units()
//{
//  getPulses();
//  return current_units;
//}

#endif
