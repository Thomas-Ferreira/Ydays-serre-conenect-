#define LEDAlert D5
#define LEDFull D6
#define waterSensor D0
// Le test se fait avec le capteur du sol car le water sensor ne marche pas

void setup() {
  Serial.begin(9600);

  pinMode(LEDAlert, OUTPUT);
  pinMode(LEDFull, OUTPUT);
  pinMode(waterSensor, INPUT);
  Serial.println("Demarrage water sensor");
}

void loop() {
  // Détecte de l'eau
  if ( digitalRead(waterSensor) == LOW) {
    digitalWrite(LEDAlert, LOW);
    Serial.println("Le réservoir contien de l'eau");
    digitalWrite(LEDFull, HIGH);
    delay(1000);
  } else {
    // Ne détecte pas d'eau
    digitalWrite(LEDFull, LOW);
    Serial.println("Le réservoir n'a plus d'eau");
    digitalWrite(LEDAlert, HIGH);
    delay(1000);
    digitalWrite(LEDAlert, LOW);
    delay(1000);
  }
}
