#include <RGB.h>
#include <RGBMatrix.h>

int NUM_BOARDS = 2;

char colors[8] = { 
  BLACK, RED, GREEN, BLUE, ORANGE, MAGENTA, TEAL, WHITE };


/*
byte spectrum[]={
 // RED
 RGB(7, 1, 0), RGB(7, 2, 0), RGB(7, 3, 0), RGB(7, 4, 0), RGB(7, 5, 0), RGB(7, 6, 0), RGB(7, 7, 0), 
 // YELLOW
 RGB(6, 7, 0), RGB(5, 7, 0), RGB(4, 7, 0), RGB(3, 7, 0), RGB(2, 7, 0), RGB(1, 7, 0), RGB(0, 7, 0), 
 // GREEN
 RGB(0, 7, 1), RGB(0, 7, 1), RGB(0, 7, 2), RGB(0, 7, 2), RGB(0, 7, 2), RGB(0, 7, 3), RGB(0, 7, 3), 
 // CYAN
 RGB(0, 6, 3), RGB(0, 5, 3), RGB(0, 4, 3), RGB(0, 3, 3), RGB(0, 2, 3), RGB(0, 1, 3), RGB(0, 0, 3), 
 // BLUE
 RGB(1, 0, 3), RGB(2, 0, 3), RGB(3, 0, 3), RGB(4, 0, 3), RGB(5, 0, 3), RGB(6, 0, 3), RGB(7, 0, 3), 
 // MAGENTA
 RGB(7, 0, 2), RGB(7, 0, 2), RGB(7, 0, 1), RGB(7, 0, 1), RGB(7, 0, 1), RGB(7, 0, 0), RGB(7, 0, 0), 
 };
 
 */

const char smileyFace[] = {
  0x0,0x26,0x46,0x40,0x40,0x46,0x26,0x0};

int screen[16];

void setup()
{
  delay(5000); 
  Serial.begin(115200);

  for(int i=0;i<16;i++)
  {
    screen[i] = 0;

  }


  RGBMatrix.begin(NUM_BOARDS);

  randomSeed(analogRead(0));

  displayBoards();
}

void displayMessage(void)
{
  RGBMatrix.scroll("HELLO ABIGAIL", GREEN, 40);
}

void displayBoards(void)
{

  RGBMatrix.clear();  
  char letter = 'A';  

  for(int board=NUM_BOARDS-1; board>=0; board--)
  {
    RGBMatrix.fillChar(board, letter, GREEN);
    letter +=1;  
  }
  RGBMatrix.display(); 
  delay(1000);

}

void displayRandom()
{
  RGBMatrix.clear();

  for(int count=0; count<500; count++)
  {
    RGBMatrix.fillPixel(random(NUM_BOARDS), random(8), random(8), colors[random(8)]); 
    RGBMatrix.display();
  }
  delay(100);

}

void displayFrame()
{
  RGBMatrix.clear();


  for(int column=0; column<NUM_COLUMNS; column++)
  {

    for(int board=0; board<NUM_BOARDS; board++)
    {
      RGBMatrix.fillPixel(board, 0, column, WHITE);
      RGBMatrix.fillPixel(board, 7, column, WHITE);
    }
  }

  for(int row=0; row<NUM_ROWS; row++)
  {

    RGBMatrix.fillPixel(NUM_BOARDS-1, row, 7, WHITE);

    RGBMatrix.fillPixel(0, row, 0, WHITE);
  }


  RGBMatrix.display();

}

void displayFillRow()
{
  RGBMatrix.clear();


  for(char color=1; color<8; color++)
  {
    for(int row=0; row<NUM_ROWS; row++)
    {
      for(int board=0; board<NUM_BOARDS; board++)
      {
        RGBMatrix.fillRow(board, row, colors[color]);
      }

      RGBMatrix.display();
      delay(50);        
    }

    for(int row=0; row<NUM_ROWS; row++)
    {
      for(int board=0; board<NUM_BOARDS; board++)
      {
        RGBMatrix.fillRow(board, row, BLACK);
      }

      RGBMatrix.display();
      delay(50);        
    }
  }
}

void displayFillColumn()
{

  RGBMatrix.clear();

  for(char color=1; color<8; color++)
  {

    for(int board=NUM_BOARDS-1; board>=0; board--)
    {
      for(int column=NUM_COLUMNS-1; column>=0; column--)
      {
        RGBMatrix.fillColumn(board, column, colors[color]);
        RGBMatrix.display();
        delay(50);            
      }
    }

    for(int board=0; board<NUM_BOARDS; board++)
    {
      for(int column=0; column<NUM_COLUMNS; column++)
      {
        RGBMatrix.fillColumn(board, column, BLACK);
        RGBMatrix.display();
        delay(50);            
      }
    }    
  }
}

void displayFillColors()
{
  int i=1;

  RGBMatrix.clear();


  for(int board=NUM_BOARDS-1; board>=0; board--)
  {
    for(int column=NUM_COLUMNS-1; column>=0; column--)
    {
      RGBMatrix.fillColumn(board, column, colors[i]);
      RGBMatrix.display();
      delay(10);            
      i++;

      if(i>7)
      {
        i=1;
      }  
    }
  }

  for(int board=0; board<NUM_BOARDS; board++)
  {
    for(int column=0; column<NUM_COLUMNS; column++)
    {
      RGBMatrix.fillColumn(board, column, BLACK);
      RGBMatrix.display();
      delay(10);            
    }
  }    


}

void displayFrames()
{
  int columnStart, columnEnd;
  int rowStart, rowEnd;

  columnStart = 0; 
  columnEnd = NUM_COLUMNS;
  rowStart = 0; 
  rowEnd = NUM_ROWS;


  RGBMatrix.clear();

  //for(int i=0;i<4;i++)
  //{

  //for(int board=0; board<NUM_BOARDS; board++)
  //{
  //if( board == 1)
  //{
  //  columnEnd = NUM_COLUMNS;
  //}

  //if( board == NUM_BOARDS-1 )
  //{
  //  columnStart == 0;
  //}

  //for(int column=columnStart; column<columnEnd; column++)
  //{

  //RGBMatrix.fillPixel(board, 0+i, column, colors[1+i]);    // top
  //RGBMatrix.fillPixel(board, 7-i, column, colors[1+i]);    // bottom

  //RGBMatrix.display();
  //delay(100);  

  //}

  //}  
  //columnStart++; 
  //columnEnd--;

  //}


}

void displayFace(void)
{
  RGBMatrix.clear();


  for(int color=1; color<7; color++)
  {

    for(int board=0; board<NUM_BOARDS; board++)
    {

      for(int column=0; column<NUM_COLUMNS; column++)
      {
        for(int row=0; row<NUM_ROWS; row++)
        {
          if( smileyFace[(7-column)] & (1<<row))
          {
            RGBMatrix.fillPixel(board, row, column, colors[color]);

            //screenBuffer[screen].pixel[row*8+column]=color;
          }
          else 
          {
            RGBMatrix.fillPixel(0, row, column, BLACK);
            //screenBuffer[screen].pixel[row*8+column]=BLACK;
          }
        }
      }
    }

    RGBMatrix.display();
    delay(100);
  }

}


void displayRain()
{

  char rowPos = 0;
  int number = 0;
  int count = 0;
  int board = 0;
  int column = 0;
  
  RGBMatrix.clear();

  while(count < 100)
  {

    number = random(16);

    if( screen[number] == 0)
    {
      screen[number] = 1;
    }

    for( int i=0; i<16; i++ )
    {
      if( i > 7 )
      {
        board = 1;
        column = i-7;
      }
      else
      {
        board = 0;
        column = i;
      }
      
      
      if( screen[i] > 0 )
      {

        for(int row=0; row<NUM_ROWS; row++)
        {

          if( row == screen[i]-1)
          {
            if( screen[i]-1 < 8 )
              RGBMatrix.fillPixel(board, screen[i]-1, column, TEAL);  

            if( screen[i]-1 > 0 )
            {
              if( screen[i]-2 < 8)
                RGBMatrix.fillPixel(board, screen[i]-2, column, BLUE);  
            }

          }
          else
          {
            if( screen[i]-1 >= 0 and screen[i]-1 < 10 )
            {
              if( screen[i]-3 <= 7)
                RGBMatrix.fillPixel(board, screen[i]-3, column, BLACK);
            }  
          }



        }  
        RGBMatrix.display();
        delay(2);

      }
    }

    // Increase rain drop positions
    for( int i=0; i<16; i++)
    {
      if(screen[i] > 0)
      {
        screen[i]++;
      }

      if( screen[i] > 10)
      {
        screen[i] = 0;
      }
    }

    count++;
  }



}


void loop()
{

  //displayMessage(); 
  //  
  //displayRandom();
  //displayFrame();
  //displayFillColors();
  //displayFillRow();
  //displayFillColumn();
  //displayFrames();

  //displayFace();

  displayRain();
  displayBoards();
}





















