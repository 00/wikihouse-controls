/*
Wikihouse Ventilation Motor Controller sketch
Using Arduino Uno with the Adafruit Motor Shield V2 and the Arduino Ethernet Shield
Communication protocol is MQTT from the Ethernet Shield
2014 francesco.anselmo@arup.com
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>


// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Select ports M1 and M2
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);

// Networking setup
byte mac[]    = {  0xFA, 0xDE, 0xAF, 0xFA, 0xDE, 0xAF };
byte server[] = { 192, 168, 1, 10 };
byte ip[]     = { 192, 168, 1, 20 };

EthernetClient ethClient;
PubSubClient client(server, 1883, callback, ethClient);


void callback(char* topic, byte* payload, unsigned int length) {
  // Allocate the correct amount of memory for the payload copy
  byte* p = (byte*)malloc(length);
  // Copy the payload to the new buffer
  memcpy(p,payload,length);
  //client.publish("vents", p, length);
  char inData[5]; // Allocate some space for the string
  for (int i = 0; i < length; i++) {
    Serial.print(char(p[i]));
    inData[i] = char(p[i]); // Store it
    inData[i+1] = '\0';
  }  
  Serial.println();
  //Serial.println(String(inData).toInt());
  
  int speedV=String(inData).toInt();
  if (speedV>200) speedV=200;

  // actuate motors
  myMotor1->run(FORWARD);
  myMotor1->setSpeed(speedV);  
  delay(10);
  myMotor1->run(RELEASE);
  delay(500);
  myMotor2->run(FORWARD);
  myMotor2->setSpeed(speedV);  
  delay(10);
  myMotor2->run(RELEASE);
  delay(500);

  // Free the memory
  free(p);

}



void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Wikihouse Ventilation Motor Control");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Motor 1
  myMotor1->setSpeed(0); // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor1->run(FORWARD);
  myMotor1->run(RELEASE); // turn on motor
  
  // Motor 2
  myMotor2->setSpeed(0); // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor2->run(FORWARD);
  myMotor2->run(RELEASE); // turn on motor
  
  Ethernet.begin(mac, ip);
  if (client.connect("wikihouseVents")) {
    client.publish("vents","vents started");
    client.subscribe("vents");
  }
}


void loop()
{
  client.loop();
  myMotor1->run(FORWARD);
  //myMotor1->run(RELEASE);
  myMotor2->run(FORWARD);
  //myMotor2->run(RELEASE);
}


