#include <OneWire.h>
#include <LiquidCrystal_I2C.h>
#define INT_SENSOR 10
#define EXT_SENSOR 11

LiquidCrystal_I2C lcd(0x27,16,2);
OneWire is(INT_SENSOR);
OneWire es(EXT_SENSOR);

byte grad[8] = {0b01100, 0b10010, 0b10010, 0b01100, 0b00000, 0b00000, 0b00000, 0b00000};
byte data_int[9], data_ext[9], i; 
float temp_int, temp_ext;

void setup() {
  lcd.init(); lcd.backlight(); lcd.createChar(1, grad);
}

void loop() {
  is.reset(); es.reset();
  is.write(0xCC, 0); es.write(0xCC, 0);
  is.write(0x44, 0); es.write(0x44, 0);
    delay(1000);
  is.reset(); es.reset();
  is.write(0xCC, 0); es.write(0xCC, 0);
  is.write(0xBE, 0); es.write(0xBE, 0);
  is.read_bytes(data_int, 9); es.read_bytes(data_ext, 9);

  temp_int =  (float)((int)data_int[0] | (((int)data_int[1]) << 8)) * 0.0625 + 0.03125;
  temp_ext =  (float)((int)data_ext[0] | (((int)data_ext[1]) << 8)) * 0.0625 + 0.03125;


  lcd.setCursor(1,0);
    if (temp_int == 0.03125) {
      lcd.print("NO INT SENSOR");
     } else {
      lcd.print("INT: ");lcd.print(temp_int, 1);lcd.print(" ");lcd.print(char(1));lcd.print("C");lcd.print("    ");
     }

  lcd.setCursor(1,1);
    if (temp_ext == 0.03125) {
      lcd.print("NO EXT SENSOR");
     } else {
      lcd.print("EXT: ");lcd.print(temp_ext, 1);lcd.print(" ");lcd.print(char(1));lcd.print("C");lcd.print("    ");
     }
  }
bcvbcv