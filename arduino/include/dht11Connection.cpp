#include "DHT.h"

#define DHTPIN D2  
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);

void dhtInit(){
  dht.begin();
  Serial.println("\nSensor dht11 (temperatura y humedad) Listo para usar.");
}

float getTemperature(){
  #define temperature dht.readTemperature()
  if (isnan(temperature)) {
    Serial.println(F("\nNo se pudo leer la temperatura"));
    return 0.0;
  }else{
    Serial.println("\ntemperatura: " + String(temperature) + "°c");
    return temperature;
  }
}

float getHumidity(){
  #define humidity dht.readHumidity()
  if (isnan(humidity)) {
    Serial.println(F("\nNo se pudo leer la humedad"));
    return 0.0;
  }else{
    Serial.println("\nHumedad relativa: " + String(humidity) + "%");
    return humidity;
  }
}