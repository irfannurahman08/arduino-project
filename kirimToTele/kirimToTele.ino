#include "CTBot.h"
CTBot myBot;
String ssid = "XXXX";
String pass = "XXXX";
String token = "XXXX";
const int id = 1234;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting TelegramBot...");
  myBot.wifiConnect(ssid, pass);
  myBot.setTelegramToken(token);

  if (myBot.testConnection()) {
    Serial.println("Koneksi Bagus");
  } else {
    Serial.println("Koneksi Jelek");
  }

  myBot.sendMessage(id, "Tes Kelas Robot");
  Serial.println("Pesan Terkirim");
}

void loop() {

}
