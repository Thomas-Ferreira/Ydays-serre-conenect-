#define cactus D5
#define waterSensor D0
// Le test ce fait avec celui du sol car le water sensor ne marche pas

void setup() {
  Serial.begin(9600);
  
  pinMode(cactus, OUTPUT);
  pinMode(waterSensor, INPUT);
  Serial.println("Demarrage water sensor");
}

void loop() {
  Serial.println(digitalRead(waterSensor));

  if( digitalRead(waterSensor) == LOW) {
    // Détecte de l'eau
    digitalWrite(cactus,LOW);
  }else {
    // Ne détecte pas d'eau
    digitalWrite(cactus,HIGH);
  }
  delay(1000);
}
