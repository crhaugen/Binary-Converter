//Author: Chyanne Haugen
#include <Keypad.h>

//number of row and cols are const
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

int leds[LED_NUM] = {28, 29, 30, 31, 32, 33, 34, 35}; //led being mapped to strings

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

//init all the leds to output
void setup()
{
  Serial.begin(9600);

  for(int i = 0; i < LED_NUM; i++)
  {
    pinMode(leds[i], OUTPUT); //SETTING PINS TO OUTPUT
  }
}
 
//just keep running program waiting for input
void loop()
{
  String tempNumber = " ";
  char digit = ' ';
  
  //if the user has not inputted a # keep getting numbers
  while(digit != '#')
  {
    digit = customKeypad.getKey(); //reading in butttom being pressed on keypad

      //if the input is not a number don't add it
     if(0 <= digit && digit >= 9)
     {
        tempNumber += digit; //adding digits to string
     }
  }

  //get the string of numbers into ints
  int number = tempNumber.toInt();
  
  //if number is between one byte I can convert
  if(0 <= number && number <= 255)
  {
    //for each bit see if it should be 1 or 0 
    for(int i = 7; i >= 0; i--)
    {
      int binaryBit = number >> i; 
  
      //seeing if its a '1' or '0'
      if(binaryBit & 1)
      {
        Serial.print(1);
        digitalWrite(leds[i], HIGH); //turn this led on
      }
      else
      {
        Serial.print(0);
        digitalWrite(leds[i], LOW); //turn this led off
      }
    }

    Serial.println();
  }
}
