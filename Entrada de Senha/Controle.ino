#include <EEPROM.h>

typedef struct{
    int ID, senha;
} Usuario usuario[10];

int L[5] = {},
    C[6] = {},
    cont = 0,
    digito;
byte secao = 0;

void setup(){
   for(byte a = 0; a < 5; a++){
      digitalWrite(L[a], INPUT_PULLUP);
      digitalWrite(C[a], OUTPUT);
   }
   digitalWrite(C[5], OUTPUT);
   for(byte b = 0; b < 10; b++){
      for(byte c = 0; c < 2; c++){
         usuario[b].ID = EEPROM.read((4*b)+c);
         usuario[b].senha = EEPROM.read((4*b)+c+2);
      }
   }
}

void loop(){
   teclado();
}

void teclado(){
   for(byte d = 0; d < 6; d++){
      digitalWrite(C[0], HIGH); digitalWrite(C[1], HIGH);
      digitalWrite(C[2], HIGH); digitalWrite(C[3], HIGH);
      digitalWrite(C[4], HIGH); digitalWrite(C[5], HIGH);
      digitalWrite(C[d], LOW);
      if(digitalRead(L[0]) == LOW){
         switch (d){
            case 0: numero(1); break;
            case 1: numero(2); break;
            case 2: numero(3); break;
         }
         while(digitalRead(L[0]) == LOW);
      }
      if(digitalRead(L[1]) == LOW){
         switch (d){
            case 0: numero(4); break;
            case 1: numero(5); break;
            case 2: numero(6); break;
         }
         while(digitalRead(L[1]) == LOW);
      }
      if(digitalRead(L[2]) == LOW){
         switch (d){
            case 0: numero(7); break;
            case 2: numero(9);break;
            case 3: numero(8);break;
         }
         while(digitalRead(L[2]) == LOW);
      }
      if(digitalRead(L[3]) == LOW){
         switch (d){
            case 3: numero(0); break;
         }
         while(digitalRead(L[3]) == LOW);
      }
      if(digitalRead(L[4]) == LOW){
         switch (d){
            case 4: comando('#'); break;
            case 5: comando('*'); break;
         }
         while(digitalRead(L[4]) == LOW);
      }
   }
}

void numero(int valor){
   if(cont > 4) return;
   digito = digito*10;
   digito += valor;
}

void comando(char valor){
   if(valor == '#') digito = digito/10;
   if(valor == '*');
}

bool validacao(){
   if(secao){
      if(usuario[secao - 1].senha == digito) return true;
      else return false;
   }
   else{
      for(byte e = 0; e < 10; e++){
         if(usuario[e].ID == digito) break;
      }
      if(e == 10) return false;
      else{
         secao = e+1;
         return true;
      }
}
