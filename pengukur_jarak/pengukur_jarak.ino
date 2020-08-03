#define trigger 12
#define echo 11
   
float time=0,distance=0;
 
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
 time=pulseIn(echo,HIGH);
 distance=time*340/20000;
 Serial.print("\nJarak :");
 Serial.print(distance);
 Serial.println("cm");
 delay(1000);
}
