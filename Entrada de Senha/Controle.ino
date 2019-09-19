#include <EEPROM.h>

typedef struct{
    char ID[4], senha [4];
} Usuario usuario[10];

int L[5] = {},
    C[6] = {},
    cont = 0;
char digito[4];

void setup(){
   for(byte i = 0; i < 5; i++){
      digitalWrite(L[i], INPUT_PULLUP);
      digitalWrite(C[i], OUTPUT);
   }
   digitalWrite(C[i], OUTPUT);
   for(byte a = 0; a < 10; a++){
      for(byte b = 0; b < 4; b++){
         usuario[a].ID[b] = EEPROM.read(b);
         usuario[a].senha[b] = EEPROM.read(b+5);
      }
      usuario[a].ID[b] = '\0';
      usuario[a].senha[b] = '\0';
   }
}

void loop(){
   teclado();
}

void teclado(){
   for(byte a = 0; a < 6; a++){
      digitalWrite(C[0], HIGH); digitalWrite(C[1], HIGH);
      digitalWrite(C[2], HIGH); digitalWrite(C[3], HIGH);
      digitalWrite(C[4], HIGH); digitalWrite(C[5], HIGH);
      digitalWrite(C[a], LOW);
      if(digitalRead(L[0]) == LOW){
         switch (a){
            case 0: numero('1'); break;
            case 1: numero('2'); break;
            case 2: numero('3'); break;
         }
         while(digitalRead(L[0]) == LOW);
      }
      if(digitalRead(L[1]) == LOW){
         switch (a){
            case 0: numero('4'); break;
            case 1: numero('5'); break;
            case 2: numero('6'); break;
         }
         while(digitalRead(L[1]) == LOW);
      }
      if(digitalRead(L[2]) == LOW){
         switch (a){
            case 0: numero('7'); break;
            case 2: numero('9');break;
            case 3: numero('8');break;
         }
         while(digitalRead(L[2]) == LOW);
      }
      if(digitalRead(L[3]) == LOW){
         switch (a){
            case 3: numero('0'); break;
         }
         while(digitalRead(L[3]) == LOW);
      }
      if(digitalRead(L[4]) == LOW){
         switch (a){
            case 4: numero('#'); break;
            case 5: numero('*'); break;
         }
         while(digitalRead(L[4]) == LOW);
      }
   }
}

void numero(char valor){
   if(cont > 4){
      limpar();
      cont = 0;
   }
   digito[cont] = valor;
}

void limpar(){
   for(byte b = 0; b < 4; b++) digito[b] = '';
}
