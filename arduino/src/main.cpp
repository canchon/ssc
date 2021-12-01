#include <Arduino.h>

#include <esp8266Connection.cpp> //Internet of the things
#include <dht11Connection.cpp> //Temperature and Humidity sensor

#define motorRight D0 //open, rele sentido giro
#define motorLeft D1 //close, rele fuente

int ciclo = 3000; //ciclo de trabajo del SSC
int temperatureThreshold = 20;  //°c
int humidityThreshold = 90; //%, RH

void writePins(String response); //transforma la respuesta de la API en la escritura de los pines de los motores
void openAutonomously(); //Destapa o cubre el café según las condiciones ambientales
void funcionalityInit(); //prepara los pines que van al motor
void uncoverCoffee(); //destapa el café
void coverCoffee(); //cubre el café




void setup(){
	Serial.begin(115200);
	espInit();
	dhtInit();
	funcionalityInit();
}

void loop(){
	String sensorsStatus = fetch("Ssc", "sendSensorsStatus", "{}"); /*traigo el
                                                                    estado de los sensores de la Db */
	writePins(sensorsStatus);

    openAutonomously();
	delay(ciclo);
}




//functions
void funcionalityInit(){
	pinMode(motorRight, OUTPUT);
    pinMode(motorLeft, OUTPUT);

    digitalWrite(motorLeft, HIGH);
}

void writePins(String json) {
	#define sizeSensorState 50
	String sensorState[sizeSensorState];
	bool flag1 = false;
	int j = 0; 
	for (size_t i = 0; i < json.length(); i++) {
		if (json.charAt(i) == '\"' && flag1) {
			flag1 = false;
			i++;
			j++;
		}
		if (json.charAt(i) == '\"' || flag1) {
			if (json.charAt(i) == '\"') { i++; }
			flag1 = true;
			sensorState[j] += json.charAt(i);
		}
	}
	for (size_t i = 0; i < sizeSensorState; i++) {
		if (sensorState[i] == "ciclo" && ciclo != sensorState[i+2].toInt()){
			ciclo = sensorState[i+2].toInt();
			Serial.println("\n\nCiclo de trabajo cambiado a " + String(ciclo) + " milisegundos\n");
		}

		if (sensorState[i] == "uncoverCoffee" && sensorState[i+2] == "true") {
				uncoverCoffee();
				Serial.println("\n\nDestapando el café...\n");
		}

		if (sensorState[i] == "coverCoffee" && sensorState[i+2] == "true") {
				coverCoffee();
				Serial.println("\n\nCubriendo el café...\n");
		}
		
		if (sensorState[i] == "temperatureThreshold" && temperatureThreshold != sensorState[i+2].toInt() ) {
			temperatureThreshold = sensorState[i+2].toInt();
			Serial.println("\n\nUmbral de temperatura cambiado a < " + String(temperatureThreshold) + "°c\n");
		}

		if (sensorState[i] == "humidityThreshold" && humidityThreshold != sensorState[i+2].toInt() ) {
			humidityThreshold = sensorState[i+2].toInt();
			Serial.println("\n\nUmbral de humedad relativa cambiado a > " + String(humidityThreshold) + "%\n");
		}
	}
}

void openAutonomously(){
	#define humidity getHumidity()
	#define temperature getTemperature()
	( (temperature < temperatureThreshold || humidity > humidityThreshold) && (humidity != 0 && temperature != 0) ) ? uncoverCoffee() : coverCoffee();

	Serial.print("sendToDb ->");
	#define response fetch("Ssc", "addTemperatureHumidity", "{\"humidity\": \"" + String(humidity) + "\", \"temperature\": \"" + String(temperature) + "\"}")
	Serial.println("\n\n" + String(response) + "▼\n");
}

void uncoverCoffee(){
	Serial.println("\nDestapando el café.");
	//giro encontra de los componentes
	digitalWrite(motorRight, LOW);
	delay(100); //tiempo prudente para que la bobina reaccione
	digitalWrite(motorLeft, LOW);
	delay(2000); //Espera a que el motor habra por completo el café
	digitalWrite(motorRight, HIGH);
	digitalWrite(motorLeft, HIGH);
}

void coverCoffee(){
	Serial.println("\nCubriendo el café.");
	//giro hacia los componentes
	digitalWrite(motorLeft, LOW);
	delay(2000); //Espera a que el motor cierre por completo el café	
	digitalWrite(motorLeft, HIGH);
}