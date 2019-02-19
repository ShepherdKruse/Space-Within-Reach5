#include <Wire.h>
#include <Adafruit_BMP085.h>
 
// Connect VCC of the BMP180 sensor to 3.3V
// Connect GND to Ground
// Connect SCL to i2c clock  thats A5
// Connect SDA to i2c data  thats A4
 
Adafruit_BMP085 bmp;
 
void setup() 
{
  Serial.begin(9600);
  if (!bmp.begin()) 
  {
  Serial.println("BMP180 sensor not found");
  while (1) {}
  }
}
 
void loop() {
    Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");
 
    Serial.print("Altitude = ");
    Serial.print(bmp.readAltitude(101325));
    Serial.println(" meters");
 
    Serial.println();
    delay(1000);
}
