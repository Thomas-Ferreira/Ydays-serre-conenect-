#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
//http://10.3.141.167/
class SensorData
{
public:
    //DHT
    float Temperature;
    float Humidity;
    //humidité de sol
    int HumiditySOL;
    //lumier
    int luminosite;
    //eau
    int waterLevel;
    bool ledON;
    SensorData();
    ~SensorData();
    void toweb(WiFiClient &client, unsigned long epochTime,String fTime);
};