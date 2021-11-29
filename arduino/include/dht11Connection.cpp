#include "DHT.h"

#define DHTPIN D2  
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);

void dhtInit() {
  dht.begin();
  Serial.println("Sensor dht11 (temperatura y humedad) Listo para usar.");
}

float getTemperature(){
  #define temperature dht.readTemperature()
  if (isnan(temperature)) {
    Serial.print(F("Failed to read from DHT sensor!"));
    return 0.0;
  }else{
    return temperature;
  }
}

float getHumidity(){
  #define humidity dht.readHumidity()
  if (isnan(humidity)) {
    Serial.print(F("Failed to read from DHT sensor!"));
    return 0.0;
  }else{
    return humidity;
  }
}