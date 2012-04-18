#include <RotaryEncoder.h>

const byte redPin = 5;  // Encoder's red LED - D5 is PWM enabled
const byte bluPin = 6;  // Encoder's blue LED- D6 is PWM enabled
const byte grnPin = 9;  // Encoder's green LED - D9 is PWM enabled
const byte swhPin = 8;  // Encoder's switch pin

enum PinAssignments {
  encoderPinA = 2,                     // Right Pin
  encoderPinB = 3                      // Left Pin
};

volatile unsigned int encoderPos = 0;   // a counter for the dial
unsigned int lastReportedPos = -1;       // change management
static boolean rotating = false;         // debounce management

// interrupt service routine vars
boolean A_set = false;              
boolean B_set = false;


void setup() 
{
  noInterrupts();
  
  Serial.begin(9600);

  RotaryEncoder.begin(redPin,grnPin,bluPin,swhPin);

  pinMode(encoderPinA, INPUT); 
  pinMode(encoderPinB, INPUT);

  digitalWrite(encoderPinA, HIGH);
  digitalWrite(encoderPinB, HIGH);

  attachInterrupt(0, doEncoderA, CHANGE);
  attachInterrupt(1, doEncoderB, CHANGE);

  interrupts();
}

void loop() 
{

  if( RotaryEncoder.debounce())
  {
    Serial.println("Switch Pressed");
    while(RotaryEncoder.debounce() == HIGH);

    RotaryEncoder.cycleEncoderLED();
  }
 
  RotaryEncoder.pulseEncoderLED();



  rotating = true;  // reset the debouncer

  if (lastReportedPos != encoderPos) 
  {
    if(encoderPos > 65000 ) encoderPos = 0;
    if( encoderPos > 100) encoderPos = 100;
    
    lastReportedPos = encoderPos;   

    Serial.print("Enocder Pos = ");
    Serial.println(encoderPos);


  }


}



// Interrupt on A changing state
void doEncoderA()
{
  // debounce
  if ( rotating ) delay (1);  // wait a little until the bouncing is done

  // Test transition, did things really change? 
  if( digitalRead(encoderPinA) != A_set ) {  // debounce once more
    A_set = !A_set;

    // adjust counter + if A leads B
    if ( A_set && !B_set ) 
      encoderPos -= 1;

    rotating = false;  // no more debouncing until loop() hits again
  }  
}

// Interrupt on B changing state, same as A above
void doEncoderB()
{
  
  if ( rotating ) delay (1);
  
  if( digitalRead(encoderPinB) != B_set ) {
    B_set = !B_set;
  
    //  adjust counter - 1 if B leads A
    if( B_set && !A_set ) 
      encoderPos += 1;

    rotating = false;
  }
}

