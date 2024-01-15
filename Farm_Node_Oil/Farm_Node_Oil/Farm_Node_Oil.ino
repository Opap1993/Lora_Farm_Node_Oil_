#include "libs/EnergySave/EnergySave.h"
#include "libs/GPS/GPS.h"
#include "libs/Sensors/Sensors.h"
#include "libs/Network/Network.h"
#include "libs/LoRaWan/LoRaWan.h"

Sensors sensors = Sensors();

void setup()
{
	SerialUSB.begin(115200);
	SerialUSB.println("Setup");

	EnergySave.init(&SerialUSB);
	EnergySave.lowPowerPins(false);
	EnergySave.disableI2CDevices();
	EnergySave.setMCUSleepMode(onWakeUp);
	EnergySave.setAlarmDateTime(DEFAULT_ALARM_HOUR, DEFAULT_ALARM_MINUTE, DEFAULT_ALARM_SEC);
	//Sensors.init(&SerialUSB, &EnergySave);
	
	LoraWan.init(&SerialUSB);
	Network.init(&SerialUSB, &LoraWan);
	Network.setup(10);
	
	if (Network.connected()) {
		Network.ping();
	}
	
	//GPS.init(&SerialUSB);
	//GPS.getGpsData(DEFAULT_GPS_TIMEOUT);
}

void loop()
{
	sensorsRead();
	if (Network.connected()) {
		sendMeasurement();
		} else {
		Network.setup(10);
		if (Network.connected()) {
			sendMeasurement();
		}
	}
	EnergySave.setTime(0,0,0);
	EnergySave.standByMode();
}


void sendMeasurement() {
	
	//Sensors.readAll(ADC_SAMPLES, SENSORS_WARM_UP);
	//Network.transmitMeasurement(Sensors.getMeasurements(), GPS.getPosition());
}

void onWakeUp(){
	
}

void sensorsRead() {
	float batteryVolt;
	float dsTemp;
	float bmeTemp;
	float bmeHum;
	float bmePre;
	
	sensors.readAll();
	
	dsTemp = sensors.readTemp();
	batteryVolt = sensors.readBatteryVoltage();
	bmeTemp = sensors.readBMEtemp();
	bmeHum = sensors.readBMEhum();
	bmePre = sensors.readBMEpre();
	sensors.disable();
	delay(1000);
	

	SerialUSB.print("Temperature: ");
	SerialUSB.println (dsTemp);
	SerialUSB.print("BME Temperature: ");
	SerialUSB.println (bmeTemp);
	SerialUSB.print("BME Humidity: ");
	SerialUSB.println (bmeHum);
	SerialUSB.print("BME Pressure: ");
	SerialUSB.println (bmePre);
	SerialUSB.print("Battery volt: ");
	SerialUSB.println (batteryVolt);
}