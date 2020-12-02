#include <dht.h>

dht DHT;

#define DHT11_PIN 2

void setup () {
  Serial.begin(115200);
  Serial.println("Démarrage Temperature & Humidity")
}

void loop {
  int chk = DHT.read11(DHT11_PIN);
    Serial.print("Temperature = ");
    Serial.println(DHT.temperature);
    Serial.print("Humidity = ");
    Serial.println(DHT.humidity);
    delay(1);

    delay(30000);
}

