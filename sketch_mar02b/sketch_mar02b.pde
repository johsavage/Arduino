#define PIN_SCK  13
#define PIN_MISO 12
#define	PIN_MOSI 11    
#define PIN_SS   10

#define BLACK  0
#define RED  0xE0
#define GREEN  0x1C
#define BLUE  0x03
#define ORANGE  RED|GREEN
#define MAGENTA  RED|BLUE
#define TEAL  BLUE|GREEN
#define WHITE (RED|GREEN|BLUE)-0xA0

char color_buffer[8];
char frameBuffer[65];


char sendChar(char cData){
  SPDR = cData;
  while(!(SPSR&(1<<SPIF)));

  return SPDR;
}

// Send a full frame to the LED matrix
void sendFrame(char *frame) {

  digitalWrite(PIN_SS, LOW);
  delayMicroseconds(500);

  // send the full buffer
  for(int i=0;i<64;i++) {
    char c;
    c=*(frame+i);
    // This is needed because sending a '%' will reconfigure the
    // board for daisy chain operation
    if('%'==c)
      sendChar((2<<5)&(1<<2)&1); // similar color
    else
      sendChar(c);
  }

  digitalWrite(PIN_SS, HIGH);

  // The LED Matrix datasheet's recommends this delay on daisy
  // chain configurations
  delayMicroseconds(10);
}

void setup(){

  SPCR=(1<<SPE)|(1<<MSTR)|(1<<SPR1)|(1<<SPR0);
  SPSR = SPSR & B11111110;

  pinMode(PIN_SCK, OUTPUT);
  digitalWrite(PIN_SCK, LOW); // ensure clock low
  pinMode(PIN_MOSI, OUTPUT);
  pinMode(PIN_SS, OUTPUT);
  digitalWrite(PIN_SS, HIGH); // de-assert SS
  delayMicroseconds(500); // delay as the LED Matrix datasheet's recommends

  // This section reconfigure the board to no daisy chain
  // operation.
  // This can be confirmed by an RRGGBB pattern beginning at a
  // corner, with no black LEDs before the first LED, when the
  // matrix is powered on.
  // Warning: this will take effect only after first run, power
  // off and power on!

  digitalWrite(PIN_SS, LOW);
  delayMicroseconds(500);
  sendChar('%');
  sendChar(1);
  digitalWrite(PIN_SS, HIGH);
  delayMicroseconds(10);


  for(int LED=0; LED<64; LED++)
  {
    frameBuffer[LED] = BLACK;
  }

  color_buffer[0]=BLACK;
  color_buffer[1]=RED;
  color_buffer[2]=GREEN;
  color_buffer[3]=BLUE;
  color_buffer[4]=ORANGE;
  color_buffer[5]=MAGENTA;
  color_buffer[6]=TEAL;
  color_buffer[7]=WHITE;


}


void loop()
{
  int pos = 0;
  int color = 1;
  sendFrame(frameBuffer);


  while(1)
  {
    for(int LED=0; LED<64; LED++)
    {
      if( LED == pos )
      {
        frameBuffer[LED] = color_buffer[color];
      } 



      pos++;

      if( pos >= 64 )
      {
        pos = 0;
        color++;
      }

      if(color> 7)
      {
        color = 0;
      }

      sendFrame(frameBuffer);
      //delay(100);
    }

  }


}


/*
void loop(){
 char frameBuffer[64];
 
 // Cycle through each possible color
 for(int color=0;color<=255;color++) {
 // And populate each position of the buffer with one color
 for(int j=0;j<64;j++) {
 frameBuffer[j]=j+color;
 }
 // Send the frame to the LED Matrix
 sendFrame(frameBuffer);
 // Colors are made by blinking the LEDs very fast.
 // Decreasing this delay too much (or removing it) may lead
 // to corrupted images.
 delay(200);
 }
 }
 */





