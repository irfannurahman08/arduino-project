
#define trigger D8
#define echo D7
   
float waktu =0;
float distance=0;
 
void setup()
{
 Serial.begin(9600);
 pinMode(trigger,OUTPUT);
 pinMode(echo,INPUT);
 Serial.println("Sensor Ultrasonic");
 delay(2000);
 Serial.println("Pengukur Jarak");
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
 distance=waktu*340/20000;
 Serial.print("\nJarak :");
 Serial.print(distance);
 Serial.println("cm");
 delay(1000);
}
