/*-----------------------------------------------------------------------
  Acrobotic - 09/10/2015
  Author: MakerBro
  Platforms: RFduino
  File: receiving_messages.ino
  ------------------------------------------------------------------------
  Description: 
  Simple program for printing to the Serial interface messages when data 
  are received over BLE.
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
void setup() {
  // Set the device name we want 
  RFduinoBLE.deviceName("My LED Controller");

  // Set the data we want to appear in the advertisement
  // (if the deviceName and advertisementData are too long to fix into the 31 byte
  // ble advertisement packet, then the advertisementData is truncated first down to
  // a single byte, then it will truncate the deviceName)
  RFduinoBLE.advertisementData = "rgb";
  
  // start the BLE stack
  RFduinoBLE.begin();

  // For debugging purposes use the Serial object.
  Serial.begin(9600);
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
}

void RFduinoBLE_onReceive(char *data, int len) {
  // Debug message printed to Serial interface
  Serial.print("Data received: ");
  Serial.println(data);
}
