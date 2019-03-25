#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 4;
const int LED_NUM = 8;

//define the symbols 
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

int leds[LED_NUM] = {28, 29, 30, 31, 32, 33, 34, 35};

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

//init all the leds to output
void setup()
{
  Serial.begin(9600);

  for(int i = 0; i < LED_NUM; i++)
  {
    pinMode(leds[i], OUTPUT);
  }
}
  
void loop()
{
  String tempNumber = " ";
  char digit = ' ';
  
  while(digit != '#')
  {
    digit = customKeypad.getKey();

     if(0 <= digit && digit >= 9)
     {
        tempNumber += digit;
     }
  }

  int number = tempNumber.toInt();
  
  if(0 <= number && number <= 255)
  {
    for(int i = 7; i >= 0; i--)
    {
      int binaryBit = number >> i;
  
      if(binaryBit & 1)
      {
        Serial.print(1);
        digitalWrite(leds[i], HIGH);
      }
      else
      {
        Serial.print(0);
        digitalWrite(leds[i], LOW);
      }
    }

    Serial.println();
  }
}
