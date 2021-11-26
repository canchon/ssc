// #include <Arduino.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "FAMILIA ARBOLEDA";
const char *password = "30900410";
#define url "http://serverall.000webhostapp.com/"

void espInit()
{
	delay(10);
	WiFi.begin(ssid, password);

	Serial.print("Conectando...");
	while (WiFi.status() != WL_CONNECTED)
	{ //Check for the connection
		delay(500);
		Serial.print(".");
	}

	Serial.print("Conectado con éxito, mi IP es: ");
	Serial.println(WiFi.localIP());
}

String fetch(String module, String accion, String parameters)
{
	if (WiFi.status() == WL_CONNECTED)
	{ //Check WiFi connection status

		WiFiClient client;
		HTTPClient http;

		#define json "{\"module\":\"" + module + "\", \"accion\": \"" + accion + "\", \"parameters\": \"" + parameters + "\"}"
		#define dataToSend "json=" + String(json)
		http.begin(client, url); //Indicamos el destino
		Serial.println(dataToSend);

		http.addHeader("Content-Type", "application/x-www-form-urlencoded");
		int responseCode = http.POST(dataToSend); //Enviamos el post pasándole, los datos que queremos enviar. (esta función nos devuelve un código que guardamos en un int)

		if (responseCode > 0)
		{
			Serial.println("Código HTTP ► " + String(responseCode)); //Print return code
			Serial.println(http.getString());

			if (responseCode == 200)
			{
				Serial.println("El servidor respondió ▼ ");
				Serial.println(http.getString());
				return http.getString();
			}
		}
		else
		{
			Serial.print("Error enviando POST, código: ");
			Serial.println(responseCode);
			//  return "Error enviando POST, código: " + String(responseCode);
		}

		http.end(); //libero recursos
	}
	else
	{
		Serial.println("Error en la conexión WIFI");
		// return "Error en la conexión WIFI";
	}
	return "";
}