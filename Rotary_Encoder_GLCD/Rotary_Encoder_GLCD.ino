//#include <IRremoteInt.h>
//#include <IRremote.h>

#include <glcd.h>
#include "fonts/allFonts.h"

#include <RotaryEncoder.h>
#include <TimerThree.h>

#define CLEARSCREENPAUSE 40





gText countdownArea =  gText(GLCD.CenterX, GLCD.CenterY,1,1,Arial_14); // text area for countdown digits
gText encoderArea = gText(0, 0, 5, 1, System5x7);
gText dataArea = gText (30, 0, 5, 1, System5x7);

enum PinAssignments {
  pinEncoderA       = 18,                     
  pinEncoderB       = 19,                     
  pinEncoderRed     = 2,
  pinEncoderGreen   = 3,
  pinEncoderBlue    = 4,
  pinEncoderSwitch  = 51,
  pinLEDStart       = 12,
  pinLEDEnd         = 5,
};


unsigned int lastEncoderPosition = -1;    

boolean timerStarted = false;

byte pinCurrentLED = pinLEDEnd;

void setup()
{

  Serial.begin(9600);
  RotaryEncoder.begin(pinEncoderRed,pinEncoderGreen,pinEncoderBlue,pinEncoderSwitch,pinEncoderA,pinEncoderB);

  GLCD.Init(NON_INVERTED);
  introScreen();
  GLCD.ClearScreen();

  for( int i = pinLEDStart; i > pinLEDEnd-1; i-- )
  {
    pinMode(i, OUTPUT);
    digitalWrite(i,LOW);  
  }

  drawScreen();

  Timer3.initialize(250000);         // initialize timer1, and set a 1/2 second period
  Timer3.attachInterrupt(callbackShiftLED);  // attaches callback() as a timer overflow interrupt

}

void callbackShiftLED()
{
 
  if( timerStarted )
  {
    digitalWrite(pinCurrentLED, LOW);
    pinCurrentLED--;
    
    if( pinCurrentLED < pinLEDEnd )
      pinCurrentLED = pinLEDStart;

    digitalWrite(pinCurrentLED,HIGH);

    dataArea.ClearArea();
    dataArea.print(pinCurrentLED);
   
  }

  
}



void loop()
{  

  RotaryEncoder.setRotating(true);  

  if (lastEncoderPosition != RotaryEncoder.getEncoderPosition()) 
  {
    if( RotaryEncoder.getEncoderPosition() > 4096 )
      RotaryEncoder.setEncoderPosition(0);

    encoderArea.ClearArea(); 
    encoderArea.print(RotaryEncoder.getEncoderPosition());

    lastEncoderPosition = RotaryEncoder.getEncoderPosition();
  }


  if( RotaryEncoder.debounce())
  {
    while(RotaryEncoder.debounce() == HIGH);

    timerStarted = !timerStarted;

    RotaryEncoder.cycleEncoderLED();
  }

  RotaryEncoder.pulseEncoderLED();


}

void drawScreen( void )
{
  unsigned int xPos;
  unsigned int xGap = 0;
  unsigned int xStart = 30;
  unsigned int yEnd = 44;

  GLCD.ClearScreen();
  GLCD.SelectFont(System5x7);

  for(int i=1; i<9; i++)
  {
    if( (i-1) % 2 == 0 && i != 1)
      xGap+=5;

    xPos = xStart + (i*8) + xGap;

    GLCD.CursorToXY(xPos, 10);
    GLCD.print(i);

    GLCD.DrawLine(xPos+2, 18, xPos+2, yEnd, BLACK);
    GLCD.DrawLine(xPos+1, 18, xPos+3, 18, BLACK);
    GLCD.DrawLine(xPos+1, yEnd, xPos+3, yEnd, BLACK);


    GLCD.CursorToXY(xPos, yEnd+2);
    GLCD.print(i);
  } 
}


void introScreen()
{
  GLCD.ClearScreen();
  GLCD.SelectFont(Arial_14);

  GLCD.CursorToXY(GLCD.Width/2 - 44, 3);
  GLCD.print("Rotary Encoder");
  GLCD.DrawRoundRect(8,0,GLCD.Width-19,17, 5);  // rounded rectangle around text area   
  countdown(1);  
}

void countdown(int count){
  while(count--){  // do countdown  
    countdownArea.ClearArea(); 
    countdownArea.print(count);
    delay(1000);  
  }  
}



