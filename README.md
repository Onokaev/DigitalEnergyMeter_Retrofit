# DigitalEnergyMeter_Retrofit
IoT solution for converting postpaid digital electricity meter to a smart meter for both pre-paid and post-paid applications.

meter_kplc
This is an IoT solution for replacing electromechanical energy meters with a smart meter that includes telemetry functionality. Consumption data is periodically sent to a web server.

meter_kplc_digital
This is an IoT solution that adds telemetry to the already existing digital energy meters. Digital energy meters produce a set number of pulses per kWh (typically 1600 pulses per kilowatt-hour). Each pulse is detected using an external interrupt(check attachInterrupt(pin)). Consumption data is sent to a web server periodically.

For pre-paid functionality, this IoT solution uses MQTT to send electricity tokens purchased to the specific energy meters. 

