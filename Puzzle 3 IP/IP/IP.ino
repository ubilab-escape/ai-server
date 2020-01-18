#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// Assign human-readable names to some common 16-bit color values:
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

//rotation settings 
#define VERTICAL 0
#define HORISONTAL 1

#define MAX_X 320
#define MAX_Y 240

Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Elegoo_TFTLCD tft;

int frame = 0;

String ip = "";
int percentage = 0;

char state = 4;

void setup() {
  // put your setup code here, to run once:
 tft.reset();
 uint16_t identifier = tft.readID();
 identifier=0x9341;
 tft.begin(identifier);
 tft.fillScreen(BLACK);
 frame = 0;
 percentage = 0;
 Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
 frame++;
 delay(20);
switch (state)
{
  case '0':
  
  break;
  case '1':
  IPInsertWindow(ip);
  break;
  case '2':
  AccessDeniedPaint();
  break;
  case '3':
  AccessGrantedPaint();
  break;
  case '4':
  SendingData();
  break;
}
if (Serial.available())
{
  char cmd = Serial.read();
  switch (cmd)
  {
    case 'S':
    state = Serial.read();
     tft.fillRect(0, 0, MAX_X,MAX_Y, BLACK);
    break;
    case 'I':
    ip = Serial.readStringUntil('E');
    if (state == '1')
    {
       tft.fillRect(10, 120, MAX_X-20,60, BLACK);
    tft.setCursor(25, 150);
   tft.setTextSize(3);
    tft.println(ip);
    }
    break;
  }
}
}
void AccessGrantedPaint()
{
  
  if (frame%30==0)
  {
     
    tft.setRotation(HORISONTAL);
  tft.setTextColor(GREEN);
  tft.setTextSize(6);
  tft.setCursor(50, 70);
  tft.println("ACCESS");
  tft.setCursor(30, 130);
   tft.println("GRANTED");
   for (int i = 0; i<10;i++) tft.drawRect(i, i, MAX_X-2*i,MAX_Y-2*i, GREEN);
  }
  if (frame%61==0) 
  {
    tft.fillRect(10, 10, MAX_X-20,MAX_Y-20, BLACK);
    
  }
 
}

void AccessDeniedPaint()
{
  
  if (frame%30==0)
  {
     
    tft.setRotation(HORISONTAL);
  tft.setTextColor(RED);
  tft.setTextSize(6);
  tft.setCursor(50, 70);
  tft.println("ACCESS");
  tft.setCursor(50, 130);
   tft.println("DENIED");
    for (int i = 0; i<10;i++) tft.drawRect(i, i, MAX_X-2*i,MAX_Y-2*i, RED);
  }
  if (frame%61==0) 
  {
    tft.fillRect(10, 10, MAX_X-20,MAX_Y-20, BLACK);
   
  }
}
 
void IPInsertWindow(String IP)
{
  
  if (frame%300==0)
  {
  tft.setRotation(HORISONTAL);
  tft.setTextColor(WHITE);
  tft.setTextSize(5);
  tft.setCursor(25, 55);
  tft.println("INSERT IP");
  for (int i = 0; i<10;i++) tft.drawRect(i, i, MAX_X-2*i,MAX_Y-2*i, WHITE);
  }
  
 

}

void SendingData()
{
  tft.setRotation(HORISONTAL);
  tft.setTextColor(WHITE);
  tft.setTextSize(4);
  tft.setCursor(20, 55);
  tft.println("SENDING DATA");
  for (int i = 0; i<10;i++) tft.drawRect(i, i, MAX_X-2*i,MAX_Y-2*i, WHITE);
  if (frame%1==0) percentage++;
  float load = ((MAX_X-70)/100)*percentage;
   tft.fillRect(35, 160, (int)load-10,30, GREEN);

  for (int i = 0; i<10;i++) tft.drawRect(25+i, 150+i, MAX_X-2*i-50,50-2*i, WHITE);
  
  if (percentage >70){
    tft.fillRect(0, 0, MAX_X,MAX_Y, BLACK);
    state = '2';
    percentage=0;
  }
 
}
