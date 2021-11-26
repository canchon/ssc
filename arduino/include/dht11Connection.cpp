#include "DHT.h"

#define DHTPIN 2  
#define DHTTYPE DHT11   

DHT dht(DHTPIN, DHTTYPE);
#define led 0

void dhtInit() {
  Serial.println(F("DHTxx test!"));
  pinMode(led, OUTPUT);
  dht.begin();
}

String getTemperatureAndHumidity() {
  #define h dht.readHumidity() //read humidity
  #define t dht.readTemperature()

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) ) {
    return F("Failed to read from DHT sensor!");
  }

  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(F("  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));

  Serial.println("leds funcionando:");
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(500);
  // return "{humidity: " +  + "temperature: " + String(t) + "}";
  return "{" + String(h) + "," + String(t) + "}"; //primero la humedad, luego la temperatura.
}