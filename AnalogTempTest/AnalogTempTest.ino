#include <Servo.h>

int sensorPin=0;
Servo servo;
double recieved=0, staticTemp = 72, threshold = 1;
bool change=false;
double fahren =0;


double Thermistor(int RawADC) {
  double Temp;
  Temp = log(((10240000/RawADC) - 10000));
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
  Temp = Temp - 273.15;           
  return Temp;
}
bool checkChange(double temp){
  if(staticTemp != recieved){
    staticTemp = recieved;
    return true;
  }
  if(fahren > staticTemp && servo.read()!=180){
    return true;
  }
  else if(fahren < staticTemp && servo.read()!=0){
    return true;
  }
  return false;
}
void setup() {
   Serial.begin(9600);
   servo.attach(9);
   servo.write(0);
   delay(1000);
   servo.detach();
}

void loop() {
  if(Serial.available() >0){
    recieved = Serial.read();  
    Serial.print("RECIEVED: ");
    Serial.println(recieved);
  }
  //getting the voltage reading from the temperature sensor
 int reading = analogRead(sensorPin);  
 double temp =  Thermistor(reading);
 // print out the voltage
 /*Serial.println("Temp. : ");
 Serial.print(temp); 
 Serial.println(" Celsius");
 */fahren = temp * 9 / 5 +32;/*
 Serial.print(fahren);
 Serial.println(" Fahrenheit");*/
 change = checkChange(staticTemp);
 if(change){
    if(fahren > staticTemp){
      servo.attach(9);
      servo.write(180);
      delay(1000);
      servo.detach();
    }
    else if(fahren < staticTemp){
      servo.attach(9);
      servo.write(0);
      delay(1000);
      servo.detach();
    }
    change = false;
 }
 Serial.print("is currently: ");
 Serial.println(staticTemp);
 delay(5000); 
}
