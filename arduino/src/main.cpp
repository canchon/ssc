#include <Arduino.h>

#include <esp8266Connection.cpp> //Internet of the things
#include <dht11Connection.cpp> //Temperature and Humidity sensor

#define motorRight D0 //open
#define motorLeft D1 //close

void writePins();
void sendTemperatureHumidityToDb();
void openAutonomously();
void funcionalityInit();

void setup(){
	Serial.begin(115200);
	espInit();
	dhtInit();
	funcionalityInit();
}

void loop(){
	String sensorsStatus = fetch("Ssc", "sendSensorsStatus", "{}"); //traigo el
	// 					
	writePins(sensorsStatus);
																//estado de los sensores de la BD

    openAutonomously();
	delay(5000);
}

//functions
void funcionalityInit(){
	pinMode(motorRight, OUTPUT);
    pinMode(motorLeft, OUTPUT);

    digitalWrite(motorRight, HIGH);
}

void writePins(String array){
	#define sizeSensorState 5
	String sensorState[sizeSensorState];
	bool flag1 = false;
	int j = 0; 
	for (size_t i = 0; i < array.length(); i++){
		if (array.charAt(i) == '\"' && flag1){
			flag1 = false;
			i++;
			j++;
		}
		if(array.charAt(i) == '\"' || flag1){
			flag1 = true;
			sensorState[j] += array.charAt(i+1);
		}
	}
	for (size_t i = 0; i < sizeSensorState; i++){
		String mode = "";
		if(sensorState[i] == "motorRight"){
			if(sensorState[i+1] == "HIGH"){ 
				digitalWrite(motorRight, HIGH); 
    		}
			if(sensorState[i+1] == "LOW"){
				digitalWrite(motorRight, LOW);
			}
		}
	}
}

void sendTemperatureHumidityToDb(float t, float h){
	Serial.print("sendToDb ->");
	String response = fetch("Ssc", "addTemperatureHumidity", "{\"humidity\": \"" + String(h) + "\", \"temperature\": \"" + String(t) + "\"}");
	Serial.print("\n\n\n\n\n\n\n▼\n\n\n\n\n\n\n");
}

void openAutonomously(){
	#define humidity getHumidity()
	#define temperature getTemperature()

	sendTemperatureHumidityToDb(temperature, humidity);
	if(temperature < 20 || humidity > 90){
		digitalWrite(motorRight, HIGH);
		delay(2000); //Espera a que el motor cierre por completo el café	
		digitalWrite(motorRight, LOW); //apaga el motor
	}
}