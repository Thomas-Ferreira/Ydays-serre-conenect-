void setup() 
{
Serial.begin(9600);
}

void loop() 
{
  int temperature = digitalRead(16);

  Serial.println(temperature);
  delay(1000);
  
}
