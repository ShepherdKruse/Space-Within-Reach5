/*
   LoRaLib Transmit Example

   This example transmits LoRa packets with one second delays
   between them. Each packet contains up to 256 bytes
   of data, in the form of:
    - Arduino String
    - null-terminated char array (C-string)
    - arbitrary binary data (byte array)

   For more detailed information, see the LoRaLib Wiki
   https://github.com/jgromes/LoRaLib/wiki

   For full API reference, see the GitHub Pages
   https://jgromes.github.io/LoRaLib/
*/

// include the library
#include <LoRaLib.h>
#include <Wire.h>


// create instance of LoRa class using SX1278 module
// this pinout corresponds to KITE Shield
// https://github.com/jgromes/KiteShield
// NSS pin:   10 (4 on ESP32/ESP8266 boards)
// DIO0 pin:  2
// DIO1 pin:  3
SX1272 lora = new LoRa(10,2,3);

void setup() {
  Serial.begin(9600);
  

  // initialize SX1278 with default settings
  Serial.print(F("Initializing ... "));
  // carrier frequency:           915.0 MHz
  // bandwidth:                   125.0 kHz
  // spreading factor:            6
  // coding rate:                 5
  // sync word:                   0x14
  // output power:                17 dBm
  // current limit:               100 mA
  // preamble length:             8 symbols
  // amplifier gain:              0 (automatic gain control)
  //915.0 , 125 , 6 , 5, 0x14 , 20 
  int state = lora.begin();
  if (state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  
}
}

void loop() {
  

  Serial.print("Sending packet ... ");

  // you can transmit C-string or Arduino string up to
  // 256 characters long
  int state = lora.transmit("Hello World!");
 


  // you can also transmit byte array up to 256 bytes long
  
   // byte byteArr[] = {0x01, 0x23, 0x45, 0x56,
                //      0x78, 0xAB, 0xCD, 0xEF};
    //int state = lora.transmit(byteArr, 8);
  

  if (state == ERR_NONE) {
    // the packet was successfully transmitted
    Serial.println(" success!");

    // print measured data rate
    Serial.print("Datarate:\t");
    Serial.print(lora.getDataRate());
    Serial.println(" bps");

  } else if (state == ERR_PACKET_TOO_LONG) {
    // the supplied packet was longer than 256 bytes
    Serial.println(" too long!");

  } else if (state == ERR_TX_TIMEOUT) {
    // timeout occurred while transmitting packet
    Serial.println(" timeout!");

  }

  // wait a second before transmitting again
  delay(1000);
}
