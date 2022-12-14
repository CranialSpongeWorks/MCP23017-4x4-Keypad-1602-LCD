/**************************************************************************
 This example builds a simple MCP23017 interface to 4x4 Keypad and 2 line x 16 char LCD 
 
 Board: Arduino NANO

 David C. Boyce https://www.youtube.com/@PCBoardRepair
 This sketch is available @ https://github.com/CranialSpongeWorks 
 **************************************************************************/

//Include these libraries
#include <Arduino.h>
#include <MCP23017.h>
#include "Wire.h"

// Setting up serial connection (I2C) to MCP23017 expander IC
//Select I2C_ADDR       // A0 A1 A2 Address
#define I2C_ADDR 0x20   //  L  L  L 0x20        Where 'H' means jumper is open
//#define I2C_ADDR 0x21 //  H  L  L 0x21        and 'L' means jumper is closed
//#define I2C_ADDR 0x22 //  L  H  L 0x22
//#define I2C_ADDR 0x23 //  H  H  L 0x23
//#define I2C_ADDR 0x24 //  L  L  H 0x24
//#define I2C_ADDR 0x25 //  H  L  H 0x25
//#define I2C_ADDR 0x26 //  L  H  H 0x26
//#define I2C_ADDR 0x27 //  H  H  H 0x27
//define MCP23017 addresses
#define MCP23017_IODIRA 0x00      //PORT A-Input/Output Direction
#define MCP23017_IODIRB 0x01     //PORT B-Input/Output Direction
#define MCP23017_GPPUA 0x0C      //PORT A-Input/Output Weak Pull-up
#define MCP23017_GPPUB 0x0D      //PORT B-Input/Output Weak Pull-up
#define MCP23017_GPIOA 0x12      //PORT A-Input/Output Port
#define MCP23017_GPIOB 0x13      //PORT B-Input/Output Port

//define MCP23017 defaults
#define MCP23017_PORTA_DIR 0x00001111   //PORT A Direction Default
#define MCP23017_PORTB_DIR 0x00000000   //PORT B Direction Default
#define MCP23017_PORTA 0x11111111       //PORT A Output Default
#define MCP23017_PORTB 0x00000000       //PORT B Output Default

//define PINS
byte R1 = 0x10;                  //R1 pin definition
byte R2 = 0x20;                  //R1 pin definition
byte R3 = 0x40;                  //R1 pin definition
byte R4 = 0x80;                  //R1 pin definition

// Define 8-bit variable "Port_Data" for MCP23017 output port
byte  Port_Data = B11110000;

bool  Debug = 0;                    //set to 1 to debug server stream

void setup() {      // put your setup code here, to run once:


  MCP23017_Init();              //initialize

  // Setup Serial Monitor for easy debugging  
  Serial.begin(115200);
  while (!Serial) ; // wait for Arduino Serial Monitor
  delay(200);

}

void loop() {       // put your main code here, to run repeatedly:
 Scan_Keys();       //Scan Keypad
}

void Scan_Keys() {
  Wire.beginTransmission(I2C_ADDR);
  Wire.write(MCP23017_GPIOA);
//  Port_Data = bitSet(Port_Data,0);
  Wire.write(R1);
  Wire.endTransmission(); 
  Serial.println("R1");
  delay(10);

  Wire.beginTransmission(I2C_ADDR);
  Wire.write(MCP23017_GPIOA);
//  Port_Data = bitSet(Port_Data,0);
  Wire.write(R2);
  Wire.endTransmission(); 
  Serial.println("R2");
  delay(10);

  Wire.beginTransmission(I2C_ADDR);
  Wire.write(MCP23017_GPIOA);
//  Port_Data = bitSet(Port_Data,0);
  Wire.write(R3);
  Wire.endTransmission(); 
  Serial.println("R3");
  delay(10);

  Wire.beginTransmission(I2C_ADDR);
  Wire.write(MCP23017_GPIOA);
//  Port_Data = bitSet(Port_Data,0);
  Wire.write(R4);
  Wire.endTransmission(); 
  Serial.println("R4");
  delay(10);

}

void MCP23017_Init() {              // put your code here
  Wire.begin();
  //set PORTA Pullups
  Wire.beginTransmission(I2C_ADDR); //Initiate I2C transmission to MCP23017
  Wire.write(MCP23017_GPPUA );      //setup MCP23017 Address to access 
  Wire.write(0x11111111);           //Write to register
  Wire.endTransmission();           //end I2C transmission
  //set PORTB Pullups
  Wire.beginTransmission(I2C_ADDR); //Initiate I2C transmission to MCP23017
  Wire.write(MCP23017_GPPUB);       //setup MCP23017 Address to access 
  Wire.write(0x11111111);           //Write to register
  Wire.endTransmission();           //end I2C transmission
  //set PORTA Directions
  Wire.beginTransmission(I2C_ADDR); //Initiate I2C transmission to MCP23017
  Wire.write(MCP23017_IODIRA);      //setup MCP23017 Address to access 
  Wire.write(MCP23017_PORTA_DIR);   //Write to register
  Wire.endTransmission();           //end I2C transmission
  //set PORTB Directions
  Wire.beginTransmission(I2C_ADDR); //Initiate I2C transmission to MCP23017
  Wire.write(MCP23017_IODIRB);      //setup MCP23017 Address to access 
  Wire.write(MCP23017_PORTB_DIR);   //Write to register
  Wire.endTransmission();           //end I2C transmission
  //set PORTA Data
  Wire.beginTransmission(I2C_ADDR); //Initiate I2C transmission to MCP23017
  Wire.write(MCP23017_GPIOA);       //setup MCP23017 Address to access 
  Wire.write(MCP23017_PORTA);       //Write to register
  Wire.endTransmission();           //end I2C transmission
  //set PORTB Data
  Wire.beginTransmission(I2C_ADDR); //Initiate I2C transmission to MCP23017
  Wire.write(MCP23017_GPIOB);       //setup MCP23017 Address to access 
  Wire.write(MCP23017_PORTB);       //Write to register
  Wire.endTransmission();           //end I2C transmission

}
