/****************
 
branchement de la photoresistance DATA GROUND VCC

****************/
#define VIN 3.3
#define R 10000

const int sensorPin = A0; // Pin connected to sensor

int sensorVal; // Analog value from the sensor
int lux; //Lux value
bool isLight ;

void setup() {
  Serial.begin(9600);
  Serial.println("Démmarage");
}

void loop(void) {
  sensorVal = analogRead(sensorPin);
  lux=sensorRawToPhys(sensorVal);
  
  /*Serial.print("Analog value = ");
  Serial.println(sensorVal); // the analog reading
  Serial.print("= ");
  Serial.print(lux); // the analog reading
  Serial.println(" lumen"); // the analog reading*/
  
  if (isShiny(sensorVal) == true) {
    Serial.println("light on");
  } else {
    Serial.println("light off");
  }
  delay(1000);
}

int sensorRawToPhys(int raw){
  // Conversion rule
  float Vout = float(raw) * (VIN / float(1024));// Conversion analog to voltage
  float RLDR = (R * (VIN - Vout))/Vout; // Conversion voltage to resistance
  int phys=500/(RLDR/1000); // Conversion resitance to lumen
  return phys;
}

bool isShiny(int value){
  
  bool light;
  if (value < 600){
    light = false ;
  }
  else{
    light=true;
  }
  return light;

}
