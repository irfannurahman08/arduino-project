#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

 
#define trigger D8
#define echo D7
#define ledNotif D6 // lampu petunjuk

const char *ssid = "wifi@id";  //ENTER YOUR WIFI SETTINGS
const char *password = "12345678";

//Web/Server address to read/write from 
const char *host = "irfan-dev.online";   //https://circuits4you.com website or IP address of server

float waktu =0;
float jarak =0;
float tinggi_sensor = 15;
float tinggi_air;
int sensorValue = 0;
String postData;
 
void setup() {
  delay(1000);
 Serial.begin(9600);
 pinMode(trigger,OUTPUT);
 pinMode(echo,INPUT);
 pinMode(ledNotif,OUTPUT);
 Serial.println("Sensor Ultrasonic");
 delay(2000);
 Serial.println("Pengukur Tinggi Air");
 delay(2000);


  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(ledNotif, HIGH);
    delay(500);
    digitalWrite(ledNotif, LOW);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}
 
void loop() {
 digitalWrite(ledNotif, HIGH);
  
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

 Serial.print(tinggi_air); Serial.print(" CM"); 
    Serial.println();
    
  HTTPClient http;    //Declare object of class HTTPClient

  String tinggiSungai = (String)tinggi_air;
  //Post Data
  postData = "tinggiSungai=" + tinggiSungai ;
  
  http.begin("http://irfan-dev.online/tinggisungai/post.php");              //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header

  int httpCode = http.POST(postData);   //Send the request
  String payload = http.getString();    //Get the response payload

  Serial.print(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload

  http.end();  //Close connection

  digitalWrite(ledNotif, LOW);
  delay(5000);  //Post Data at every 5
}
