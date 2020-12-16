#define cactus D5
#define waterSensor D0

void setup() {
  pinMode(cactus, OUTPUT);
  pinMode(waterSensor, INPUT);
}

void loop() {

if( digitalRead(waterSensor) == LOW) {
      digitalWrite(cactus,HIGH);
   }else {
      digitalWrite(cactus,LOW);
   }
}
