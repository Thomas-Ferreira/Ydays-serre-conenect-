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
  Serial.println(F("Test DH11"));
  
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

byte readDHT11(byte pin, float* temperature, float* humidity) {
  
  /* Lit le capteur */
  byte data[BROCHE_CAPTEUR];
  byte ret = readDHTxx(pin, data, 18, 1000);
  
  /* Détecte et retourne les erreurs de communication */
  if (ret != DHT_SUCCESS) 
    return ret;
    
  /* Calcul la vraie valeur de la température et de l'humidité */
  *humidity = data[0];
  *temperature = data[2];

  /* Ok */
  return DHT_SUCCESS;
}

/**
 * Fonction bas niveau permettant de lire la température et le taux d'humidité (en valeurs brutes) mesuré par un capteur DHTxx.
 */
byte readDHTxx(byte pin, byte* data, unsigned long start_time, unsigned long timeout) {
  data[0] = data[1] = data[2] = data[3] = data[4] = 0;
  // start_time est en millisecondes
  // timeout est en microsecondes
