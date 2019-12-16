#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SD.h>

#define LcdID = 0x3F
#define TextFileLocation "text.txt"

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x3F, 20, 4);
File textFile;
String displayText[4] = {"", "", "", ""};

String readLine(File file) {
  String received = "";
  char ch;
  while (file.available())
  {
    ch = file.read();
    Serial.print(ch);
    if (ch == '\n')
    {
      return String(received);
    }
    else
    {
      received += ch;
    }
  }
  return "";
}

void displayUpdate(String text[]) {
  lcd.clear();
  for(int i = 0; i < 4; i++) {
    lcd.setCursor(0, i);
    lcd.print(text[i]);
    Serial.println(i);
  }
}

void arrayShiftLeft(String t[], String v) {
  int l = 4;
  v.remove(20);
  
  for(int i = 0; i < l; i++) {
    t[i] = t[i+1];
  }
  
  t[l-1] = v;
}

void setup() {
  lcd.begin();
  lcd.backlight();

  SD.begin(9);
  textFile = SD.open(TextFileLocation, FILE_READ);
  
  Serial.begin(9600);
  
  Serial.println("Powered on");
}

void loop() {
  displayUpdate(displayText);

  arrayShiftLeft(displayText, readLine(textFile));
  
  delay(2000);

}
