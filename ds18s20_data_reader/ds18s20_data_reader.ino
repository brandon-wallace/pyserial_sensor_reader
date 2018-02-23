// DS18S20 DATA READER //////////////////////////

#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>


int data = 0;
char userInput;

#define ONE_WIRE_BUS_PIN 5
OneWire oneWire(ONE_WIRE_BUS_PIN);
DallasTemperature sensors(&oneWire);

// First sensor
DeviceAddress Probe01 = { 0x28, 0xFF, 0xD5, 0xE6, 0x86, 0x16, 0x05, 0x4E }; 
// Second sensor
DeviceAddress Probe02 = { 0x28, 0xFF, 0xB7, 0xE7, 0x86, 0x16, 0x05, 0x53 }; 
// Third sensor
DeviceAddress Probe03 = { 0x28, 0xFF, 0xF9, 0xAC, 0x8C, 0x16, 0x03, 0xDB }; 


void setup()
{
    Serial.end();
    Serial.begin(115200);
    // DS18B20 One-Wire Sensors /////////////////////////
    sensors.begin();
    sensors.setResolution(Probe01, 10);
    sensors.setResolution(Probe02, 10);
    sensors.setResolution(Probe03, 10);
    //Serial.println(sensors.getResolution(Probe01), DEC);
    //sensors.setResolution(Probe02, 10);
    //Serial.println(sensors.getResolution(Probe02), DEC);
    //sensors.setResolution(Probe03, 10);
    //Serial.println(sensors.getResolution(Probe03), DEC);
}


void loop()
{    
    // Wait for input from the serial device.
    if (Serial.available() > 0) {
        // Read the input coming in.
        userInput = Serial.read();
        // Check the input for a particular value.
        if (userInput == 'z') {

            sensors.requestTemperatures();
            float s1 = sensors.getTempFByIndex(0);
            if (s1 == -127.00) {
                Serial.print("Error");
            } else {
            Serial.print(s1);
            }
            Serial.print(" ");
            float s2 = sensors.getTempFByIndex(1);
            if (s2 == -127.00) {
                Serial.print("Error");
            } else {
            Serial.print(s2);
            }
            Serial.print(" ");
            float s3 = sensors.getTempFByIndex(2);
            if (s3 == -127.00) {
                Serial.print("Error");
            } else {
            Serial.print(s3);
            }
            Serial.println(" ");
        }
    }
}
