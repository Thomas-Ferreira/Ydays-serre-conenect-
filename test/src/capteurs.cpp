#include "capteurs.h"

using namespace std;

data_capteurs::data_capteurs()
{
    sensorVal = 0;
    lux = 0;
}

void data_capteurs::test_water_sensor()
{

    if( digitalRead(water) == LOW) 
    {
        digitalWrite(led,HIGH);
    }
    else 
    {
        digitalWrite(led,LOW);
    }
}

void data_capteurs::test_lumiere()
{
    sensorVal = analogRead(sensorPin);
    lux=sensorRawToPhys(sensorVal);

    if (isShiny(sensorVal) == true) 
    {
        Serial.println("light on");
    } 
    else 
    {
        Serial.println("light off");
    }
  delay(1000);
}

void data_capteurs::test_tempHum()
{
    Serial.print("Temperature = ");
    Serial.println(dht.readTemperature());
    Serial.print("Humidity = ");
    Serial.println(dht.readHumidity());
    delay(10000);
}

int data_capteurs::sensorRawToPhys(int raw)
{
    // Conversion rule
    float Vout = float(raw) * (VIN / float(1024));// Conversion analog to voltage
    float RLDR = (R * (VIN - Vout))/Vout; // Conversion voltage to resistance
    int phys=500/(RLDR/1000); // Conversion resitance to lumen
    return phys;

}

bool data_capteurs::isShiny(int value)
{
    bool light;
    if (value < 600)
    {
        light = false ;
    }
    else
    {
        light=true;
    }
    return light;
}
