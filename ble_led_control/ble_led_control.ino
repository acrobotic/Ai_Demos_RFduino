/*-----------------------------------------------------------------------
  Acrobotic - 09/10/2015
  Author: MakerBro
  Platforms: RFduino
  File: ble_led_control.ino
  ------------------------------------------------------------------------
  Description: 
  Simple program for setting the brightness of an RGB LED (PL9823-F8) over
  BLE.
  ------------------------------------------------------------------------
  Requirements:
  RFduino WS28X RGB LED Library
  https://github.com/acrobotic/Ai_RFDlib_WS2812
  ------------------------------------------------------------------------
  Please consider buying products from Acrobotic to help fund future
  Open-Source projects like this! We’ll always put our best effort in every
  project, and release all our design files and code for you to use. 
  http://acrobotic.com/
  ------------------------------------------------------------------------
  License:
  Beerware License; if you find the code useful, and we happen to cross 
  paths, you're encouraged to buy us a beer. The code is distributed hoping
  that you in fact find it useful, but  without warranty of any kind.
------------------------------------------------------------------------*/
#include <RFduinoBLE.h>
#include <Ai_RFD_WS2812.h>

#define PIN     2
#define NUM     1                           // Assuming only 1 LED
RFD_WS2812 blinker = RFD_WS2812(NUM, PIN);

void setup() {
  // Set the device name we want 
  RFduinoBLE.deviceName = "My BLE LED";

  // Set the data we want to appear in the advertisement
  // (if the deviceName and advertisementData are too long to fix into the 31 byte
  // ble advertisement packet, then the advertisementData is truncated first down to
  // a single byte, then it will truncate the deviceName)
  RFduinoBLE.advertisementData = "rgb";
  
  // start the BLE stack
  RFduinoBLE.begin();

  // For debugging purposes use the Serial object.
  Serial.begin(9600);

  // Initialize the RGB LED
  blinker.initialize();
  // As they're extremely bright, we adjust the brightness to about 40%.
  blinker.setBrightness(100); 
}

void loop() {
  // Switch to lower power mode
  RFduino_ULPDelay(INFINITE);
}

void RFduinoBLE_onConnect() {
  // Debug message printed to Serial interface
  Serial.println("RFduino connected");
}

void RFduinoBLE_onDisconnect() {
  // Debug message printed to Serial interface
  Serial.println("RFduino disconnected");
  // Ensure that all LEDs are OFF when we disconnect
  // blinker.clear();  
}

void RFduinoBLE_onReceive(char *data, int len) {
  // Debug message printed to Serial interface
  Serial.println("Data received: ");
  for(int i=0;i<len;i++)
      Serial.print(int(data[i]));
  Serial.println();
  // Each transmission should contain an RGB triple
  if (len >= 3)
  {
    // Get the RGB value, note that the ordering if GRB for 
    // the LED we tested
    uint8_t r = data[1];
    uint8_t g = data[0];
    uint8_t b = data[2];
    blinker.setPixel(0,r,g,b);
  }
  blinker.render();
}
