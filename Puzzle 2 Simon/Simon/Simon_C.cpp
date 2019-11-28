//    ____   _               __                                  
//   / ___| (_) _ __ ___    /_/   _ __    ___   __ _  _   _  ___ 
//   \___ \ | || '_ ` _ \  / _ \ | '_ \  / __| / _` || | | |/ __|
//    ___) || || | | | | || (_) || | | | \__ \| (_| || |_| |\__ \
//   |____/ |_||_| |_| |_| \___/_|_| |_| |___/ \__,_| \__, ||___/
//   |  _ \ | |  __ _  _ __    / ___|                 |___/      
//   | |_) || | / _` || '_ \  | |                                
//   |  __/ | || (_| || | | | | |___                             
//   |_|    |_| \__,_||_| |_|  \____|                            
//                                   
//   By Group 8                              
// 
//
// Color = Out_Pin   // Green = 2 / White = 3 / Yellow = 4  / Blue = 5  / Red = 6
// Color = Input_Pin // Green = 8 / White = 9 / Yellow = 10 / Blue = 11 / Red = 12
//
//

int timer=150; 


int show[]={2,3,4,5,6}; //Initial led wave to draw user attention (also used in setup() to define output pins)
int input[]={8,9,10,11,12}; //Used in setup() to define input pins

int simon[5][5]={{5,4,4,2,2},  //Different sequences matrix. 
                 {3,6,2,4,3},
                 {2,6,5,3,3},
                 {5,4,6,2,2},
                 {3,5,4,4,5}};

int sol[5][5]={{8,12,12,4,4}, // Solutions for each sequence (solution wrt the input pin (look under the ascii text))
               {9,12,8,10,9},
               {12,12,8,9,9},
               {10,8,8,10,12},
               {11,10,9,11,10}};

int input_sequence[5];
int pinCount = 5; // Should be constant since is the button counter, but maybe in tests we use less buttons.
int buzz = 7;  
int code;
int randnum; // Random selection of row
        
unsigned long previousMillis = 0;

void setup() 
{
  pinMode(buzz, OUTPUT);
  for (int i = 0; i < pinCount; i++) 
  {
    pinMode(show[i], OUTPUT);
    pinMode(input[i], INPUT);
  }
}

void loop() 
{
  unsigned long currentMillis = millis(); 
  //code = choosecode();
  code = 1;
  preamble(); // The condition to only run at the beggining is pending. (Loop until button is pressed missing ~ search for "attachinterrupt" function) 
           // Cristina's option is smarter (while(1) check all buttons break)

  sequence_show(); // Here is where simon[][] is showed to the user.
  sequence_read(); // Here is where input_sequence[] is compared with sol[][]
}

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
      if (digitalRead(8) == HIGH) 
      {
        digitalWrite(2, HIGH); // When the button is pressed, the led turns on... because why not
        input_sequence[i] = 8;
        flag = 1; // exit while
        delay(200);
        if (input_sequence[i] != sol[code][i]) //input comparisson with solution
        {
          wrong_input();
          return;
        }
        digitalWrite(2, LOW);
      }

      if (digitalRead(9) == HIGH)
      {
        digitalWrite(3, HIGH);
        input_sequence[i] = 9;
        flag = 1;
        delay(200);
        if (input_sequence[i] != sol[code][i])
        {
          wrong_input();
          return;
        }
        digitalWrite(3, LOW);
      }

      if (digitalRead(10) == HIGH)
      {
        digitalWrite(4, HIGH);
        input_sequence[i] = 10;
        flag = 1;
        delay(200);
        if (input_sequence[i] != sol[code][i])
        {
          wrong_input();
          return;
        }
        digitalWrite(4, LOW);
      }

      if (digitalRead(11) == HIGH)
      {
        digitalWrite(5, HIGH);
        input_sequence[i] = 11;
        flag = 1;
        delay(200);
        if (input_sequence[i] != sol[code][i])
        {
          wrong_input();
          return;
        }
        digitalWrite(5, LOW);
      }

      if (digitalRead(12) == HIGH)
      {
        digitalWrite(6, HIGH);
        input_sequence[i] = 12;
        flag = 1;
        delay(200);
        if (input_sequence[i] != sol[code][i])
        {
          wrong_input();
          return;
        }
        digitalWrite(6, LOW);
      }

    } 
  }

 puzzle_correct(); // This is the puzzle ending sequence. 

}// end of sequence_read()

void sequence_show()
{

  for (int i = 0; i < pinCount; i++) 
    {
      digitalWrite(simon[code][i], HIGH);
      delay(2000);
      digitalWrite(simon[code][i], LOW);
      delay(200);
      //tone(buzz,800,10); //Commented bcz is super annoying
    }
}

int wrong_input()
{
  // error++;
  // if error > 3 just skip or simplify puzzle?
  // 

} // end of wrong_input()

void puzzle_correct()
{
      for (int out = 0; out < 15; out++) 
      {
        digitalWrite(show[0], HIGH);
        delay(250);
        digitalWrite(show[0], LOW);
        delay(350);
        //tone(buzz,800,10); //Commented bcz is super annoying
      }
}

