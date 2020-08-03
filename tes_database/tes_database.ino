#include <ESP8266WiFi.h>


const char* ssid     = "wifi@id"; //nama wifi
const char* password = "12345678"; //password
const char* host = "192.168.43.124"; //IP PC
 
#define trigger D8
#define echo D7
#define ledNotif D6
   
float waktu =0;
float jarak =0;
float tinggi_sensor = 15;
float tinggi_air;
int sensorValue = 0;
 
 
void setup() {

 Serial.begin(9600);
 pinMode(trigger,OUTPUT);
 pinMode(echo,INPUT);
 pinMode(ledNotif,OUTPUT);
 Serial.println("Sensor Ultrasonic");
 delay(2000);
 Serial.println("Pengukur Tinggi Air");
 delay(2000);
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
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
  
 
  Serial.print("connecting to ");
  Serial.println(host);
 
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    
      digitalWrite(ledNotif, LOW);
      delay(500);
      digitalWrite(ledNotif, HIGH);
      delay(500);
      digitalWrite(ledNotif, LOW);
      delay(500);
      digitalWrite(ledNotif, HIGH);
    return;

  }
 
  // We now create a URI for the request
  String url = "/t/add.php?";
  url += "tinggi_air=";
  url += tinggi_air;
 
  Serial.print("Requesting URL: ");
  Serial.println(url);
 
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
 
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
 
  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    //Serial.print(line);
 
    if (line.indexOf("sukses gaes") != -1) {
      Serial.println();
      digitalWrite(ledNotif, LOW);
      delay(100);
      digitalWrite(ledNotif, HIGH);
      delay(100);
      digitalWrite(ledNotif, LOW);
      delay(100);
      digitalWrite(ledNotif, HIGH);
      Serial.println("Yes, data masuk");
    } else if (line.indexOf("gagal gaes") != -1) {
      Serial.println();
      digitalWrite(ledNotif, LOW);
      delay(500);
      digitalWrite(ledNotif, HIGH);
      delay(500);
      digitalWrite(ledNotif, LOW);
      delay(500);
      digitalWrite(ledNotif, HIGH);
      Serial.println("Maaf, data gagal masuk");
      //digitalWrite(alarmPin, HIGH);
    }
  }
 
  Serial.println();
  Serial.println("closing connection");
  delay(5000);
}
