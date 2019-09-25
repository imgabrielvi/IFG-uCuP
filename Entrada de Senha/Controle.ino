#include <EEPROM.h>
#include <LiquidCrystal.h>
#define LED_VD 1
#define LED_VM 0

LiquidCrystal lcd(A1, A0, A2, A3, A4, A5);

typedef struct{
    int ID, senha;
} Usuario;

Usuario usuario[10];

int L[6] = {8, 10, 11, 5, 4/*Pinos, em ordem, das linhas do teclado.*/},
    C[7] = {7, 9, 12, 6, 3, 2/*Pinos, em ordem, das colunas do teclado.*/},
    digito = 0, ID1, senha1;
unsigned long tempo, tempo1;
byte cont = 0, secao = 1, selo = 0, selo1 = 0,
     validar = 0, cadastrar = 0;
bool confirma;

bool validacao(){
   if(selo){
      if(usuario[selo - 1].senha == digito){
        selo = 0;
        return 1;
      }
      else return 0;
   }
   else{
      byte e;
      for(e = 0; e < 10; e++){
         if(usuario[e].ID == digito) break;
      }
      if(e == 10) return 0;
      else{
         selo = e+1;
         return 1;
      }
   }
}

void teclado(void); void numero(int valor);
void comando(char valor1); void salvar(void);
void sinaliza(int pin); void tecladoserial(void);

void setup(){
    tempo = millis(); tempo1 = millis();
    lcd.begin(16,2);
    lcd.clear(); Serial.begin(9600);
   for(byte a = 0; a < 5; a++){
      pinMode(L[a], INPUT_PULLUP);
      pinMode(C[a], OUTPUT);
   }
   pinMode(C[5], OUTPUT);
   for(byte b = 0; b < 10; b++){
    usuario[b].ID = EEPROM.read((4*b));
    usuario[b].ID = EEPROM.read((4*b)+1) + (usuario[b].ID)*100;        
    usuario[b].senha = EEPROM.read((4*b)+2);
    usuario[b].senha = EEPROM.read((4*b)+3) + (usuario[b].senha)*100; 
    Serial.print(usuario[b].ID); Serial.print(" - ");
    Serial.println(usuario[b].senha);
   }
}

void salvar(){
  for(byte b = 0; b < 10; b++){
    EEPROM.update(((4*b)), (usuario[b].ID)/100);
    EEPROM.update(((4*b)+1), (usuario[b].ID)%100);
    EEPROM.update(((4*b)+2), (usuario[b].senha)/100);
    EEPROM.update(((4*b)+3), (usuario[b].senha)%100);
    if(millis()-tempo1 > 1000){
      if(b==9) tempo1 = millis();
      Serial.print(usuario[b].ID); Serial.print(" - ");
      Serial.println(usuario[b].senha); Serial.println();
    }
   }
}

void loop(){
   teclado();
   confirma = validacao();  //Serial.println(confirma);
   sinaliza('*'); salvar(); lcd.home();
   switch(secao){
     case 1: lcd.print("* - Cadastro."); lcd.setCursor(0,1);
             lcd.print("# - Validacao."); break;
     case 2: if(cadastrar) lcd.print("Cadastrar: "); 
             else lcd.print("Validacao: ");
             lcd.setCursor(0,1);
             lcd.print("Digite ID: "); lcd.print(digito); 
             lcd.print("     "); break;
     case 3: if(cadastrar) lcd.print("Cadastrar: "); 
             else lcd.print("Validacao: ");
             lcd.setCursor(0,1);
             lcd.print("Senha: "); lcd.print(digito); 
             lcd.print("     "); break;
     case 4: lcd.print("Confirmar senha:");
             lcd.setCursor(0,1);
             lcd.print("Senha: "); lcd.print(digito);
             lcd.print("     "); break;
   }
   tecladoserial();
}

void sinaliza(int pin){
    if(pin == '*'){
        if((millis() - tempo) > 1000){
            digitalWrite(LED_VM, LOW);
            digitalWrite(LED_VD, LOW);
        }
    }
    else{
      digitalWrite(pin, HIGH);
      tempo = millis();
    }
}

void teclado(){
   for(byte d = 0; d < 6; d++){
      digitalWrite(C[0], HIGH); digitalWrite(C[1], HIGH);
      digitalWrite(C[2], HIGH); digitalWrite(C[3], HIGH);
      digitalWrite(C[4], HIGH); digitalWrite(C[5], HIGH);
      digitalWrite(C[d], LOW);
      if(digitalRead(L[0]) == LOW){
         switch (d){
            case 0: comando('#'); break;
            case 1: numero(0); break;
            case 2: comando('*'); break;
         }
         while(digitalRead(L[0]) == LOW);
      }
      if(digitalRead(L[1]) == LOW){
         switch (d){
            case 0: numero(9); break;
            case 1: numero(8); break;
            case 2: numero(7); break;
         }
         while(digitalRead(L[1]) == LOW);
      }
      if(digitalRead(L[2]) == LOW){
         switch (d){
            case 0: numero(6); break;
            case 2: numero(4);break;
            case 3: numero(5);break;
         }
         while(digitalRead(L[2]) == LOW);
      }
      if(digitalRead(L[3]) == LOW){
         switch (d){
            case 3: numero(2); break;
         }
         while(digitalRead(L[3]) == LOW);
      }
      if(digitalRead(L[4]) == LOW){
         switch (d){
            case 4: numero(3); break;
            case 5: numero(1); break;
         }
         while(digitalRead(L[4]) == LOW);
      }
   }
}

void numero(int valor){
   if(cont == 4) return;
   digito = valor + digito*10;
   cont++;
}

void comando(char valor1){
   if(valor1 == '#'){ lcd.clear();
       switch(secao){
           case 1:  validar++; secao++; digito = 0; selo = 0; cont = 0;break;
           case 2:  if(validar){
                      if(confirma){
                        secao++;
                        digito = 0; cont = 0;
                      }
                      else{
                          digito = 0; cont = 0;
                          sinaliza(LED_VM);
                      }
                    }
                    if(cadastrar){
                      if(confirma){
                        secao = 1; selo = 0; cont = 0;
                        digito = 0; sinaliza(LED_VM);
                      }
                      else{
                        selo = 0; cont = 0;
                        int f = digito;
                        digito = 2525;
                        if(validacao()){
                          ID1 = f; selo1 = selo;
                          secao++;
                        }
                        digito = 0;
                      }
                    } break;
           case 3:  if(validar){
                      if(confirma){
                        secao = 1; cont = 0;
                        digito = 0;
                      }
                      else{
                        secao = 1;
                        digito = 0; cont = 0;
                        sinaliza(LED_VM);
                      }
                    }
                    if(cadastrar){
                      senha1 = digito;
                      digito = 0; cont = 0; secao++;
                    } break;
          case 4: if(digito == senha1){Serial.print("Senha correta");
                    secao = 1; cont = 0;
                    digito = 0;
                    selo = 0;
                    sinaliza(LED_VD);
                    cadastrar = 0;
                    usuario[selo1 - 1].ID = ID1;
                    usuario[selo1 - 1].senha = senha1;
                } 
              else{                                           Serial.println("Senha incorreta"); Serial.print(ID1); Serial.print(" "); Serial.print(senha1); Serial.print(" "); Serial.println(digito);
                    secao = 1; cont = 0;
                    digito = 0;
                    selo = 0;
                    sinaliza(LED_VM);
                        cadastrar = 0;
                    } break;
       }
   }
   if(valor1 == '*'){ lcd.clear();
       switch(secao){
           case 1:  cadastrar++; secao++; break;
           default: if(digito){
                      digito = digito/10; cont--;
                    }
                    else{
                      secao = 1;
                      validar = 0;
                      cadastrar = 0;
                    }break;
       }
   }
}

void tecladoserial(){
  if(Serial.available()){
    char val = Serial.read();
    if(val == '#') comando('#');
    if(val == '*') comando('*');
    if(isDigit(val)) numero(val-48);
  }
}
