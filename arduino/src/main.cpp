#include <Arduino.h>

#include <esp8266Connection.cpp> //Internet of the things
#include <dht11Connection.cpp>

void readSerial()
{
	if (Serial.available() != 0)
	{
		// url = String(Serial.readString());
		// dataToSend = String(Serial.readString());
	}
}

void setup()
{
	Serial.begin(115200);
	// espInit();
	dhtInit();
}
void loop()
{
	// String sensorsStatus = fetch("Ssc", "sendSensorsStatus", "{id: 1, state: LOW}"); //traigo el
	// 																				//estado de los sensores de la BD
	// Serial.println('g' + sensorsStatus);
	String array = getTemperatureAndHumidity();
	Serial.println(array);
	delay(1500);
}

// {
// 	#define motor1 0
// 	pinmode(motor1, OUTPUT);

// }