#include "Sensors.h"
DS18B20 ds(TEMP_PIN);

Sensors::Sensors()
{
    enable();
    delay(100);
    ds.getAddress(sensor_address);

}

float Sensors::readTemp() {
    int sensors = ds.getNumberOfDevices();
    if (sensors == 0) {
        return -6;
    }

    temp = ds.getTempC();
    return temp;
}

void Sensors::enable() {
    pinMode(GROOVE_PIN, OUTPUT);
    digitalWrite(GROOVE_PIN, HIGH);
}

void Sensors::disable() {
    pinMode(GROOVE_PIN, OUTPUT);
    digitalWrite(GROOVE_PIN, LOW);
}

float Sensors::readBMEtemp() {

	bme280.setForcedMode();	
	bmeTemp = bme280.getTemperature();

	return bmeTemp;
}

float Sensors::readBMEhum() {
	
	bme280.setForcedMode();
	bmeHum = bme280.getHumidity();
	
	return bmeHum;
}

float Sensors::readBMEpre() {
	
	bme280.setForcedMode();
	bmePre = bme280.getPressure();
	
	return bmePre;
}

float Sensors::readBatteryVoltage() {
	pinMode(A5, OUTPUT);
	digitalWrite(A5, LOW);
	delay(100);
	batteryVolt = (float) analogRead(A4) / 4095  * 3.3 * 11.0;
	pinMode(A4, INPUT);
		
	return batteryVolt;
}

void Sensors::init(Stream *serial)
{
	debug = serial;
	analogReadResolution(12);
	bme280.init();
	delay(100);

}

void Sensors::warmUp() {
	int delay_ms = 3000;
	unsigned long delay_start = millis();
	debug->print(F("Response Time :"));
	debug->println(delay_ms);
	while( (millis() - delay_start) < delay_ms );
}

void Sensors::readAll() {
	enable();
	delay(100);
	//   warmUp();
	readBMEtemp();
	readBMEhum();
	readBMEpre();
	readBatteryVoltage();
	delay(200);
}
