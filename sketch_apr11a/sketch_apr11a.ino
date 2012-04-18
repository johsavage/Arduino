
int pinStart = 11;
int pinEnd = 4;

void setup()
{
  
  for( int i = pinStart; i > pinEnd-1; i-- )
  {
    pinMode(i, OUTPUT);
  }
  
}

void loop()
{
  
  for( int i = pinStart;i > pinEnd-1; i-- )
  {
      digitalWrite(i,HIGH);
      digitalWrite( (i != pinEnd) ? i-1 : pinStart, LOW);

      delay(500);
      digitalWrite(i,LOW);
  }
 
 }
