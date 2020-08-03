
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define trigPin 2
#define echoPin 3
const int PIN_2 = 4;

LiquidCrystal_I2C lcd(0x27 ,2,16);
int jarak = 175 ;
int tinggi;
void setup() {
  pinMode (PIN_2, INPUT); //Deklareasi nama alias PIN_2 sebagai inputan
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  lcd.begin();
    lcd.setCursor(0,0);
    lcd.print("SISTEM AKTIF");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Tinggi : ");
}
void loop() {
  long duration, gape;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  gape = (duration/2) / 29.0;
  tinggi = jarak - gape;
  
  if (digitalRead(PIN_2) == HIGH) {
          lcd.setCursor(0,1);
          lcd.print(tinggi);
          Serial.println(tinggi);
          Serial.println(" input HIGH");
          lcd.print(" ");
          lcd.print("CM");
          lcd.print("   ");
          delay(200);
          
          while (digitalRead(PIN_2) == HIGH){
            delay(100);
            Serial.println(" stop HIGH");
          }
        
  } else if(digitalRead(PIN_2) == LOW){
          lcd.setCursor(0,1);
          lcd.print(tinggi);
          Serial.println(tinggi);
          Serial.println(" input LOW");
          lcd.print(" ");
          lcd.print("CM");
          lcd.print("   ");
          delay(200);
  }
}
