#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// Initialize Wifi connection to the router
char ssid[] = "wifi@id";     // your network SSID (name)
char password[] = "12345678"; // your network key

// Initialize Telegram BOT
#define BOTtoken "1274678508:AAGYnE5Mbu6ua7na1uKWzZeNTHRjXTNBBy8"  // your Bot Token (Get from Botfather)
#define idChat "358127090" //idbot
#define trigger D8
#define echo D7
   
float waktu =0;
float jarak =0;
float tinggi_sensor = 15;
float tinggi_air;
 
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int Bot_mtbs = 1000; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done
bool Start = false;

int getHasil(){
  
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
  return tinggi_air;
}
void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "tesss";

    if (text == "/t") {
        bot.sendChatAction(chat_id, "typing");
        delay(2000);
        tinggi_air = getHasil();
        String pesan = "Tinggi Air Sekarang Adalah : ";
        pesan += int(tinggi_air);
        pesan += " CM";
        bot.sendMessage(chat_id, pesan, "");  
        Serial.println("kirim ketinggian air");
    }

    if (text == "/start") {
      String welcome = "Selamat Datang Di Telegram Bot Pengukur Tinggi Air, " + from_name + ".\n";
      welcome += "Chat ini di kirim dari NodeEMU ESP8266 v3. \n\n";
      welcome += "/t : untuk mengukur tinggi air\n";
      bot.sendMessage(chat_id, welcome);
      
      Serial.println("kirim pesan welcome");
    }
  }
}

void setup()
{
 Serial.begin(9600);
 pinMode(trigger,OUTPUT);
 pinMode(echo,INPUT);

   // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
 Serial.println("Sensor Ultrasonic");
 delay(2000);
 Serial.println("Pengukur Tinggi Air");
 delay(2000);
}
 
void loop()
{
   if (millis() > Bot_lasttime + Bot_mtbs)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    Bot_lasttime = millis();
  }
  
  tinggi_air = getHasil();
  
 Serial.print("\nTinggi Air :");
 Serial.print(tinggi_air);
 Serial.println("cm");
 delay(1000);
}
