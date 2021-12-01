// #include <Arduino.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "FAMILIA ARBOLEDA";
const char *password = "30900410";

#define url "http://serverall.000webhostapp.com/"
WiFiClient client;
HTTPClient http;
String json = "";
String dataToSend = "";

void espInit(){
	//connect to red wifi
	delay(50);
	WiFi.begin(ssid, password);
	Serial.print("Conectando...");
	while (WiFi.status() != WL_CONNECTED){ //Check for the connection
		delay(500);
		Serial.print(".");
	}
	Serial.print("Conectado con éxito a la red wifi " + *ssid);

	//connect to API
	http.begin(client, url);
}

String fetch(String module, String accion, String parameters){
	delay(4000);
	if (WiFi.status() == WL_CONNECTED){ //Check WiFi connection status
		json = "{\"module\":\"" + module + "\", \"accion\": \"" + accion + "\", \"parameters\": " + parameters + "}";
		dataToSend = "json=" + String(json);
		Serial.println("\nDatos a enviar: " + String(dataToSend));
		http.addHeader("Content-Type", "application/x-www-form-urlencoded");
		int responseCode = http.POST(dataToSend); //Enviamos el post pasándole los datos que queremos enviar. retorna un código http

		if (responseCode > 0){ //no hubo errores al hacer la petición
			Serial.println("Código HTTP ► " + String(responseCode));
			if (responseCode == 200) { //La API envió una respuesta
				Serial.println("El servidor respondió ▼ ");
				String response = http.getString();
				Serial.println( response + "▼");
				http.end();
				Serial.println("------------------");
				return response;
			}
		}
		else{
			Serial.print("Error enviando POST, código: ");
			Serial.println(responseCode);
		}
	}
	else{
		Serial.println("\nError en la conexión WIFI");
	}
	return "";
}


