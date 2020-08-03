#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include "DHT.h"
#define DHTPIN D6
char ssid[] = "wifi@id"; //nama wifi
char password[] = "12345678"; //password wifi
#define BOTtoken "907580866:AAGulSeQkxWxsCew-6zQQbIihTFoBu91o" //token bot telegram
#define idChat "672053529" //idbot
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
int Bot_mtbs = 1000;
long Bot_lasttime;
bool Start = false;
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(9600);
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  dht.begin();
  delay(5000);
}
void loop() {
  delay(2000);
  float t = dht.readTemperature();
  Serial.print("Suhu saat ini : ");
  Serial.print(t);
  Serial.println(" *C");
  if (t > 37.00) {
    bot.sendChatAction(idChat, "Sedang mengetik...");
    Serial.print("Suhu saat ini : ");
    Serial.println(t);
    delay(3000);
    String suhu = "Intensitas suhu : ";
    suhu += int(t);
    suhu += " *C\n";
    suhu += "Suhu maksimal\n";
    bot.sendMessage(idChat, suhu, "");
    Serial.print("Mengirim data sensor ke telegram");
  }
  if (millis() > Bot_lasttime + Bot_mtbs) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages) {
      Serial.println("Memeriksa Respon");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    Bot_lasttime = millis();
  }
}
void handleNewMessages(int numNewMessages) {
  Serial.println("Pesan baru...");
  Serial.println(String(numNewMessages));
  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;
    if (text == "/cekSuhu") {
      delay(2000);
      float t = dht.readTemperature();
      String suhu = "Suhu sekarang : ";
      suhu += int(t);
      suhu += " *C";
      bot.sendMessage(idChat, suhu, "");
    }
    else if (text == "/cekHum") {
      delay(2000);
      float h = dht.readHumidity();
      String hum = "Hum sekarang : ";
      hum += int(h);
      hum += " %";
      bot.sendMessage(idChat, hum, "");
    }
    else if (text == "/start") {
      String welcome = "Perintah : \n";
      welcome += "/cekSuhu\n";
      welcome += "/cekHum";
      bot.sendMessage(chat_id, welcome);
    }
  }
}
