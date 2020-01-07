/*   ____   _               __                                  
//   / ___| (_) _ __ ___    /_/   _ __      ___   __ _  _   _  ___ 
//   \___ \ | || '_ ` _ \  / _ \ | '_ \    / __| / _` || | | |/ __|
//    ___) || || | | | | || (_) || | | |   \__ \| (_| || |_| |\__ \
//   |____/ |_||_| |_| |_| \___/_|_| |_|   |___/ \__,_| \__, ||___/
//   |  _ \ | |  __ _  _ __    / ___|                   |___/      
//   | |_) || | / _` || '_ \  | |                                
//   |  __/ | || (_| || | | | | |___                             
//   |_|    |_| \__,_||_| |_|  \____|                            
*/                                   
//   By Group 8                              
// 
//
// Color = Out_Pin   // Green = 13 / White = 12 / Yellow = 14  / Blue = 27  / Red = 26
// Color = Input_Pin // Green = 18 / White = 19 / Yellow = 21  / Blue = 22  / Red = 23
//
//

int timer=150; 


int show[]={13,12,14,27,26}; //Initial led wave to draw user attention (also used in setup() to define output pins)
int input[]={18,19,21,22,23}; //Used in setup() to define input pins

int simon[5][5]={{27,14,14,13,13},  //Different sequences matrix. 
                 {12,26,13,14,12},
                 {13,26,27,12,12},
                 {27,14,26,13,13},
                 {12,27,14,14,27}};

int sol[5][5]={{18,23,23,21,21}, // Solutions for each sequence (solution wrt the input pin (look under the ascii text))
               {19,23,18,21,19},
               {23,23,18,19,19},
               {21,18,18,21,23},
               {22,21,19,22,21}};

int input_sequence[5];
int pinCount = 5; // Should be constant since is the button counter, but maybe in tests we use less buttons.
//int buzz = 7;  
int code;
int randnum; // Random selection of row
int error;
        
unsigned long previousMillis = 0;

void setup() 
{
 // pinMode(buzz, OUTPUT);
  for (int i = 0; i < pinCount; i++) 
  {
    pinMode(show[i], OUTPUT);
    pinMode(input[i], INPUT_PULLUP);
  }
}

void loop() 
{
  unsigned long currentMillis = millis(); 
  //code = choosecode();
  code = 0;
  error = 0;
  preamble(); 
               
  while(error < 3)
  {
    sequence_show(error); // Here is where simon[][] is showed to the user.
    sequence_read(); // Here is where input_sequence[] is compared with sol[][]
  }
} // end of loop()

int choosecode()
{
    randnum = random(0,5); // random(0,pinCount-1)??; 
    return randnum;
} // end of choosecode()

void preamble() 
{
    for (int k = 0; k < 3; k++) 
    {
      for (int out = 0; out < pinCount; out++) 
      {
        digitalWrite(show[out], HIGH);
        delay(timer);
        digitalWrite(show[out], LOW);
        //tone(buzz,800,10); //Commented bcz is super annoying
      }
        
      for (int out = 4; out >= 0; out--) 
      {
        digitalWrite(show[out], HIGH);
        delay(timer);
        digitalWrite(show[out], LOW);
        //tone(buzz,800,10); //Commented bcz is super annoying
      }
    }
  delay(1000);
} // end of preamble()

void sequence_read()
{
  int flag = 0; // This is the state toggle. Analize inputs, when detected flag == 1. 
              // The logic is while inputs are correct, while function remains. if the whole sequence is correct (correctly compared), for function ends and final sequence -puzzle_correct()- starts 

  for (int i = 0; i < pinCount; i++)
  {
    flag = 0;
    while(flag == 0)
    {
      if (digitalRead(18) == LOW) 
      {
        digitalWrite(13, HIGH); // When the button is pressed, the led turns on... because why not
        input_sequence[i] = 8;
        flag = 1; // exit while
        delay(200);
        if (input_sequence[i] != sol[code][i]) //input comparisson with solution
        {
          digitalWrite(13, LOW);
          w_input();
          return;
        }
        digitalWrite(13, LOW);
      }

      if (digitalRead(19) == LOW)
      {
        digitalWrite(12, HIGH);
        input_sequence[i] = 9;
        flag = 1;
        delay(200);
        if (input_sequence[i] != sol[code][i])
        {
          digitalWrite(12, LOW);
          w_input();
          return;
        }
        digitalWrite(12, LOW);
      }

      if (digitalRead(21) == LOW)
      {
        digitalWrite(14, HIGH);
        input_sequence[i] = 10;
        flag = 1;
        delay(200);
        if (input_sequence[i] != sol[code][i])
        {
          digitalWrite(14, LOW);
          w_input();
          return;
        }
        digitalWrite(14, LOW);
      }

      if (digitalRead(22) == LOW)
      {
        digitalWrite(27, HIGH);
        input_sequence[i] = 11;
        flag = 1;
        delay(200);
        if (input_sequence[i] != sol[code][i])
        {
        digitalWrite(27, LOW);
        w_input();
        return;
      }
        digitalWrite(27, LOW);
      }

      if (digitalRead(23) == LOW)
      {
        digitalWrite(26, HIGH);
        input_sequence[i] = 12;
        flag = 1;
        delay(200);
        if (input_sequence[i] != sol[code][i])
        {
          digitalWrite(26, LOW);
          w_input();
          return;
        }
        digitalWrite(26, LOW);
      }
    } 
  }
  puzzle_correct(); // This is the puzzle ending sequence. 
} // end of sequence_read()

void sequence_show(int x)
{
  for (int s = 0; s < pinCount; s++) 
    {
      digitalWrite(simon[code][s], HIGH);
      delay(1000-x*10);
      digitalWrite(simon[code][s], LOW);
      delay(300);
      //tone(buzz,800,10); //Commented bcz is super annoying
    }
} // end of sequence_show()

void w_input()
{
  error++;
  for (int w = 0; w < 10; w++) 
    {
        digitalWrite(26, HIGH);
        delay(250);
        digitalWrite(26, LOW);
        delay(350);
        //tone(buzz,800,10); //Commented bcz is super annoying
    }
}

void puzzle_correct()
{
  for (int out = 0; out < 10; out++) 
  {
    digitalWrite(show[0], HIGH);
    delay(250);
    digitalWrite(show[0], LOW);
    delay(350);
    //tone(buzz,800,10); //Commented bcz is super annoying
  }
   error=4; // This is for testing purposes (continuity). gives a new maze.  
} // end of puzzle_correct()
