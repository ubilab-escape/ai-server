                                
//   Group 8                              
// 
//
//    Color = Out_Pin   // Green = 13 / White = 12 / Yellow = 2   / Blue = 27  / Red = 26

//    Color = Input_Pin // Green = 18 / White = 19 / Yellow = 21  / Blue = 22  / Red = 23
//
//

 

int show[]={13,12,2,27,26}; // Initial led wave to draw user attention (also used in setup() to define output pins)
int input[]={18,19,21,22,23}; // Used in setup() to define input pins


int simon[5][5]={{27,2,2,13,13},  // Different sequences matrix. 
                 {12,26,13,2,12},
                 {13,26,27,12,12},
                 {27,2,26,13,13},
                 {12,27,2,2,27}};

int sol[5][5]={{18,23,23,21,21}, // Solutions for each sequence (solution wrt the input pin (look under the ascii text))
               {19,23,18,21,19},
               {23,23,18,19,19},
               {21,18,18,21,23},
               {22,21,19,22,21}};

int input_sequence[5];
int pinCount = 5; // Should be constant since is the button counter, but maybe in tests we use less buttons.
//int buzz = 7;  
int code;
int randnum; // Random selection of puzzle (row of matrix)
int error;
        
unsigned long previousMillis = 0;

const int brb = 5; // BRB because it is a big red button
const int freq = 2000;
const int channel = 0;
const int resolution = 8;
int tggl = 0;

int channel1 = 1;
const int buzz = 4;



void setup() 
{
  Serial.begin(115200);
 // pinMode(buzz, OUTPUT);
  for (int i = 0; i < pinCount; i++) 
  {
    pinMode(show[i], OUTPUT);
    pinMode(input[i], INPUT_PULLUP);
  }
  pinMode(14,INPUT_PULLUP);
  ledcSetup(channel, freq, resolution);  
  ledcAttachPin(brb, channel);
  ledcAttachPin(buzz, channel1);
}

void loop() 
{
  //code = choosecode();
  code = 0;
  Serial.print("Simon didn't say puzzle nº ");
  Serial.println(code);
  error = 0;
  while(tggl==0) //input[]={18,19,21,22,23}
  {
    Serial.println("while loop");
    if (digitalRead(18) == LOW){
      break;}
    if (digitalRead(19) == LOW){
      break;}
    if (digitalRead(21) == LOW){
      break;}
    if (digitalRead(22) == LOW){
      break;}
    if (digitalRead(23) == LOW){
      break;}
  }
  tggl = 1;
  preamble(); 
               
  while(error < 3)
  {
    sequence_show(error); // Here is where simon[][] is showed to the user.
    Serial.print("User input: ");
    sequence_read(); // Here is where input_sequence[] is compared with sol[][]
    Serial.println(" ");
  }
} // end of loop()

int choosecode()
{
    randnum = random(0,5); // random(0,pinCount-1)??; 
    return randnum;
} // end of choosecode()

void preamble() 
{
  Serial.println("Showing preamble");
  for (int k = 0; k < 4; k++) 
  {
    
      digitalWrite(13, HIGH);
      digitalWrite(12, HIGH);
      digitalWrite(2, HIGH);
      digitalWrite(27, HIGH);
      digitalWrite(26, HIGH);
      delay(400);
      digitalWrite(13, LOW);
      digitalWrite(12, LOW);
      digitalWrite(2, LOW);
      digitalWrite(27, LOW);
      digitalWrite(26, LOW);
      delay(400);      
      //tone(buzz,800,10); //Commented bcz is super annoying
  }
  delay(1500);
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
        Serial.print("18 ");
        digitalWrite(13, HIGH); // When the button is pressed, the led turns on... because why not
        input_sequence[i] = 18;
        flag = 1; // exit while
        delay(200);
        if (input_sequence[i] != sol[code][i]) //input comparisson with solution
        {
          digitalWrite(13, LOW);
          w_input();
          return;
        }
        c_input();
        digitalWrite(13, LOW);
      }

      if (digitalRead(19) == LOW)
      {
        Serial.print("19 ");
        digitalWrite(12, HIGH);
        input_sequence[i] = 19;
        flag = 1;
        delay(200);
        if (input_sequence[i] != sol[code][i])
        {
          digitalWrite(12, LOW);
          w_input();
          return;
        }
        c_input();
        digitalWrite(12, LOW);
      }

      if (digitalRead(21) == LOW)
      {
        Serial.print("21 ");
        digitalWrite(2, HIGH);
        input_sequence[i] = 21;
        flag = 1;
        delay(200);
        if (input_sequence[i] != sol[code][i])
        {
          digitalWrite(2, LOW);
          w_input();
          return;
        }
        c_input();
        digitalWrite(2, LOW);
      }

      if (digitalRead(22) == LOW)
      {
        Serial.print("22 ");
        digitalWrite(27, HIGH);
        input_sequence[i] = 22;
        flag = 1;
        delay(200);
        if (input_sequence[i] != sol[code][i])
        {
        digitalWrite(27, LOW);
        w_input();
        return;
      }
        c_input();
        digitalWrite(27, LOW);
      }

      if (digitalRead(23) == LOW)
      {
        Serial.print("23 ");
        digitalWrite(26, HIGH);
        input_sequence[i] = 23;
        flag = 1;
        delay(200);
        if (input_sequence[i] != sol[code][i])
        {
          digitalWrite(26, LOW);
          w_input();
          return;
        }
        c_input();
        digitalWrite(26, LOW);
      }
    } 
  }
  puzzle_correct(); // This is the puzzle ending sequence. 
} // end of sequence_read()

void sequence_show(int x)
{
  Serial.print("Sequence: ");
  for (int s = 0; s < pinCount; s++) 
    {
      Serial.print(simon[code][s]);
      Serial.print(" ");
      digitalWrite(simon[code][s], HIGH);
      ledcWriteTone(channel1, 600);
      delay(400);
      ledcWriteTone(channel1, 0);
      delay(600-x*10);
      ledcWriteTone(channel1, 0);
      digitalWrite(simon[code][s], LOW);
      delay(300);
      //tone(buzz,800,10); //Commented bcz is super annoying
    }
    Serial.println(" ");
} // end of sequence_show()

void w_input()
{
  Serial.println(" ");
  Serial.println("Input error, puzzle incorrect");
  error++;
  
  
     ledcWriteTone(channel1, 200);
     delay(200);
     ledcWriteTone(channel1, 100);
     delay(500);
     ledcWriteTone(channel1, 0);
     delay(2000);
      
}

void puzzle_correct()
{
  Serial.println(" ");
  Serial.println("Puzzle correctly solved");
  while(digitalRead(14) != LOW)
  {
    for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++)
    {     
      ledcWrite(channel, dutyCycle);
      delay(4);
      if (digitalRead(14) == LOW) 
        {
          dutyCycle = 0;
          ledcWrite(channel, dutyCycle);
          break;
        }
    }
      
    for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--)
    {
      // changing the LED brightness with PWM
      ledcWrite(channel, dutyCycle);   
      delay(4);
      if (digitalRead(14) == LOW) //input comparisson with solution
      {
        dutyCycle = 0;
        ledcWrite(channel, dutyCycle);
        break;
      }
    }
  }
  error=4; // This is for testing purposes (continuity). gives a new maze.  
} // end of puzzle_correct()

void c_input()
{
     ledcWriteTone(channel1, 600);
     delay(200);
     ledcWriteTone(channel1, 1000);
     delay(400);
     ledcWriteTone(channel1, 0);
     delay(10);
}