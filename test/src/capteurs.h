#ifndef DEF_DATA_CAPTEURS
#define DEF_DATA_CAPTEURS

#include <Arduino.h>
#include "DHT.h"

using namespace std;

/* water sensor */
#define led D5
#define water D0

/****************
 
branchement de la photoresistance DATA GROUND VCC

****************/

/* test lumiere */
#define VIN 3.3
#define R 10000

/* test temperature+humidité */
DHT dht;
#define DHT11_PIN 2

class data_capteurs
{
    private:

        /* data */
            // utilisé pour le test lumière
            const int sensorPin = A0;
            int sensorVal; // Analog value from the sensor
            int lux; //Lux value
            int sensorRawToPhys(int raw);
            bool isShiny(int value);

    public:
     
        /* Constructeurs/destructeurs */
            data_capteurs();
            ~data_capteurs();

        /* water sensor */
            void test_water_sensor();

        /* lumiere */
            void test_lumiere();

        /* température + humidité */
            void test_tempHum();

};


#endif