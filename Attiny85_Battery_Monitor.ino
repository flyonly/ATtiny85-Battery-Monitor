// RGB_Tiny Board Testing for Common Anode Rgb Leds
// with LOW it lgiths up the led and with HIGH it lights off because its INVERTED due to common anode rgb led


// Prepared by Ty Tower  "tytower@yahoo.com"


/*.
ATTiny85 Pinout
       (PCINT5/!RESET//ADC0/dW)PB5 -1    8-  VCC
 (PCINT3/XTAL1/CLK1/!OC1B/ADC3)PB3 -2    7-  PB2(SCK/USCK/SCL/ADC1/T0/INT0/PCINT2)
  (PCINT4/XTAL2/CLK0/OC1B/ADC2)PB4 -3    6-  PB1(MISO/D0/AIN1/OC0B/OC1A/PCINT1)
                               GND -4    5-  PB0(MOSI/D1/SDA/AIN0/OC0A/!OC1A/AREF/PCINT0)
*/

const int redPin = PB2;
const int greenPin = PB0;
const int bluePin = PB1;
int del = 200; // delay

// Example of sleeping and saving power
//
// Author: Nick Gammon
// Date:   25 May 2011

#include <avr/sleep.h>
#include <avr/wdt.h>

// watchdog interrupt
ISR(WDT_vect)
  {
  wdt_disable();  // disable watchdog
  }

void myWatchdogEnable(const byte interval)
  { 
  MCUSR = 0;                          // reset various flags
  WDTCR |= 0b00011000;               // see docs, set WDCE, WDE
  WDTCR =  0b01000000 | interval;    // set WDIE, and appropriate delay
 
  wdt_reset();
  set_sleep_mode (SLEEP_MODE_PWR_DOWN);
  sleep_mode();            // now goes to Sleep and waits for the interrupt
  }

// Setup for outputs
void setup()
{

pinMode(redPin, OUTPUT);
pinMode(greenPin, OUTPUT);
pinMode(bluePin, OUTPUT);

digitalWrite(redPin, HIGH);
digitalWrite(bluePin, HIGH);
digitalWrite(greenPin, HIGH);
delay(200);
}

void loop(){
 for (int x = 0; x < 5; x++){ // run for x seconds then sleep
 int sensorValue = analogRead(PB3);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 4.9V):
  float voltage = sensorValue * (4.9 / 1023.0);
delay(100);
 int value=sensorValue; 

if (value<=550)  {                                                                                                                                                                                                                                                                        
      digitalWrite(redPin, LOW);
      delay(del);
      digitalWrite(redPin, HIGH);
      delay(del/2);
      digitalWrite(bluePin, HIGH);
      digitalWrite(greenPin, HIGH);
}
else 
if (value>550 && value<=575) {
    digitalWrite(redPin, LOW                                                                                                 );
      delay(del);
      digitalWrite(bluePin,HIGH);
      digitalWrite(greenPin,HIGH);
}
else 
if (value>575 && value<=640) {
    digitalWrite(greenPin, LOW);
      delay(del);
      digitalWrite(redPin, HIGH);
      digitalWrite(bluePin, HIGH);
}
else 
if (value>640 && value<=690) {
    digitalWrite(bluePin, LOW);
      delay(del);
      digitalWrite(redPin, HIGH);
      digitalWrite(greenPin, HIGH);
      
}
else 
if (value>690) {
     digitalWrite(bluePin, LOW);
       delay(del);
      digitalWrite(bluePin, HIGH);
      delay(del/2);
      digitalWrite(redPin, HIGH);
      digitalWrite(greenPin, HIGH);
}
  delay(100);
  }
  digitalWrite(redPin, HIGH);
  digitalWrite(bluePin, HIGH);
  digitalWrite(greenPin, HIGH);
  
  for (int i = 0; i < 6; i++){  // sleep for i times
  myWatchdogEnable (0b100001);  // 8 second
  }

}  // end ofloop

// sleep bit patterns:
//  1 second:  0b000110
//  2 seconds: 0b000111
//  4 seconds: 0b100000
//  8 seconds: 0b100001
