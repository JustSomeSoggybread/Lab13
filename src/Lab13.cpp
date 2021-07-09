/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/evanh/OneDrive/Desktop/CTD/InternetOfThings/Lab13/src/Lab13.ino"
void isr();
void setup();
void loop();
#line 1 "c:/Users/evanh/OneDrive/Desktop/CTD/InternetOfThings/Lab13/src/Lab13.ino"
SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);

volatile bool interruptOccured = false; //must be declared volatile if used inside an isr.
volatile bool interruptsEnabled = true;

#include "oled-wing-adafruit.h"

OledWingAdafruit display;

volatile int count = 0;

void isr(){
  if (interruptsEnabled){
    count++;
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.print(count);
    Serial.println(count);
    display.display();

    interruptOccured = true;
  }
}
// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  Serial.begin(9600);
  pinMode(D6, INPUT); //green
  pinMode(D7, INPUT_PULLUP); //yellow
  interrupts();

  attachInterrupt(D6, isr, FALLING); // D6 will now generate an interrupt on the falling edge and will run the code in the isr
  
  display.setup();
  display.clearDisplay();
  display.display();  // cause the display to be updated
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Hi");

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  display.loop();
  // The core of your code will likely live here.
  if (interruptOccured){
    Serial.println("Interrupt occured");
    interruptOccured = false;
  }

  if (digitalRead(D7) == LOW){

    if (interruptsEnabled){
      interruptsEnabled = false;
      Serial.println("Interruptions disabled");
    }
    else{
      interruptsEnabled = true;
      Serial.println("Interruptions enabled");
    }

    delay(200);
  }

}