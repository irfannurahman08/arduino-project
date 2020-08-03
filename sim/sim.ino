

#include <Sim800l.h>
#include "sms.h"
#include "SoftwareSerial.h"
#include <TinyGPS++.h>
#include <PString.h>
int led=3;
TinyGPSPlus gps;
char buffer[160];
char smsbuffer[160];
char n[20];
unsigned long last = 0UL;
SMSGSM sms;
String kirim="";
PString str(buffer, sizeof(buffer));
void setup(){
  pinMode(led,OUTPUT);
  Serial.begin(9600);
  if (gsm.begin(9600)){
    
    sms.SendSMS("nomor hape kamu", "GPS TRACKER ONLINE");
    delsms();
   digitalWrite(led,HIGH);
  delay(1000); 
  digitalWrite(led,LOW);
  delay(1000);
  digitalWrite(led,HIGH);
  delay(1000); 
  digitalWrite(led,LOW);
  delay(1000);
  digitalWrite(led,HIGH);
  delay(1000); 
  digitalWrite(led,LOW);
  delay(1000);
  }
  
  
}

void loop(){
  
 
    kirim="";
    
  while (Serial.available() > 0)
   if( gps.encode(Serial.read()))
   info();
  
}
void(* resetFunc) (void) = 0;

void delsms()
{
  for (int i=0; i<10; i++)
  {  
      int pos=sms.IsSMSPresent(SMS_ALL);
      if (pos!=0)
      {
        if (sms.DeleteSMS(pos)==1){}else{}
      }
  }
}

void info(){
  str.begin();
    str.print("https://maps.google.com/maps?q=");
    str.print(gps.location.lat(), 6);
    str.print(F(","));
    str.print(gps.location.lng(), 6);
    kirim=str;
 
    
  int pos=0;
  pos=sms.IsSMSPresent(SMS_ALL);
  if(pos){
    sms.GetSMS(pos,n,smsbuffer,100);
    if(!strcmp(smsbuffer,"track")){
         digitalWrite(led,HIGH);
 
 
      str.begin();
      str.print(kirim);
      sms.SendSMS(n,buffer);
       digitalWrite(led,LOW); 
    }
    if(!strcmp(smsbuffer,"reset")){
      
      sms.SendSMS(n,"GPS TRACKER RESET");
      delay(5000);
      resetFunc(); 
    }
    delsms();
  }
  
  
}
