/*For OLED connection
   GND = GND
   VCC = +5V or +3.3V
   SCL = A5 (for Arduino Uno), 21 (For Arduino Mega), A5 (For Arduino Nano), 21 (For Arduino Leonardo)
   SDA = A4 (for Arduino Uno), 20 (For Arduino Mega), A4 (For Arduino Nano), 20 (For Arduino Leonardo)
*/

/*For DHT11 Temperature Sensor
   VCC of sensor connected with 5V
   GND of sensor connected with GND
   DATA pin of sensor connected with A0 of Arduino
   
   This Programm is made by Uttam Basu
   Follow me on GitHub- https://github.com/UttamBasu
*/

#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0);

#include<dht.h>
#define dhtpin_room  A0
dht dhtroom;

int temp = 0;
int hmdt = 0;

void u8g_prepare(void)
{
  u8g.setFont(u8g_font_6x10);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
}

void intro(uint8_t a)
{
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr(2, 19, "Welcome to");
  u8g.drawStr(2, 38, "Weather Station");
  u8g.drawStr(2, 57, "of Uttam Basu");
}

void RoomTemp(uint8_t a)
{
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr(1, 10, "Room Temperature");  //1 from left side and 10 from above position.
  u8g.setPrintPos(1, 25); //1 from left side and 25 from above position.
  u8g.print(temp, 1);
  u8g.drawStr(20, 25, "C");  //20 from the left side and 25 from above position.

  u8g.drawStr(1, 40, "Room Humidity");
  u8g.setPrintPos(1, 55); //1 from the left side and 55 from above position.
  u8g.print(hmdt, 1);
  u8g.drawStr(20, 55, "%");  //20 from the left side and 55 from above position.
}

uint8_t draw_state = 2;

void draw(void)
{
  u8g_prepare();
  switch (draw_state >> 2)
  {
    case 0: intro(draw_state & 7); break;
    case 1: RoomTemp(draw_state & 7); break;
  }
}

void setup(void)
{
  Serial.begin(9600);
}
void loop(void)
{
  dhtroom.read11(dhtpin_room);
  temp = dhtroom.temperature;
  hmdt = dhtroom.humidity;  
  
  // picture loop (It is compulsory)
  u8g.firstPage();
  do
  {
    draw();
  }
  while (u8g.nextPage());

  //increase the state
  draw_state++;
  if ( draw_state >= 3*2)
    draw_state = 0;
    delay(500);
}
