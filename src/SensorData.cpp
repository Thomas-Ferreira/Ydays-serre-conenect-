#include "SensorData.h"
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Arduino.h>
#include <DHT.h>

SensorData::SensorData(/* args */)
{
}

SensorData::~SensorData()
{
}
void SensorData::toweb(WiFiClient &client, unsigned long epochTime,String fTime)
{
  struct tm *ptm = gmtime((time_t *)&epochTime);
  int monthDay = ptm->tm_mday;
  int currentMonth = ptm->tm_mon + 1;
  int currentYear = ptm->tm_year + 2000;

  client.flush();
  //la partie client de web
  // Affichage
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");

  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<h1><b>serre connectée: </b></h1>");

  client.print("voila les resultats: ");

  client.println("<br><br>");
  client.print("Date: ");
  client.print(String(currentYear) + "-" + String(currentMonth) + "-" + String(monthDay));
  client.println("<br><br>");
  client.print("Heure: ");
  client.print(fTime);
  client.println("<br><br>");
  client.print("Temperature: ");
  client.print(Temperature);
  // client.println(dht.temperature);
  client.println("<br><br>");
  client.print("Humidite: ");
  client.print(Humidity);
  // client.println(dht.humidity);
  client.println("<br><br>");
  client.print("Lumiere: ");
  client.print(ledON ? "Lumiere allumee" : "Lumiere eteinte");
  client.println("<br><br>");
  client.println("Changer la luminosité: ");
  if (ledON)
  {
    client.println("<a href=\"/LED=ON\">Eteindre la lumiere</a><br>");
  }
  else
  {
    client.println("<a href=\"/LED=ON\">Allumer la lumiere</a><br>");
  }
  client.println("</html>");
  client.flush();
}
