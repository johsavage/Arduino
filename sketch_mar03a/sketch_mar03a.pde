
#define CHIPSELECT 10//ss
#define SPICLOCK  13//sck
#define DATAOUT 11//MOSI
#define PIN_SCK  13
#define PIN_MISO 12
#define	PIN_MOSI 11    
#define PIN_SS   10
#define RED	0xE0 // For code readability.
#define GREEN	0x1C // Only 8 colors available
#define BLUE	0x07 // but variation possible with
#define ORANGE  0xFC // brightness (see Sparkfun doc).
#define MAGENTA	0xE3
#define TEAL	0x1F
#define WHITE	0xFF
#define BLACK	0x00

byte frame[16]; // Global frame for display. [0-7] is front frame. [8-15] is buffer frame.
byte color_tst_tbl[] = {
  MAGENTA,MAGENTA,ORANGE,ORANGE,ORANGE,WHITE,WHITE,WHITE,
  MAGENTA,MAGENTA,MAGENTA,ORANGE,ORANGE,ORANGE,WHITE,WHITE,
  RED,MAGENTA,MAGENTA,MAGENTA,ORANGE,ORANGE,ORANGE,WHITE,
  RED,RED,MAGENTA,MAGENTA,ORANGE,ORANGE,ORANGE,ORANGE,
  RED,RED,MAGENTA,MAGENTA,MAGENTA,MAGENTA,ORANGE,ORANGE,
  RED,RED,MAGENTA,MAGENTA,MAGENTA,MAGENTA,MAGENTA,ORANGE,
  RED,RED,RED,RED,RED,MAGENTA,MAGENTA,MAGENTA,
  RED,RED,RED,RED,RED,RED,MAGENTA,MAGENTA,
}; // Table of color codes, one color duplicated to get 8 entries for test purpose.

byte pattern[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0:Blank
  0x18, 0x3C, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x00, //1:A
  0x7C, 0x66, 0x66, 0x7C, 0x66, 0x66, 0x7C, 0x00, //2:B
  0x3C, 0x66, 0xC0, 0xC0, 0xC0, 0x66, 0x3C, 0x00, //3:C
  0x78, 0x6C, 0x66, 0x66, 0x66, 0x6C, 0x78, 0x00, //4:D
  0x7E, 0x60, 0x60, 0x78, 0x60, 0x60, 0x7E, 0x00, //5:E
  0x7E, 0x60, 0x60, 0x78, 0x60, 0x60, 0x60, 0x00, //6:F
  0x3C, 0x66, 0xC0, 0xC0, 0xCE, 0x66, 0x3E, 0x00, //7:G
  0x66, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x66, 0x00, //8:H
  0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, //9:I
  0x06, 0x06, 0x06, 0x06, 0x66, 0x66, 0x3C, 0x00, //10:J
  0x66, 0x66, 0x6C, 0x78, 0x6C, 0x66, 0x66, 0x00, //11:K
  0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7E, 0x00, //12:L
  0xC6, 0xEE, 0xFE, 0xFE, 0xD6, 0xC6, 0xC6, 0x00, //13:M
  0xC6, 0xE6, 0xF6, 0xDE, 0xCE, 0xC6, 0xC6, 0x00, //14:N
  0x3C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x00, //15:O
  0x7C, 0x66, 0x66, 0x7C, 0x60, 0x60, 0x60, 0x00, //16:P
  0x3C, 0x66, 0x66, 0x66, 0x6E, 0x3C, 0x0E, 0x00, //17:Q
  0x7C, 0x66, 0x66, 0x7C, 0x6C, 0x66, 0x66, 0x00, //18:R
  0x3C, 0x66, 0x70, 0x38, 0x0E, 0x66, 0x3C, 0x00, //19:S
  0x7E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, //20:T
  0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3E, 0x00, //21:U
  0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x00, //22:V
  0xC6, 0xC6, 0xC6, 0xD6, 0xFE, 0xEE, 0xC6, 0x00, //23:W
  0x66, 0x66, 0x3C, 0x18, 0x3C, 0x66, 0x66, 0x00, //24:X
  0x66, 0x66, 0x66, 0x3C, 0x18, 0x18, 0x18, 0x00, //25:Y
  0xFE, 0x06, 0x0C, 0x18, 0x30, 0x60, 0xFE, 0x00 //26:Z
};

void showAlphabet(char letter)
{
  if( letter > 64 && letter < 91)
  {
    int alphabet = (letter - 64)*8;
    int index = 0;
    digitalWrite(CHIPSELECT,LOW); // enable the ChipSelect on the backpack
    delayMicroseconds(500);
    for (int i=0;i<8;i++)
    {
	for (int j=0;j<8;j++)
	{
	  if (bitRead(pattern[alphabet+i],j) == 0) //bitRead funcion is used to get each 8 bit of the 8 bytes pattern table (64 bits in total).
	  {
	    sendChar(BLACK);
	  }	 // bit is 0 -> Transfer Black color.
	  else
	  {
	    //sendChar(color_tst_tbl[index]);
            sendChar(RED);
	  } // bit is 1 -> Transfer a color choosen in the color test table.
	  index++;
	}
    }   // 64 bytes should have been transfered to the RGB matrix.
    digitalWrite(CHIPSELECT,HIGH); // disable the ChipSelect on the backpack
    // What you've send is displayed on the matrix.
    delayMicroseconds(500);
  }
}


void setup()
{
 
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

}
char sendChar(char cData){
  SPDR = cData;
  while(!(SPSR&(1<<SPIF)));

  return SPDR;
}
char incoming_letter;

void loop()
{
  
  char hw[]= "JOHN";
  for (int i=0;i<4;i++)
  {
    showAlphabet(hw[i]);
    delay(500);
  }
  
}
 
