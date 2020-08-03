#include <SimpleDHT.h>

// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2

#define ledNotif D6
int pinDHT11 = D5;
SimpleDHT11 dht11;

void setup() {
  Serial.begin(9600);
  
 pinMode(ledNotif,OUTPUT);
}

void loop() {
  digitalWrite(ledNotif, HIGH);
  // start working...
  Serial.println("=================================");
  Serial.println("Sample DHT11...");
  
  // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  
  if (dht11.read(pinDHT11, &temperature, &humidity, NULL)) {
    Serial.print("Read DHT11 failed.");
    return;
  }
  
  Serial.print("Sample OK: ");
  Serial.print(temperature); 
  Serial.print(" *C, "); 
  Serial.print(humidity); 
  Serial.println(" %");
  
  // DHT11 sampling rate is 1HZ.
  digitalWrite(ledNotif, LOW);
  delay(1000);

}
