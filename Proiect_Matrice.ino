#include "LedControl.h"
#include <LiquidCrystal.h>

#define JoyPinX A0
#define JoyPinY A1 
#define INDEX_TIME 10

LedControl lc = LedControl(12, 11, 10, 1); //DIN, CLK, LOAD, No. DRIVER
LiquidCrystal lcd(3,4,5,6,7,8);

int Interval1 = 300; 

int PositionX = 0;
int PrevPosX = 0;
int ValX = 0;

int LetTheGameBegin = 0;
int Beginning = 1 ;

bool BallDirectionX = true;
bool BallDirectionY = false;
int BallX = random(3,7);
int BallY = random(3,7);

unsigned long LastUpdate = 0;
unsigned long LastUpdateBall = 0;

int Time = 0;
int Speed = 0;
int Lives = 5;
int NrMoves = 0;
int PrevNrMoves = 0;


const byte Start[][8] = {
{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
},{
  B00000000,
  B00000001,
  B00000000,
  B00000001,
  B00000001,
  B00000001,
  B00000000,
  B00000000
},{
  B00000000,
  B00000011,
  B00000000,
  B00000011,
  B00000010,
  B00000011,
  B00000000,
  B00000000
},{
  B00000000,
  B00000111,
  B00000001,
  B00000111,
  B00000100,
  B00000111,
  B00000000,
  B00000000
},{
  B00000000,
  B00001110,
  B00000010,
  B00001110,
  B00001000,
  B00001110,
  B00000000,
  B00000000
},{
  B00000000,
  B00011100,
  B00000100,
  B00011100,
  B00010000,
  B00011101,
  B00000000,
  B00000000
},{
  B00000000,
  B00111001,
  B00001001,
  B00111001,
  B00100001,
  B00111011,
  B00000000,
  B00000000
},{
  B00000000,
  B01110010,
  B00010010,
  B01110010,
  B01000010,
  B01110111,
  B00000000,
  B00000000
},{
  B00000000,
  B11100100,
  B00100100,
  B11100100,
  B10000100,
  B11101110,
  B00000000,
  B00000000
},{
  B00000000,
  B11001001,
  B01001001,
  B11001001,
  B00001001,
  B11011101,
  B00000000,
  B00000000
},{
  B00000000,
  B10010010,
  B10010010,
  B10010011,
  B00010010,
  B10111011,
  B00000000,
  B00000000
},{
  B00000000,
  B00100101,
  B00100101,
  B00100111,
  B00100101,
  B01110111,
  B00000000,
  B00000000
},{
  B00000000,
  B01001010,
  B01001010,
  B01001110,
  B01001010,
  B11101110,
  B00000000,
  B00000000
},{
  B00000000,
  B10010101,
  B10010101,
  B10011101,
  B10010101,
  B11011101,
  B00000000,
  B00000000
},{
  B00000000,
  B00101010,
  B00101011,
  B00111011,
  B00101010,
  B10111011,
  B00000000,
  B00000000
},{
  B00000000,
  B01010101,
  B01010110,
  B01110111,
  B01010101,
  B01110111,
  B00000000,
  B00000000
},{
  B00000000,
  B10101010,
  B10101100,
  B11101110,
  B10101010,
  B11101110,
  B00000000,
  B00000000
},{
  B00000000,
  B01010100,
  B01011000,
  B11011100,
  B01010100,
  B11011101,
  B00000000,
  B00000000
},{
  B00000000,
  B10101001,
  B10110001,
  B10111001,
  B10101001,
  B10111011,
  B00000000,
  B00000000
},{
  B00000000,
  B01010010,
  B01100010,
  B01110010,
  B01010010,
  B01110111,
  B00000000,
  B00000000
},{
  B00000000,
  B10100100,
  B11000100,
  B11100100,
  B10100100,
  B11101110,
  B00000000,
  B00000000
},{
  B00000000,
  B01001001,
  B10001000,
  B11001001,
  B01001001,
  B11011101,
  B00000000,
  B00000000
},{
  B00000000,
  B10010010,
  B00010000,
  B10010010,
  B10010010,
  B10111010,
  B00000000,
  B00000000
},{
  B00000000,
  B00100100,
  B00100000,
  B00100100,
  B00100100,
  B01110100,
  B00000000,
  B00000000
},{
  B00000000,
  B01001000,
  B01000000,
  B01001000,
  B01001000,
  B11101000,
  B00000000,
  B00000000
},{
  B00000000,
  B10010000,
  B10000000,
  B10010000,
  B10010000,
  B11010000,
  B00000000,
  B00000000
},{
  B00000000,
  B00100000,
  B00000000,
  B00100000,
  B00100000,
  B10100000,
  B00000000,
  B00000000
},{
  B00000000,
  B01000000,
  B00000000,
  B01000000,
  B01000000,
  B01000000,
  B00000000,
  B00000000
},{
  B00000000,
  B01000000,
  B00000000,
  B01000000,
  B01000000,
  B01000000,
  B00000000,
  B00000000
},{
  B00000000,
  B10000000,
  B00000000,
  B10000000,
  B10000000,
  B10000000,
  B00000000,
  B00000000
},{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
}};
const int IMAGES_LEN1 = sizeof(Start)/8;

const byte End[][8] = {
{
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111
},{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
}};
const int IMAGES_LEN2 = sizeof(End)/8;

void GameSetups(){

     if(Lives ==0){ 
      
           PositionX = 0;    
           PrevPosX = 0;
           ValX = 0;
          
           BallDirectionX = true; 
           BallDirectionY = false;
      
           LastUpdate = 0;
           LastUpdateBall = 0;
      
           LetTheGameBegin = 0;
           Beginning = 1 ;
      
           Time = 0;
           Speed = 0;
           Lives = 3;
           NrMoves = 0;
           PrevNrMoves = 0;

           Interval1 = 300;
     }
     
       BallX = random(3,7); 
       BallY = random(3,7);
}

void PlateMovement(){

       int Interval = 60;
       if(( millis() - LastUpdate) >= Interval){

            LastUpdate = millis();
            ValX = analogRead(JoyPinX);
            Serial.println(ValX);
            
            if( ValX < 340 ){
                    PrevPosX = PositionX;
                    PositionX--;
                    NrMoves++;
             }
            if( ValX > 680 ){
                    PrevPosX = PositionX;
                    PositionX++;
                    NrMoves++;
            }

            if( PositionX < 0) PositionX = 0;
            if( PositionX > 5) PositionX = 5; 
           // PositionX = PositionX % 8;

            if( PrevPosX != PositionX ){
                  lc.setLed(0,PrevPosX,0,0);
                  lc.setLed(0,PrevPosX + 1,0,0);
                  lc.setLed(0,PrevPosX + 2,0,0);
            }
            lc.setLed(0,PositionX,0,1);
            lc.setLed(0,PositionX + 1,0,1);
            lc.setLed(0,PositionX + 2,0,1);
       }
       
}

void BallMove(){

  
  if( NrMoves > PrevNrMoves + 7 ) {
    PrevNrMoves = NrMoves;
    Interval1 = Interval1 - INDEX_TIME;
    Speed++;
  }
  if( (millis() - LastUpdateBall) >= Interval1 ){ 
    
           LastUpdateBall = millis();

           lc.setLed(0,BallX,BallY,0);
           
          if (BallDirectionX)
            BallX--;
          else
            BallX++;
        
          if (BallDirectionY)
            BallY--;
          else
            BallY++;
             
          if ( BallY == 1 ){
            if ( BallX < PositionX || BallX > PositionX + 2 ){
              Lives--;
              GameOver();
            }
            else
              BallDirectionY = !BallDirectionY;
          }
          
          if( BallX == 0 || BallX == 7)
            BallDirectionX = !BallDirectionX;
            
          if( BallY == 7)
            BallDirectionY = !BallDirectionY;

           lc.setLed(0,BallX,BallY,1);
        }
}

void displayImage( const byte* image){
      for ( int i = 0; i < 8; i++)
        for ( int j = 0; j < 8; j++)
                lc.setLed(0,j,i,bitRead(image[i],7 - j));
                
}

void StartGame(){

    Beginning = 0;
    lcd.print("The Game Begins");
    for ( int i = 0; i < IMAGES_LEN1; i++){
          displayImage(Start[i]);
          delay(100);    
    }
    lcd.setCursor(1,1);
    lcd.println("Time Speed Lives ");
}

void ContinueGame(){
    PlateMovement();
    BallMove();
}

void GameOver(){
    GameSetups();
    LetTheGameBegin = 0;
     for ( int i = 0; i < IMAGES_LEN2; i++){
          displayImage(End [i]);
          delay(200);    
    }
    Lives--;
}

void setup() {
  
  Serial.begin(9600);
  Serial.println("----Start Serial Monitor-----");
  
  lc.shutdown(0,false);
  lc.setIntensity(0,2);
  lc.clearDisplay(0);
  
  pinMode(JoyPinX, INPUT);
  pinMode(JoyPinY, INPUT);

  lcd.begin(16,1);
  lcd.clear();
  lcd.setCursor(1,1);

}
int Flag;

void loop() {
  
  if( LetTheGameBegin == 1 ){
      if ( Beginning == 1 ) StartGame();
      if (Lives > 0) ContinueGame();
  }
  else{
    Flag = analogRead(JoyPinX);
    if(Flag >1000 ) LetTheGameBegin = 1;
  }
   

}
