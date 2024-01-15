
#ifndef Sensors_H
#define Sensors_H

#define ONEWIRE_SEARCH 0
#define TEMP_PIN  A2
#define GROOVE_PIN 38
#include "Arduino.h"
#include "../DS18B20/src/DS18B20.h"
#include "../BME280/BME280.h"
#include "../../Parameters.h"


class Sensors
{
protected:
	Stream *debug;
	BME280 bme280;
	
public:
    Sensors();
    void enable();
    void disable();
    void init(Stream *serial);
    float readTemp();
	float readBMEtemp();
	float readBMEhum();
	float readBMEpre();
	float readBatteryVoltage(void);
	void readAll();
	void warmUp();

	
private:
    uint8_t sensor_address[8];
    float temp;
	float batteryVolt;
	float bmeTemp;
	float bmeHum;
	float bmePre;
};

#endif