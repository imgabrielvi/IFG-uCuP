#define S_A 2
#define S_B	3
#define S_C 4
#define S_D 5
#define S_E 6
#define S_F 7
#define S_G 8
#define P 9
#define button1 11
#define button2 10
#define trans 100

unsigned long tempo;
int val;
bool state = HIGH;

void liga(int pin){
  digitalWrite(pin, !state);
}

void desliga(int pin){
  digitalWrite(pin, state);
}

void escreve(char letra){
  switch(letra){
    case 'A': liga(S_A); liga(S_B); liga(S_C); desliga(S_D); liga(S_E); 
              liga(S_F); liga(S_G); desliga(P); break;
    case 'B': desliga(S_A); desliga(S_B); liga(S_C); liga(S_D); liga(S_E); 
              liga(S_F); liga(S_G); desliga(P); break;
    case 'C': desliga(S_A); desliga(S_B); desliga(S_C); liga(S_D); liga(S_E);
              liga(S_F); desliga(S_G); desliga(P); break;
    case 'D': desliga(S_A); liga(S_B); liga(S_C); liga(S_D); liga(S_E); 
              desliga(S_F); liga(S_G); desliga(P); break;
    case 'E': liga(S_A); desliga(S_B); desliga(S_C); liga(S_D); liga(S_E);
              liga(S_F); liga(S_G); desliga(P); break;
    case 'F': liga(S_A); desliga(S_B); desliga(S_C); desliga(S_D); liga(S_E); 
              liga(S_F); liga(S_G); desliga(P); break;
    case '0': liga(S_A); liga(S_B); liga(S_C); liga(S_D); liga(S_E); 
              liga(S_F); desliga(S_G); desliga(P); break;
    case '1': desliga(S_A); liga(S_B); liga(S_C); desliga(S_D); desliga(S_E);
              desliga(S_F); desliga(S_G); desliga(P); break;
    case '2': liga(S_A); liga(S_B); desliga(S_C); liga(S_D); liga(S_E);
              desliga(S_F); liga(S_G); desliga(P); break;
    case '3': liga(S_A); liga(S_B); liga(S_C); liga(S_D); desliga(S_E); 
              desliga(S_F); liga(S_G); desliga(P); break;
    case '4': desliga(S_A); liga(S_B); liga(S_C); desliga(S_D); desliga(S_E); 
              liga(S_F); liga(S_G); desliga(P); break;
    case '5': liga(S_A); desliga(S_B); liga(S_C); liga(S_D); desliga(S_E); 
              liga(S_F); liga(S_G); desliga(P); break;
    case '6': liga(S_A); desliga(S_B); liga(S_C); liga(S_D); liga(S_E); 
              liga(S_F); liga(S_G); desliga(P); break;
    case '7': liga(S_A); liga(S_B); liga(S_C); desliga(S_D); desliga(S_E);
              desliga(S_F); desliga(S_G); desliga(P); break;
    case '8': liga(S_A); liga(S_B); liga(S_C); liga(S_D); liga(S_E);
              liga(S_F); liga(S_G); desliga(P); break;
    case '9': liga(S_A); liga(S_B); liga(S_C); liga(S_D); desliga(S_E);
              liga(S_F); liga(S_G); desliga(P); break;
    case '+': desliga(S_A); desliga(S_B); desliga(S_C); desliga(S_D); desliga(S_E);
              desliga(S_F); desliga(S_G); desliga(P); break;
    case '-': liga(S_A); liga(S_B); liga(S_C); liga(S_D); liga(S_E);
              liga(S_F); liga(S_G); liga(P); break;
    case '#': break;
    default:  if(val == 47){val = 57;}
    		  if(val == 58){val = 48;} break;
  }
}

void setup(){
  for(int x=2; x<10; x++) pinMode(x, OUTPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  for(int x=0; x<3; x++){
      escreve('+'); delay(trans);
      escreve('-'); delay(trans);
  }
  tempo = millis();
  val = 48;
}

void loop(){
    escreve(val);
    int Button1 = digitalRead(button1);
    int Button2 = digitalRead(button2);
    if((millis() - tempo) > trans && Button1 == LOW && Button2 == HIGH){
        val++;
        tempo = millis();
    }
    if((millis() - tempo) > trans && Button1 == HIGH && Button2 == LOW){
        val--;
        tempo = millis();
    }
    if((millis() - tempo) > trans && Button1 == LOW && Button2 == LOW){
        val = 48;
        tempo = millis();
    }
}
