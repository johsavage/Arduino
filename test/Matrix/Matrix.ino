#include <RGB.h>
#include <RGBMatrix.h>

int NUM_BOARDS = 8;
int RAIN_SIZE = 40;

char colors[8] = { BLACK, RED, GREEN, BLUE, ORANGE, MAGENTA, TEAL, WHITE};
const byte smileyFace[] = {0x0,0x26,0x46,0x40,0x40,0x46,0x26,0x0};

unsigned int rainPositions[40];

void setup()
{
  delay(5000); 
  Serial.begin(115200);

  pinMode(7, INPUT);

  // Clear array
  for(int i=0;i<RAIN_SIZE;i++)
  {
    rainPositions[i] = 0;
  }

  RGBMatrix.begin(NUM_BOARDS);

  RGBMatrix.clear();
  displayBoards();

  randomSeed(analogRead(0));
}

void displayMessage(void)
{
  RGBMatrix.scroll("JOHN WAS HERE!", GREEN, 40);
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

  for(int count=0; count<2000; count++)
  {
    RGBMatrix.fillPixel(random(NUM_BOARDS), random(8), random(8), colors[random(8)]); 
    RGBMatrix.display();
  }
  delay(1);

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
      delay(1);        
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
        delay(5);            
      }
    }

    for(int board=0; board<NUM_BOARDS; board++)
    {
      for(int column=0; column<NUM_COLUMNS; column++)
      {
        RGBMatrix.fillColumn(board, column, BLACK);
        RGBMatrix.display();
        delay(5);            
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
  int count=0;


  for(int color=1; color<255; color++)
  {

    for(int board=0; board<NUM_BOARDS; board++)
    {

      for(int column=0; column<NUM_COLUMNS; column++)
      {
        for(int row=0; row<NUM_ROWS; row++)
        {
          if( smileyFace[(7-column)] & (1<<row))
          {
            RGBMatrix.fillPixel(board, row, column, color);
          }
          else 
          {
            RGBMatrix.fillPixel(0, row, column, BLACK);
          }
        }
      }
    }

    RGBMatrix.display();
    delay(50);

  }

}

/*
void displayRain()
{

  unsigned int randomNumber, currentBoard, currentColumn, rowPosition;
  unsigned int count;
  unsigned int totalColumns;
 
  randomNumber = 0; 
  currentBoard = 0; 
  currentColumn = 0; 
  rowPosition = 0; 
  count=0;
  totalColumns = 8 * NUM_BOARDS;

  RGBMatrix.clear();

  // Number or interations
  while(count < 500)
  {

    // Generate random number indicates column rain drop will start from
    randomNumber = random(totalColumns);

    if( rainPositions[randomNumber] == 0)
    {
      rainPositions[randomNumber] = 1;
    }

    // Increase rain drop row positions
    for( int i=0; i<totalColumns; i++)
    {
      if(rainPositions[i] > 0)
      {
        rainPositions[i]++;
      }

      // Reset column once drop has left the rainPositions
      if( rainPositions[i] > totalColumns+2)
      {
        rainPositions[i] = 0;
      }
    }

    // Display rain drops
    // NOTE: Need fix for NUM_BOARDS

    for( int i=0; i<totalColumns; i++ )
    {
      // Set current board and column
      if( i % 8 = 0 )
      {
        currentBoard++;
        currentColumn = i - (currentBoard * 8);
      }
      
      // Rain drop waiting to be displayed
      if( rainPositions[i] > 0 )
      {

        // Iterate through the rows
        for(int row=0; row<NUM_ROWS; row++)
        {

          // Rain drop exists on current row
          if( rainPositions[i]-1 = row)
          {
            // Front of drop color
            if( rainPositions[i]-1 < 8 )
            {
              RGBMatrix.fillPixel(currentBoard, rainPositions[i]-1, currentColumn, TEAL);  
            }

            // Behind drop color
            if( rainPositions[i]-1 > 0 )
            {
              if( rainPositions[i]-2 < 8)
              {
                RGBMatrix.fillPixel(currentBoard, rainPositions[i]-2, currentColumn, BLUE);  
              }  
            }

          }
          else
          {
            // Clear previous rain drop position
            if( rainPositions[i]-1 >= 0 and rainPositions[i]-1 < 10 )
            {
              if( rainPositions[i]-3 <= 7)
              {
                RGBMatrix.fillPixel(currentBoard, rainPositions[i]-3, currentColumn, BLACK);
              } 
            } 
          }

        }  

        RGBMatrix.display();
        delay(10);

      }
    }

    count++;
  }



}
*/

void displayCrossLines(void)
{
  int row = 0;


  for( int color=1; color<8; color++)
  {
    RGBMatrix.clear();

    for( int column = 0; column<NUM_COLUMNS; column++)
    {


      if( column > 0)
      {
        for(int board=0; board<NUM_BOARDS; board++)
        {
          RGBMatrix.fillColumn(board, column-1, BLACK);
        }
        RGBMatrix.display();
      }


      if( row > 0)
      {
        for(int board=0; board<NUM_BOARDS; board++)
        {
          RGBMatrix.fillRow(board, row-1, BLACK);
        }
        RGBMatrix.display();
      }

      for(int board=0; board<NUM_BOARDS; board++)
      {

        RGBMatrix.fillColumn(board, column, colors[color]);
        RGBMatrix.fillRow(board, row, colors[color]);

      }   
      RGBMatrix.display();

      row++;
      if(row > NUM_ROWS)
      {
        row = 0;
      }

      delay(5);
    } 

    row = NUM_ROWS-2;


    for( int column = NUM_COLUMNS-2; column>0; column--)
    {


      if( column < NUM_COLUMNS)
      {
        for(int board=0; board<NUM_BOARDS; board++)
        {
          RGBMatrix.fillColumn(board, column+1, BLACK);
        }
        RGBMatrix.display();
      }


      if( row <= NUM_ROWS)
      {
        for(int board=0; board<NUM_BOARDS; board++)
        {

          RGBMatrix.fillRow(board, row+1, BLACK);
        }
        RGBMatrix.display();
      }

      for(int board=0; board<NUM_BOARDS; board++)
      {

        RGBMatrix.fillColumn(board, column, colors[color]);
        RGBMatrix.fillRow(board, row, colors[color]);
      }   
      RGBMatrix.display();

      row--;
      if(row < 0)
      {
        row = NUM_ROWS-1;
      }

      delay(5);
    } 


  }



}


void displayLevel( void )
{
  
  RGBMatrix.clear();
  
  for(char i=0; i<10; i++ )
  {
    RGBMatrix.fillNumber(0, i, GREEN);
    RGBMatrix.display();
    
    delay(1000);
  }
  
}
    
    

void loop()
{
 //Serial.println(analogRead(5)/10);
  
  displayBoards();
  
  //displayLevel();
  
  //  
  //displayRandom();
  //displayFrame();
  displayFillColors();
  displayFillRow();
  displayFillColumn();
  //displayFrames();

  displayFace();
  //displayRain();

  displayCrossLines();
  displayMessage(); 
  
  


}



























