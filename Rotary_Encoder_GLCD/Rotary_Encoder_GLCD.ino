
#include <glcd.h>

#include "fonts/allFonts.h"

gText countdownArea =  gText(GLCD.CenterX, GLCD.CenterY,1,1,Arial_14); // text area for countdown digits
gText encoderArea = gText(GLCD.CenterX, GLCD.CenterY,5,1,Arial_bold_14);

enum PinAssignments {
  encoderPinA = 2,                     // Right Pin
  encoderPinB = 3,                     // Left Pin
};

volatile unsigned int encoderPos = 0;   // a counter for the dial
unsigned int lastReportedPos = -1;       // change management
static boolean rotating = false;         // debounce management

// interrupt service routine vars
boolean A_set = false;              
boolean B_set = false;


void setup()
{
  GLCD.Init();
  introScreen();

  GLCD.ClearScreen();
  GLCD.SelectFont(Arial_bold_14, BLACK);

  pinMode(encoderPinA, INPUT); 
  pinMode(encoderPinB, INPUT); 

  // turn on pullup resistors
  digitalWrite(encoderPinA, HIGH);
  digitalWrite(encoderPinB, HIGH);

  attachInterrupt(0, doEncoderA, CHANGE);
  attachInterrupt(1, doEncoderB, CHANGE);

  //GLCD.DrawRect(5,5,15,15, BLACK);
  GLCD.DrawRect(2,47,GLCD.Width-5,15, BLACK);

    //GLCD.FillRect(6,6,13,13, (A_set && !B_set) ? BLACK:WHITE);
    //GLCD.FillRect(23,6,13,13, (B_set && !A_set) ? BLACK:WHITE);

}


void loop()
{

  rotating = true;  // reset the debouncer

  if (lastReportedPos != encoderPos) 
  {
   if(encoderPos > 65000 )
   {
     encoderPos = 0;
   }
   
   if( encoderPos > 100)
   {
     encoderPos = 100;
   }
    
  

    float percent = (float)encoderPos / 100;
    
    int barPos = (float)(GLCD.Width-5-2-1) * percent;
    GLCD.FillRect(3,48,GLCD.Width-7,13, WHITE);
    GLCD.FillRect(3,48,barPos+1,13,BLACK);
    

    encoderArea.ClearArea(); 
    encoderArea.print(encoderPos);
    encoderArea.print("%");

    lastReportedPos = encoderPos;
    
 
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

// Interrupt on A changing state
void doEncoderA()
{
  // debounce
  if ( rotating ) delay (1);  // wait a little until the bouncing is done

  // Test transition, did things really change? 
  if( digitalRead(encoderPinA) != A_set ) {  // debounce once more
    A_set = !A_set;

    // adjust counter + if A leads B
    if ( A_set && !B_set ) s
      encoderPos -= 1;

    rotating = false;  // no more debouncing until loop() hits again
  }
}

// Interrupt on B changing state, same as A above
void doEncoderB(){
  if ( rotating ) delay (1);
  if( digitalRead(encoderPinB) != B_set ) {
    B_set = !B_set;
    //  adjust counter - 1 if B leads A
    if( B_set && !A_set ) 
      encoderPos += 1;

    rotating = false;
  }
}

