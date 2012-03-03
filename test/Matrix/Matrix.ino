#include <RGB.h>
#include <RGBMatrix.h>

int NUM_BOARDS = 2;

char colors[8] = { 
  BLACK, RED, GREEN, BLUE, ORANGE, MAGENTA, TEAL, WHITE };



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




void setup()
{
  delay(5000); 
  RGBMatrix.begin(NUM_BOARDS);

  randomSeed(analogRead(0));
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
      delay(50);            
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
      delay(50);            
    }
  }    

}




void loop()
{

  //displayMessage(); 
  //displayBoards();  
  //displayRandom();
  //displayFrame();
  //displayFillColors();
  //displayFillRow();
  //displayFillColumn();

  while(1){
    for(byte p=0;p<display.pixels;p++)
      plasma[p]-=6;
    for(byte p=0;p<display.pixels;p++)
      display.frameBuff[p]=spectrum[int(float(plasma[p])/255.0*float(SPECTRUM_LEN-1))];
    display.show();
    delay(60);
  };




}






