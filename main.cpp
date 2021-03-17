#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Arduino.h>
#include <DHT.h>
#include <data.h>

// Définir par son réseau de labo IOT
const char *ssid = "raspi-webgui";
const char *password = "laboiot20-21";

// Le port serveur
WiFiServer server(80);

// Définir le NTP client pour le temps
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

//NTPClient timeClient(ntpUDP, "europe.pool.ntp.org");//, 3600, 60000);
String cDate;
String fTime;

// Définir le DHT22 pour l'humidité et la temperature
//dht DHT;
#define DHT11_PIN D1
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22 // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHT11_PIN, DHTTYPE);

// PIN du PCS humidité et temperature
String messageDHT11;

// PIN du capteur humidité du sol
#define pinAnalogKT A0
#define pinDigitalKT D0
int valAnalogKT;
int mapAnalogKT;
int valDigitalKT;
String messageKT;

// PIN du capteur lumière
#define VIN 3.3
#define R 10000
#define pinDigitallum D2
int valueLum;      // Valeur de pin de la lumier
String etatLum;    //etat de la lumier
String messageLum; //message a avoir

// PIN du capteur  niveau d'eau
#define pinDigitalWater D5
int waterLevel;

data d;

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
    Serial.print(".?");
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

  //Initialisation de capteur de sol
  Serial.println("Initialisation KT");
  pinMode(pinAnalogKT, INPUT);
  pinMode(pinDigitalKT, INPUT);

  //initialisation de la lumier
  Serial.println("Initialisation lumi");
  pinMode(pinDigitallum, INPUT);

  //initialisation de capteur de niveau d'eau
  Serial.println("Initialisation niveau d'eau:");
  pinMode(pinDigitalWater, INPUT);
}

void loop()
{
  WiFiClient client = server.available();
  // Ne rien avoir c'est si pas le bon client
  if (!client)
  {
    return;
  }
  // Attendre le client
  while (!client.available())
  {
    timeClient.update();

    unsigned long epochTime = timeClient.getEpochTime();
    fTime = timeClient.getFormattedTime();

    //Get a time structure
    struct tm *ptm = gmtime((time_t *)&epochTime);
    int monthDay = ptm->tm_mday;
    int currentMonth = ptm->tm_mon + 1;
    int currentYear = ptm->tm_year + 2000;

    //la date  complete:
    cDate = String(currentYear) + "-" + String(currentMonth) + "-" + String(monthDay);

    // Données DHT11
    // int chk = dht.read(DHT11_PIN);

    // // Empêche les valeurs d'être à 0
    // while (dht.temperature == 0 or dht.humidity == 0) {
    //   int chk = dht.read(DHT11_PIN);
    // }

    // Données KY71
    valAnalogKT = analogRead(pinAnalogKT);
    valDigitalKT = digitalRead(pinDigitalKT);
    // La valeur analog peut permettre d'être précis sur le taux d'humidité
    // Si la valeur digital est set à 0 alors le sol est suffisamment humide
    mapAnalogKT = map(valAnalogKT, 0, 1023, 0, 100);
    if (valDigitalKT == 0)
    {
      messageKT = "Plante hydratee ";
    }
    else
    {
      messageKT = "Plante en manque d'eau ";
    }
    Serial.println(messageKT);

    if (mapAnalogKT < 45)
    {
      Serial.println("Allumer la pompe");
      delay(1000);
      Serial.println("Etendre la pompe ");
    }

    // Données lumi
    valueLum = digitalRead(pinDigitallum);
    if (valueLum == 0)
    {
      etatLum = "Lumiere allumee";
      messageLum = "Eteindre la lumiere";
    }
    else
    {
      etatLum = "Lumiere eteinte";
      messageLum = "Allumer la lumiere";
    }

    // Données eau
    waterLevel = digitalRead(pinDigitalWater);
    Serial.println(waterLevel);
    if (waterLevel == 0)
    {
      Serial.println("Le bac n'a plus d'eau");
    }
    else
    {
      Serial.println("Le bac contient de l'eau");
    }

    // Met à jour l'heure toutes les 10 secondes | update time every 10 secondes
    timeClient.update();
    Serial.println(timeClient.getFormattedTime());
    delay(10 * 1000); // Attendre 10s | wait 10 secondes

    // Nouveau client avec requête
    String request = client.readStringUntil('\r');
    Serial.println(request);
    //client.flush();

    // Affichage
    //data.cpp

    Serial.println("--");
  }
}