/** Broche "DATA" du capteur */
const byte BROCHE_CAPTEUR = 5;

/* Code d'erreur de la fonction readDHT11() et readDHT22() */
const byte DHT_SUCCESS = 0;        // Pas d'erreur
const byte DHT_TIMEOUT_ERROR = 1;  // Temps d'attente dépassé
const byte DHT_CHECKSUM_ERROR = 2; // Données reçues erronées


/** Fonction setup() */
void setup() {
 
  /* Initialisation du port série */
  Serial.begin(115200);
  Serial.println(F("Demo DHT11 et DHT22"));
  
  /* Place la broche du capteur en entrée avec pull-up */
  pinMode(BROCHE_CAPTEUR, INPUT_PULLUP);
}

/** Fonction loop() */
void loop() {
  float temperature, humidity;
 
  /* Lecture de la température et de l'humidité, avec gestion des erreurs */
  switch (readDHT11(BROCHE_CAPTEUR, &temperature, &humidity)) {
  case DHT_SUCCESS: 
     
    /* Affichage de la température et du taux d'humidité */
    Serial.print(F("Humidite (%): "));
    Serial.println(humidity, 2);
    Serial.print(F("Temperature (^C): "));
    Serial.println(temperature, 2);
    break;
 
  case DHT_TIMEOUT_ERROR: 
    Serial.println(F("Pas de reponse !")); 
    break;
 
  case DHT_CHECKSUM_ERROR: 
    Serial.println(F("Pb de communication !")); 
    break;
  }
  
  /* Une mesure par seconde */
  delay(1000);
}
