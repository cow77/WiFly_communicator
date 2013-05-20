#include <Arduino.h>
//#include <SoftwareSerial.h>
#include "WiFly_communicator.h"

#define SSID      "AP-SSID"

// Pins' connection
// Arduino       WiFly
//  2    <---->    TX
//  3    <---->    RX
//SoftwareSerial uart(2, 3);
//WiFly wifly(&uart);
WiFly wifly(&Serial1);  // WiFly connected to Serial1 on Leonardo/Helios

void setup() {
  //uart.begin(9600);
  Serial1.begin(9600);
  Serial.begin(9600);

  // don't do anything until the serial monitor is opened
  while (!Serial) {
    ; // wait for serial port to connect. 
  }

  Serial.println("--------- WIFLY AP --------");
  
  float ver;
  Serial.print("WiFly Version: ");
  ver = wifly.version();
  Serial.println(ver);
  if (ver < 2.45) {
    Serial.println("Warning! The WiFly's firmware probably doesn't support AP mode.");
    Serial.println("Update the WiFly's firmware with wifly_firmware_update example");
  }
  
  wifly.reset();                                  // factory RESET
  
  
  wifly.sendCommand("set w j 7\r", "AOK");        // Enable AP mode
  wifly.sendCommand("set w c 3\r", "AOK");        // Specify the channel to create network
  wifly.sendCommand("set w s " SSID "\r", "AOK"); // Set network SSID
  wifly.sendCommand("set i d 4\r", "AOK");        // Enable DHCP server
  wifly.sendCommand("set i a 10.0.0.1\r", "AOK"); // Specify IP
  wifly.sendCommand("set i n 255.255.255.0\r", "AOK"); // Specify netmask
  wifly.sendCommand("set i g 10.0.0.1\r", "AOK"); // Specify gateway
  wifly.sendCommand("save\r", "Storing");         // save
  wifly.sendCommand("reboot\r");
  
  
}

void loop() {
  while (wifly.available()) {
    Serial.write(wifly.read());
  }
  
  while (Serial.available()) {
    wifly.write(Serial.read());
  }
}
