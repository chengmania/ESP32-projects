/* DHT11 Sensor Porject with OLED Screen Display
/  By Chengmania 
/  on cold snow filled Sunday 1/21/2024
*/

//Display Includes And Definitions
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);

//DHT11 Include
#include <DHT.h>
#define DHTPIN 4 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //or 0x3C
  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setTextWrap(false);

  dht.begin();

}

void loop() {
  readandDisplayDHT();
}

void readandDisplayDHT(){

  float humidity  = dht.readHumidity();        // read humidity
  float temp      = dht.readTemperature();     // read Temp
  float tempF     = dht.readTemperature(true); // read temp in Fahrenheit

  //error checking
  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temp) || isnan(tempF)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  
  //clear display set position and print 
  display.clearDisplay();
  display.setCursor(1,1);

  display.print("Tem:"); display.print(tempF,1); display.println(" F");
  display.print("Hum:" ); display.print(humidity,1); display.println(" %");
  display.display();  //needed to print to display 
  
  return;
  
}