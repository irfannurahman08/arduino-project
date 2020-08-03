
#define trigger D8
#define echo D7
   
float waktu =0;
float jarak =0;
float tinggi_sensor = 15;
float tinggi_air;
 
void setup()
{
 Serial.begin(9600);
 pinMode(trigger,OUTPUT);
 pinMode(echo,INPUT);
 Serial.println("Sensor Ultrasonic");
 delay(2000);
 Serial.println("Pengukur Tinggi Air");
 delay(2000);
}
 
void loop()
{
 digitalWrite(trigger,LOW);
 delayMicroseconds(2);
 digitalWrite(trigger,HIGH);
 delayMicroseconds(10);
 digitalWrite(trigger,LOW);
 delayMicroseconds(2);
 
 waktu = pulseIn(echo,HIGH);
 jarak = waktu * 340 / 20000;
 tinggi_air = tinggi_sensor - jarak;

 if(tinggi_air <= -1){
  tinggi_air = -1;
  }
 Serial.print("\nTinggi Air :");
 Serial.print(tinggi_air);
 Serial.println("cm");
 delay(1000);
}
