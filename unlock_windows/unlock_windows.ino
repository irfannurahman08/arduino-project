#include <SPI.h>
#include <RFID.h>
#include <Keyboard.h>

#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN, RST_PIN);

int serNum[5];
int card[5] = {198, 65, 184, 121, 70};//write your RFID card number here 
boolean password=LOW;
void setup()
{
  Serial.begin(9600);
  SPI.begin();
  rfid.init();

}

void loop()
{
  if (rfid.isCard())
  {
    Serial.println("card available");
    if (rfid.readCardSerial())
    {

      for (int x = 0; x < 10; x++)
      {
        for (int i = 0; i < sizeof(rfid.serNum); i++ )
        {
          Serial.println(rfid.serNum[i]); //to serial print the scanned RFID card number, note it down and change it on line 10
          if (rfid.serNum[i] == card[i])
          {
            password = HIGH;
            break;
          }
        }
      }
    }
  }
  if (password == HIGH)
  {
    
    Keyboard.press(0xB1);
    delay(300);
    Keyboard.print("  ");//write your password in between the qouts 
    Keyboard.press(0xB0);
    delay(50);
    Keyboard.releaseAll();
    delay(100);
    Keyboard.end();
    password=LOW;
  }
}
