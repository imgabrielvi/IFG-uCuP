#include <EEPROM.h>
#include <LiquidCrystal.h>
#define chave 9

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

typedef struct{
    int ID, senha;
} Usuario;

Usuario usuario[10];

int L[5] = {/*Pinos, em ordem, das linhas do teclado.*/},
    C[6] = {/*Pinos, em ordem, das colunas do teclado.*/},
    digito = 0;
byte cont = 0, secao = 1, selo = 0,
     validar = 0, cadastrar = 0;
bool confirma, estado = LOW;

bool validacao(){
   if(selo){
      if(usuario[selo - 1].senha == digito) return true;
      else return false;
   }
   else{
      byte e;
      for(e = 0; e < 10; e++){
         if(usuario[e].ID == digito) break;
      }
      if(e == 10) return false;
      else{
         selo = e+1;
         return true;
      }
   }
}

void teclado(void); void numero(int valor);
void comando(char valor1); void cadastro(void);

void setup(){
   for(byte a = 0; a < 5; a++){
      pinMode(L[a], INPUT_PULLUP);
      pinMode(C[a], OUTPUT);
   }
   pinMode(C[5], OUTPUT); pinMode(chave, OUTPUT); 
   for(byte b = 0; b < 10; b++){
      for(byte c = 0; c < 2; c++){
         usuario[b].ID = EEPROM.read((4*b)+c);
         usuario[b].senha = EEPROM.read((4*b)+c+2);
      }
   }
}

void loop(){
   teclado(); digitalWrite(chave, estado);
   if(validar){
       confirma = validacao();
   }
   else if(cadastrar) cadastro();
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
   if(cont = 4) return;
   digito = valor + digito*10;
   cont++;
}

void comando(char valor1){
   if(valor1 == '#'){
       switch(secao){
           case 1:  validar++; secao++; break;
           case 2:  if(confirma) secao++;
                    else digito = 0; break;
           case 3:  if(confirma){
                        secao++;
                        estado = !estado;
                    }
                    else digito = 0; break;
       }
   }
   if(valor1 == '*'){
       switch(secao){
           case 1:  cadastrar++; secao++; break;
           default: digito = digito/10; break;
       }
   }
}

void cadastro(){
    byte f;
    switch(secao){
        case 2: for(f = 0; f < 10; f++){
                    if(!usuario[f].ID) break;
                }
                if(f != 10 && cont >= 4){
                    usuario[f].ID == digito;
                    secao++; cont = 0;
                } break;
        case 3: if(cont >= 4){
                    usuario[f].senha = digito; 
                    secao++; cont = 0; 
                } break;
        case 4: if(cont >= 4 && usuario[f].senha == digito){
                    secao = 1; cont = 0;
                } 
                else{
                    usuario[f].senha = 0; secao--; cont = 0;
                } break;
                    
    }
}
