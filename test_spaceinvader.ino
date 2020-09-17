#include<M5Stack.h>
#include "fuckingalien2.c"
#include "backgroundbeforegame.c"
#include "alien.c"
#include "noob.c"
#include "fuckingalien.c"
#include "laserbullet.c"
#include "shipleft.c"
#include "explode.c"
#include "shipright.c"
#include "laserbullet2.c"
#include "laserbullet3.c"
#include"background.c"
#include "monster.c"
//Declare for level up background
#define NSTARS 1024
uint8_t sx[NSTARS] = {};
uint8_t sy[NSTARS] = {};
uint8_t sz[NSTARS] = {};
uint8_t za, zb, zc, zx;
uint8_t __attribute__((always_inline)) rng()
{
  zx++;
  za = (za^zc^zx);
  zb = (zb+za);
  zc = (zc+(zb>>1)^za);
  return zc;
}
//prototype function
void gotshot(int);
void gotshot2(int);
void gotshot3(int);
void gotshot4(int);
int findAlienX   (int);
int findAlienY   (int);
int findOldAlienX(int);
int findOldAlienY(int);
bool play=false;
bool beginstarfield=false;
uint8_t level=1;
uint8_t score=0;
//Time;
unsigned long offsetA = 0;
unsigned long offsetB = 0;
unsigned long offsetC = 0;
unsigned long offsetK = 0;
unsigned long offsetexplode=0;
int bulletspeed = 5 ;
int shipspeed   = 20;
int alienSpeed  = 50 ;
int oldAlienSpeed   ;
int explodespeed= 500;
double time_now = (double)millis()/1000.0;
//Just another zzz
int c=0;
bool numalien[18];
bool hit=false;
bool endgame = false;
int hitalien;

//for alien
int countalien=18;
int speedalien=5;
boolean alienLive[18];
int alienX = 7;
int alienY = 25;
int oldAlienX = 7;
int oldAlienY = 25;
int changeAlienX = speedalien;
int changeAlienY = 0;

//this is for bullet
  int i=0;    //number of bullet 1
  int j=150;  //number of bullet 2
  int k=300;  //number of bullet 3
  int m=450;  //number of bullet 4
  int xbul[700]{};  //Find x ship
  int ybul[700]{};  //Find y ship
  bool shoot1=false;
  bool shoot2=false;
  bool shoot3=false;
  bool shoot4=false;
  bool read2=false;
  bool read3=false;
  bool read4=false;
//this is for position of ship
int X=145; // X position of ship
int Y=190; // Y position of ship

//Function for checkbull==================================================================
void checkposibul()
{
  if(shoot1==false||shoot2==false ||shoot3==false||shoot4==false and play)
  {
  if(M5.BtnB.wasPressed() and play)
  {
    if(shoot1==false && read2==false && read3==false){
    xbul[i] = X+12; 
    ybul[i] = 170;
    shoot1  = true;
    }
    if(read2==true && read3==false && read4==false){
    xbul[j] = X+12;
    ybul[j] = 170;
    shoot2  = true;
    }
    if((read3==true && shoot2==true && shoot1==true && read4==false) or (read3==true && shoot2==true && shoot1==false && read4==false)){
    xbul[k] = X+12;
    ybul[k] = 170;
    shoot3  = true;
    }
    if(read4==true && shoot3==true && shoot2==true){
    xbul[m] = X+12;
    ybul[m] = 170;
    shoot4  = true;
    }
   }
}
}
//=============================================================================
void shooting()
{
  if (millis() - offsetC >= bulletspeed and play)
  {  offsetC=millis();
  if(shoot1==true)
  {
      read2=true;
      M5.Lcd.fillRect(xbul[i],ybul[i]-3,10,30,BLACK);
      M5.Lcd.drawBitmap(xbul[i],ybul[i],10,20,(uint8_t *)laserbullet_map);
      ybul[i]=ybul[i]-3;
      gotshot(i);
      if(ybul[i]<0)
      {
      shoot1=false;
      read2=false;
      M5.Lcd.fillRect(xbul[i],ybul[i],10,25,BLACK);
      i++;
      }
      }
      
  
  if(shoot2==true)
  { 
      read3=true;
      M5.Lcd.fillRect(xbul[j],ybul[j]-3,10,30,BLACK);
      M5.Lcd.drawBitmap(xbul[j],ybul[j],10,20,(uint8_t *)laserbullet2_map);
      ybul[j]=ybul[j]-3;
      gotshot2(j);
      if(ybul[j]<0)
      {
      shoot2=false;
      read2=false;
      read3=false;
      M5.Lcd.fillRect(xbul[j],ybul[j],10,25,BLACK);
      j++;
      }
  }
  if(shoot3==true)
  {
      read4=true;
      M5.Lcd.fillRect(xbul[k],ybul[k]-3,10,30,BLACK);
      M5.Lcd.drawBitmap(xbul[k],ybul[k],10,20,(uint8_t *)laserbullet3_map);
      ybul[k]=ybul[k]-3;
      gotshot3(k);
      if(ybul[k]<0)
      {
      shoot3=false;
      read3=false;
      read4=false;
      M5.Lcd.fillRect(xbul[k],ybul[k],10,25,BLACK);
      k++;
      }
  }
  if(shoot4==true)
  {
      M5.Lcd.fillRect(xbul[m],ybul[m]-3,10,30,BLACK);
      M5.Lcd.drawBitmap(xbul[m],ybul[m],10,20,(uint8_t *)laserbullet_map);
      ybul[m]=ybul[m]-3;
      gotshot4(m);
      if(ybul[m]<0)
      {
      shoot4=false;
      read4=false;
      M5.Lcd.fillRect(xbul[m],ybul[m],10,25,BLACK);
      m++;
      }
  }
  }
} 


//=============================================================================
void drawplayer      (int X,int Y) {M5.Lcd.drawBitmap(X,Y,30,30,(uint8_t *)alien_map);}
void eraseplayerRight(int X,int Y) {M5.Lcd.fillRect  (X+28, Y, 30,30,BLACK)          ;}
void eraseplayerLeft (int X,int Y) {M5.Lcd.fillRect  (X-28, Y, 30,30,BLACK)          ;}



//================================================================================================================<Main program>
void setup() 
{
  memset(numalien, true, 18);
  za = random(256);
  zb = random(256);
  zc = random(256);
  zx = random(256);
  int X=145;
  int Y=190;
  M5.begin();
  M5.Power.begin();
  M5.Lcd.drawBitmap(0,0,320,240,(uint8_t *)backgroundbeforegame_map);  
}
void loop() {
  //when open up device
  if(!play){beforestartgame();}
//================================================================================================================<Move player Loop>
  if(millis()-offsetB >shipspeed and play) 
  {
    offsetB=millis();
    if(M5.BtnA.isPressed()&&X>=1 and play)
    { 
        eraseplayerRight  (X = X-1,Y);
        eraseplayerRight  (X = X-1,Y);
        M5.Lcd.drawBitmap (X = X-1,Y,30,30,(uint8_t *)shipleft_map);
        M5.Lcd.drawBitmap (X = X-1,Y,30,30,(uint8_t *)shipleft_map);
    }
    if(M5.BtnC.isPressed()&&X<=289 and play)
    {   
        eraseplayerLeft   (X = X+1,Y);
        eraseplayerLeft   (X = X+1,Y);
        M5.Lcd.drawBitmap (X = X+1,Y,30,30,(uint8_t *)shipright_map);
        M5.Lcd.drawBitmap (X = X+1,Y,30,30,(uint8_t *)shipright_map);
    }
  }
//================================================================================================================<Reset player Loop>
//For reset player when release button
  if(M5.BtnC.wasReleased()|| M5.BtnA.wasReleased() and play)
  {
    drawplayer(X,Y);
  }
//For check position bullet
  if(play)
  {
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(0,0);
    M5.Lcd.print("SCORE :");
    M5.Lcd.print(score);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(200,0);
    M5.Lcd.print("TIME :");
    M5.Lcd.print(millis()/1000);
    checkposibul();
  }
  
//================================================================================================================<Alien Loop>
  if( millis() - offsetA >= alienSpeed and play) 
  {
     offsetA=millis();
     moveAliens(); 
  }
//When alien out of screen
  if (findAlienX(5) >= 294){changeAlienX=-speedalien ;changeAlienY = 7;}
  if (alienX <= 6){changeAlienX=speedalien ; changeAlienY = 7;}
  if (play){shooting();}
//================================================================================================================<Game over Loop>
  if(endgame)
  {
    delay(1500);
    M5.Lcd.clear();
    M5.Lcd.fillScreen(BLACK);
    delay(1500);
    M5.Lcd.setTextSize(5);
    M5.Lcd.setCursor(30,100);
    M5.Lcd.print("GAME OVER");
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(75,170);
    M5.Lcd.print("<PRESS RESTART>");
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(40,50);
    M5.Lcd.print("SCORE :");
    M5.Lcd.print(score);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(200,50);
    M5.Lcd.print("TIME :");
    M5.Lcd.print(millis()/1000);
  }
//================================================================================================================<Level up Loop>
  if(countalien==0)
  { 
    levelup();
    M5.Lcd.drawBitmap(0,0,320,240,(uint8_t *)background_map);
    drawplayer(X,Y);
    
  }
  
  M5.update();
}


//================================================================================================================<Main function for moving alien>
void moveAliens() 
{
  if(play)
  {
    for(int c=0;c<18;c++)
    {
      if(numalien[c])
      {
        M5.Lcd.fillRect(findOldAlienX(c),findOldAlienY(c),30,30,BLACK);
        if(c%2==0)      { M5.Lcd.drawBitmap(findAlienX(c),findAlienY(c),30,30,(uint8_t *)fuckingalien2_map );}  //Draw alien in first form
        if(c%2!=0)      { M5.Lcd.drawBitmap(findAlienX(c),findAlienY(c),30,30,(uint8_t *)fuckingalien_map  );}  //Draw alien in second form
        if(hit == true) { M5.Lcd.fillRect(findAlienX(hitalien),findAlienY(hitalien),32,32,BLACK);}              //Draw black pixel when alien got shot
        if(( X <= findAlienX(c)+30 and X >= findAlienX(c) and Y < findAlienY(c)+30 and Y > findAlienY(c)) or findAlienY(c)>210 )        //When alien hit player
        {
            M5.Lcd.drawBitmap(findAlienX(1 )+40,findAlienY(1)-40,60,25,(uint8_t *)noob_map);
            M5.Lcd.drawBitmap(X,Y,30,30,(uint8_t *)explode_map);
            play=false;
            endgame=true;
        }
      }
    }
    oldAlienX = alienX; oldAlienY = alienY;
    alienX += changeAlienX ; alienY += changeAlienY;
    if(changeAlienY != 0) { changeAlienY = 0; }
  }
}

//==================================================================
int findAlienX   (int num) { return alienX + 42*(num % 6); }
//==================================================================
int findAlienY   (int num) { return alienY + 33*(num / 6); }
//==================================================================
int findOldAlienX(int num) { return oldAlienX + 42*(num % 6); }
//==================================================================
int findOldAlienY(int num) { return oldAlienY + 33*(num / 6); }


void explode()
{
  if(millis() - offsetexplode > explodespeed)
  {
    offsetexplode = millis();  
    M5.Lcd.drawBitmap(findOldAlienX(c),findOldAlienY(c),30,30,(uint8_t *)explode_map);
    
    
    
  }
}
void gotshot(int i)
{
    for(c=0;c<18;c++)
    {
        if(xbul[i] > findAlienX(c)-10 and xbul[i] < findAlienX(c)+30 and ybul[i]<findAlienY(c)+30 and ybul[i]>findAlienY(c) and numalien[c])
        {
          explode();
          countalien-- ;
          numalien[c]=false;
          hitalien=c;
          hit=true;
          shoot1=false;
          read2=false;
          score++;
          M5.Lcd.fillRect(findOldAlienX(c),findOldAlienY(c),30,30,BLACK);
          M5.Lcd.fillRect(xbul[i],ybul[i],10,22,BLACK);
          i++;
        }
    }
}
void gotshot2(int i)
{
      for(c=0;c<18;c++)
      {
        if((xbul[i] > findAlienX(c)-10 && xbul[i] < findAlienX(c)+30 && ybul[i]<findAlienY(c)+30 && ybul[i]>findAlienY(c)&&numalien[c]))
        {
          explode(); 
          countalien--;
          numalien[c]=false;
          hitalien=c;
          hit=true;
          shoot2=false;
          read2=false;
          read3=false;
          score++;
          M5.Lcd.fillRect(findOldAlienX(c),findOldAlienY(c),30,30,BLACK);
          M5.Lcd.fillRect(xbul[i],ybul[i],10,22,BLACK);
          i++;
        }
      }
}
void gotshot3(int i)
{
      for(c=0;c<18;c++)
      {
        if((xbul[i] > findAlienX(c)-10 && xbul[i] < findAlienX(c)+30 && ybul[i]<findAlienY(c)+30 && ybul[i]>findAlienY(c)&&numalien[c]))
        {
          explode(); 
          countalien--;
          numalien[c]=false;
          hitalien=c;
          hit=true;
          shoot3=false;
          read3=false;
          read4=false;
          score++;
          M5.Lcd.fillRect(findOldAlienX(c),findOldAlienY(c),30,30,BLACK);
          M5.Lcd.fillRect(xbul[i],ybul[i],10,22,BLACK);
          i++;
        }
      }
}
void gotshot4(int i){
      for(c=0;c<18;c++){
        if((xbul[i] > findAlienX(c)-10 && xbul[i] < findAlienX(c)+30 && ybul[i]<findAlienY(c)+30 && ybul[i]>findAlienY(c)&&numalien[c]))
        {
          
          explode(); 
          numalien[c]=false;
          countalien--;
          hitalien=c;
          hit=true;
          shoot4=false;
          read4=false;
          score++;
          
          M5.Lcd.fillRect(findOldAlienX(c),findOldAlienY(c),30,30,BLACK);
          M5.Lcd.fillRect(xbul[i],ybul[i],10,22,BLACK);
          i++;
        }
      }
}
void beforestartgame()
{
    if(!endgame)
    {
      play=false;
      M5.Lcd.setTextSize(2);
      M5.Lcd.setCursor(60,200);
      M5.Lcd.print("Press B to start");
    }
    if(!play and !endgame )
    {
      if(M5.BtnB.isPressed())
      {
        play=true;
        M5.Lcd.drawBitmap(0,0,320,240,(uint8_t *)background_map);
        drawplayer(X,Y);}
      }
}
void levelup()
{
  play=false;
  memset(numalien, true, 18);
  alienX = 7;
  alienY = 25;
  oldAlienX = 7;
  oldAlienY = 25;
  M5.Lcd.fillScreen(TFT_BLACK);
  level++;
  
  beginstarfield=true;
  if(!play and countalien==0 )
  {
    for(;Y>=0;)
    {
      starfield();
      drawplayer(X,Y-=3);
      if(X<145)
      {
      M5.Lcd.setTextSize(3);
      M5.Lcd.setCursor(150,100);
      M5.Lcd.print("LEVEL :");
      M5.Lcd.print(level);
      }
      else if(X>145)
      {
      M5.Lcd.setTextSize(3);
      M5.Lcd.setCursor(10,100);
      M5.Lcd.print("LEVEL :");
      M5.Lcd.print(level);
      }
    }
    if(Y<=0){Y=145;play=true;beginstarfield=0;}
    
  }
  M5.Lcd.drawBitmap(0,0,320,240,(uint8_t *)background_map);
  countalien=18;
  play=true;
  X=145;
  Y=210;
  speedalien+=3;
  
}
void starfield()
{
  if(beginstarfield)
  {
  unsigned long t0 = micros();
  uint8_t spawnDepthVariation = 255;

  for(int i = 0; i < NSTARS; ++i)
  {
    if (sz[i] <= 1)
    {
      sx[i] = 160 - 120 + rng();
      sy[i] = rng();
      sz[i] = spawnDepthVariation--;
    }
    else
    {
      int old_screen_x = ((int)sx[i] - 160) * 256 / sz[i] + 160;
      int old_screen_y = ((int)sy[i] - 120) * 256 / sz[i] + 120;
      M5.Lcd.drawPixel(old_screen_x, old_screen_y,TFT_BLACK);

      sz[i] -= 2;
      if (sz[i] > 1)
      {
        int screen_x = ((int)sx[i] - 160) * 256 / sz[i] + 160;
        int screen_y = ((int)sy[i] - 120) * 256 / sz[i] + 120;
  
        if (screen_x >= 0 && screen_y >= 0 && screen_x < 320 && screen_y < 240)
        {
          uint8_t r, g, b;
          r = g = b = 255 - sz[i];
          M5.Lcd.drawPixel(screen_x, screen_y, M5.Lcd.color565(r,g,b));
        }
        else
          sz[i] = 0; // Out of screen, die.
      }
    }
  }
  unsigned long t1 = micros();
  Serial.println(1.0/((t1 - t0)/1000000.0));
  }
}
