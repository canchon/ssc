// #include <Arduino.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "FAMILIA ARBOLEDA";
const char *password = "30900410";
#define url "http://serverall.000webhostapp.com/"

void espInit(){
	delay(50);
	WiFi.begin(ssid, password);
	Serial.print("Conectando...");
	while (WiFi.status() != WL_CONNECTED){ //Check for the connection
		delay(500);
		Serial.print(".");
	}
	Serial.print("Conectado con éxito");
}

String fetch(String module, String accion, String parameters){
	// delay(10000);
	if (WiFi.status() == WL_CONNECTED){ //Check WiFi connection status
		WiFiClient client;
		HTTPClient http;

		#define json "{\"module\":\"" + module + "\", \"accion\": \"" + accion + "\", \"parameters\": " + parameters + "}"
		#define dataToSend "json=" + String(json)
		http.begin(client, url);
		Serial.println("Datos a enviar: " + String(dataToSend));

		http.addHeader("Content-Type", "application/x-www-form-urlencoded");
		int responseCode = http.POST(dataToSend); //Enviamos el post pasándole los datos que queremos enviar. retorna un código http

		if (responseCode > 0){ //no hubo errores en hacer la petición
			Serial.println("Código HTTP ► " + String(responseCode));

			if (responseCode == 200) { //La API envió una respuesta
				Serial.println("El servidor respondió ▼ ");
				Serial.println(http.getString() + "▼");
				return http.getString();
			}
		}
		else{
			Serial.print("Error enviando POST, código: ");
			Serial.println(responseCode);
		}
		http.end(); //libero recursos
	}
	else{
		Serial.println("Error en la conexión WIFI");
	}
	return "\n\n\n\n▼fetch▼\n\n\n\n";
}


