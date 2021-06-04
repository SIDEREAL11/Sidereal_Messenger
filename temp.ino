//You'll need to download this timer library from here
//http://www.doctormonk.com/search?q=timer
#include "Timer.h"
#include <SPI.h>
#include <SD.h>
File myFile;

// Define Variables
float V;
float temp;
float Rx;


// Variables to convert voltage to resistance
float C = 79.489;
float slope = 14.187;

// Variables to convert resistance to temp
float R0 = 100.0;
float alpha = 0.00385;

int Vin = A0; // Vin is Analog Pin A0



Timer t; // Define Timer object</p><p>
void setup() {
  Serial.begin(9600); // Set Baudrate at 9600
  pinMode(Vin,INPUT); // Make Vin Input
  t.every(100,takeReading); // Take Reading Every 100ms
}

void takeReading(){
  // Bits to Voltage
  V = (analogRead(Vin)/1023.0)*5.0; // (bits/2^n-1)*Vmax 
  // Voltage to resistance
  Rx = V*slope+C; //y=mx+c
  // Resistance to Temperature
  temp= (Rx/R0-1.0)/alpha; // from Rx = R0(1+alpha*X)
  // Uncommect to convet celsius to fehrenheit
  // temp = temp*1.8+32; 
  t.update();// Update Timer
  
 // temperature
 myFile = SD.open("temperature", FILE_WRITE);
 if (myFile)
 {
  myFile.println(Temperature);
  myFIle.println(temp);
 }
myFile.close(); // close the file in sd card 
}
}
// Links
// https://www.instructables.com/Reading-Temperature-From-PT100-Using-Arduino/
