#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <DHT.h>
#include <SensorData.h>

// Définir par son réseau de labo IOT
#define ssid "raspi-webgui"
#define password "laboiot20-21"

// Définir le DHT22 pour l'humidité et la temperature
#define DHT11_PIN D1
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22 // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
// capteur humidité du sol
#define pinAnaloghumiditesol A0
#define pinDigitalhumiditesol D0
//capteur de lumiere
#define pinDigitallumiere D2
// PIN du capteur  niveau d'eau
#define pinDigitalWater D5

// Le port serveur
WiFiServer server(80);

// Définir le NTP client pour le temps
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

DHT dht(DHT11_PIN, DHTTYPE);
SensorData d;
int count = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println();
  // Connection au Wi-Fi
  Serial.print("Connexion au wifi :");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    //Serial.print("");
  }
  // Adresse IP sur le wifi
  Serial.print("Connecté, adresse IP:");
  Serial.println(WiFi.localIP());

  // Démarrage du serveur
  server.begin();

  // démarrage du client NTP
  timeClient.begin();
  timeClient.setTimeOffset(3600);

  //Initialisation de DHT11
  Serial.println("Initialisation DHT11");
  dht.begin();

  //Initialisation de capteur de humidité de sol
  Serial.println("Initialisation le capteur de humidité de sol");
  pinMode(pinAnaloghumiditesol, INPUT);
  pinMode(pinDigitalhumiditesol, INPUT);

  //initialisation de la lumière
  Serial.println("Initialisation de lumière");
  pinMode(pinDigitallumiere, INPUT);

  //initialisation de capteur de niveau d'eau
  Serial.println("Initialisation niveau d'eau:");
  pinMode(pinDigitalWater, INPUT);
}

void loop()
{
  if (count == 10)
  {
    //DHT
    d.Temperature = dht.readTemperature();
    d.Humidity = dht.readHumidity();
    count = 0;
  }
  count++;
  // Données lumiere
  d.luminosite = digitalRead(pinDigitallumiere);
  // Données eau
  int waterLevel = digitalRead(pinDigitalWater);
  d.waterLevel = waterLevel;
  d.HumiditySOL = digitalRead(pinDigitalhumiditesol);
  // led
  d.ledON = digitalRead(pinDigitallumiere);
  //
  WiFiClient client = server.available();
  // si le bon client
  if (client)
  {
    // Attendre le client
    while (!client.available())
    {
      // Met à jour l'heure toutes les 10 secondes | update time every 10 secondes
      timeClient.update();
      unsigned long epochTime = timeClient.getEpochTime();
      String ftime = timeClient.getFormattedTime();
      Serial.println(ftime);
      // Nouveau client avec requête
      String request = client.readStringUntil('\r');
      Serial.println(request);
      d.toweb(client, epochTime, ftime);
      Serial.println("--");
    }
  }
}