/*
Wikihouse Sensor Node sketch
Using Grove Sensors and DFRobot CO2 sensor
Communication protocol is MQTT from the Ethernet Board
2014 francesco.anselmo@arup.com
*/

#define PIR_MOTION_SENSOR 2//Use pin 2 to receive the signal from the module 

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

#include <Wire.h>
//#include <Digital_Light_TSL2561.h>
#include <TH02_dev.h>
#include "Arduino.h"

// Networking setup
byte mac[]    = {  0xFA, 0xDE, 0xAF, 0xFA, 0xDE, 0xAF };
byte server[] = { 192, 168, 1, 10 };
byte ip[]     = { 192, 168, 1, 30 };

EthernetClient ethClient;
PubSubClient client(server, 1883, callback, ethClient);

// DFRobot CO2 Sensor
/************************Hardware Related Macros************************************/
#define         MG_PIN                       (0)     //define which analog input channel you are going to use
#define         BOOL_PIN                     (2)
#define         DC_GAIN                      (7)   //define the DC gain of amplifier
 
 
/***********************Software Related Macros************************************/
#define         READ_SAMPLE_INTERVAL         (50)    //define how many samples you are going to take in normal operation
#define         READ_SAMPLE_TIMES            (5)     //define the time interval(in milisecond) between each samples in 
                                                     //normal operation
 
/**********************Application Related Macros**********************************/
//These two values differ from sensor to sensor. user should derermine this value.
#define         ZERO_POINT_VOLTAGE           (0.324) //define the output of the sensor in volts when the concentration of CO2 is 400PPM
#define         REACTION_VOLTAGE             (0.020) //define the voltage drop of the sensor when move the sensor from air into 1000ppm CO2
 
/*****************************Globals***********************************************/
float           CO2Curve[3]  =  {2.602,ZERO_POINT_VOLTAGE,(REACTION_VOLTAGE/(2.602-3))};   
                                                     //two points are taken from the curve. 
                                                     //with these two points, a line is formed which is
                                                     //"approximately equivalent" to the original curve.
                                                     //data format:{ x, y, slope}; point1: (lg400, 0.324), point2: (lg4000, 0.280) 
                                                     //slope = ( reaction voltage ) / (log400 –log1000) 
 

void setup() {
  Serial.println("Wikihouse Sensor Node");
  Serial.begin(9600);           // set up Serial library at 9600 bps
  
  Wire.begin(); 
  //TSL2561.init(); 
  delay(200);
  TH02.begin();
  delay(200);
    
  Ethernet.begin(mac, ip);
  if (client.connect("wikihouseSensor1")) {
    //client.subscribe("light");
    client.subscribe("temperature");
    client.subscribe("humidity");
  }
  
  pinsInit();  
  pinMode(BOOL_PIN, INPUT);                        //set pin to input
  digitalWrite(BOOL_PIN, HIGH);                    //turn on pullup resistors

}



void loop()
{
  client.loop();
  
  // get sensor data
  //TSL2561.getLux();
  //int luxlevel=TSL2561.calculateLux(0,0,1);
  float temperature = TH02.ReadTemperature();
  float humidity = TH02.ReadHumidity();
  float volts = analogRead(0);

  int co2;
  volts = MGRead(MG_PIN);
   
  co2 = MGGetPercentage(volts,CO2Curve);
  Serial.print("CO2:");
  if (co2 < 0) {
      co2=400;
  } 
      
  delay(500);
  
  //Serial.print(luxlevel);
  //Serial.print(" lux, ");  
  Serial.print(co2);
  Serial.print(" ppm, ");  
  Serial.print(temperature);
  Serial.print(" degC, ");  
  Serial.print(humidity);
  Serial.print(" % rel hum");  
  Serial.println();

  char buffer[7];         //the ASCII of the integer will be stored in this char array
  
  //itoa(luxlevel,buffer,10);
  //client.publish("light",buffer);

  itoa(co2,buffer,10);
  client.publish("co2",buffer);

  itoa(temperature,buffer,10);
  client.publish("temperature",buffer);
  
  itoa(humidity,buffer,10);
  client.publish("humidity",buffer);

  if(isPeopleDetected())//if it detects the moving people?
    client.publish("people","1");
      else
    client.publish("people","0");
 
  delay(1000);
}

void callback(char* topic, byte* payload, unsigned int length) {
  // empty callback
}

void pinsInit()
{
	pinMode(PIR_MOTION_SENSOR, INPUT);
}



