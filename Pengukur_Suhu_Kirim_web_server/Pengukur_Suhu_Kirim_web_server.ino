/*
 * HTTP Client POST Request
 * Copyright (c) 2018, circuits4you.com
 * All rights reserved.
 * https://circuits4you.com 
 * Connects to WiFi HotSpot. */

#include <SimpleDHT.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>


#define ledNotif D6 // lampu petunjuk
int pinDHT11 = D5; // data untuk sensor DHT11
SimpleDHT11 dht11;


/* Set these to your desired credentials. */
const char *ssid = "wifi@id";  //ENTER YOUR WIFI SETTINGS
const char *password = "12345678";

//Web/Server address to read/write from 
const char *host = "irfan-dev.online";   //https://circuits4you.com website or IP address of server

//=======================================================================
//                    Power on setup
//=======================================================================

void setup() {
  delay(1000);
  Serial.begin(9600);
  
  pinMode(ledNotif,OUTPUT); //set ledNotif sebagai output
  
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

//=======================================================================
//                    Main Program Loop
//=======================================================================
void loop() {
  digitalWrite(ledNotif, HIGH);
  HTTPClient http;    //Declare object of class HTTPClient
  
  String postData;
  byte suhu = 0;
  byte kelembaban = 0;
  
  
  if (dht11.read(pinDHT11, &suhu, &kelembaban, NULL)) {
    Serial.print("Read DHT11 failed.");
    return;
  }
  
  
  Serial.print((int)suhu); Serial.print(" *C, "); 
  Serial.print((int)kelembaban); Serial.println(" %");
  
  //int adcvalue=analogRead(A0);  //Read Analog value of LDR
  //suhu = String(adcvalue);   //String to interger conversion
  //kelembaban = "A";

  String suhu1 = (String)suhu;
  String kelembaban1 = (String)kelembaban;
  
  //Post Data
  postData = "suhu=" + suhu1 + "&kelembaban=" + kelembaban ;
  
  http.begin("http://irfan-dev.online/iot_suhu/post.php");              //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header

  int httpCode = http.POST(postData);   //Send the request
  String payload = http.getString();    //Get the response payload

  Serial.print(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload

  http.end();  //Close connection

  digitalWrite(ledNotif, LOW);
  delay(60000);  //Post Data at every 1 menit
}
//=======================================================================
