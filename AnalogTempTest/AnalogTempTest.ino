int sensorPin=0;

double Thermistor(int RawADC) {
double Temp;
Temp = log(((10240000/RawADC) - 10000));
Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
Temp = Temp - 273.15;           
 return Temp;
}
void setup() {
   Serial.begin(9600);
}

void loop() {
  //getting the voltage reading from the temperature sensor
 int reading = analogRead(sensorPin);  
 double temp =  Thermistor(reading);
 // print out the voltage
 Serial.println("Temp. : ");
 Serial.print(temp); 
 Serial.println(" Celsius");
 double fahren = temp * 9 / 5 +32;
 Serial.print(fahren);
 Serial.println(" Fahrenheit");
 delay(1000); 
}
