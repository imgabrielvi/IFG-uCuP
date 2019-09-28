#include <LiquidCrystal.h>
#define button1 3  //Anterior
#define button2 4  //Proximo
#define button3 5  //Ajuste
#define button4 2  //Função

const int rs = 12, en = 11, rw = 10, d4 = 9, d5 = 8, d6 = 7, d7 = 6, p = 13 ;
LiquidCrystal lcd(rs, rw, en, d4, d5, d6, d7);
unsigned long changeTime, butTime, ajusteTime;
int cont[14], quad[14], funcao = 0, ajustar = 0,
    seg, min, hora, dia, mes, ano1, ano2, inicio, fim;

byte Ajuste, Funcao, Prox, Ant,
    C0[8] = {B11111, B11011, B11011, B11011, B11011, B11011, B11011, B11111},
    C1[8] = {B00011, B00011, B00011, B00011, B00011, B00011, B00011, B00011},
    C2[8] = {B11111, B11111, B00011, B00011, B00011, B00011, B11111, B11111},
    C3[8] = {B11111, B11111, B11000, B11000, B11000, B11000, B11111, B11111},
    C4[8] = {B11011, B11011, B11011, B11011, B11011, B11011, B11111, B11111},
    C5[8] = {B11111, B11111, B00011, B00011, B00011, B00011, B00011, B00011},
    C6[8] = {B00000, B00000, B00000, B01100, B01100, B00000, B00000, B00000},
    C7[8] = {B11111, B11111, B11011, B11011, B11011, B11011, B11011, B11011};

void numdigit(byte val, byte position){
  switch (val){
    case 0: lcd.setCursor(quad[position],0); lcd.write(byte(7));
    		lcd.setCursor(quad[position],1); lcd.write(byte(4)); break;
    case 1: lcd.setCursor(quad[position],0); lcd.write(byte(1));
    		lcd.setCursor(quad[position],1); lcd.write(byte(1)); break;
    case 2: lcd.setCursor(quad[position],0); lcd.write(byte(2));
    		lcd.setCursor(quad[position],1); lcd.write(byte(3)); break;
    case 3: lcd.setCursor(quad[position],0); lcd.write(byte(2));
    		lcd.setCursor(quad[position],1); lcd.write(byte(2)); break;
    case 4: lcd.setCursor(quad[position],0); lcd.write(byte(4));
    		lcd.setCursor(quad[position],1); lcd.write(byte(5)); break;
    case 5: lcd.setCursor(quad[position],0); lcd.write(byte(3));
    		lcd.setCursor(quad[position],1); lcd.write(byte(2)); break;
    case 6: lcd.setCursor(quad[position],0); lcd.write(byte(3));
    		lcd.setCursor(quad[position],1); lcd.write(byte(0)); break;
    case 7: lcd.setCursor(quad[position],0); lcd.write(byte(5));
    		lcd.setCursor(quad[position],1); lcd.write(byte(1)); break;
    case 8: lcd.setCursor(quad[position],0); lcd.write(byte(0));
    		lcd.setCursor(quad[position],1); lcd.write(byte(0)); break;
    case 9: lcd.setCursor(quad[position],0); lcd.write(byte(0));
    		lcd.setCursor(quad[position],1); lcd.write(byte(2)); break;
  }
  
}

void showNum(int inicio, int fim){
  for(byte x=inicio; x<fim; x++){
    numdigit(cont[x], x);
  }
}

void piscar(int position){
  if((millis() - ajusteTime > 400) && (millis() - ajusteTime < 600)){
    lcd.setCursor(quad[position],0); lcd.print(" "); lcd.setCursor(quad[position+1],0); lcd.print(" ");
    lcd.setCursor(quad[position],1); lcd.print(" "); lcd.setCursor(quad[position+1],1); lcd.print(" ");
  }
  else if(millis() - ajusteTime > 600){
    showNum(inicio,fim); ajusteTime = millis();
  }Serial.println(ajustar-2);
  Prox = digitalRead(button2);
  Ant = digitalRead(button1);
  if(!Prox && millis() - butTime > 300){
    butTime = millis();
    switch(funcao){
      case 1: switch(ajustar){
        		case 8: dia++; break;
        		case 10: mes++; break;
        		case 12: ano1++; break;
        		case 14: ano2++; break;
      		  } break;
      case 2: switch(ajustar){
        		case 2: seg++; break;
        		case 4: min++; break;
        		case 6: hora++; break;
      		  } break;
    }
  }
  if(!Ant && millis() - butTime > 300){
    butTime = millis();
    switch(funcao){
      case 1: switch(ajustar){
        		case 8: dia--; break;
        		case 10: mes--; break;
        		case 12: ano1--; break;
        		case 14: ano2--; break;
      		  } break;
      case 2: switch(ajustar){
        		case 2: seg--; break;
        		case 4: min--; break;
        		case 6: hora--; break;
      		  } break;
    }
  }
  contarTempo();
}

void data(){
  Ajuste = digitalRead(button3);
  if((!Ajuste) && (millis() - butTime > 500)){
    if(!ajustar) ajustar = 6;
    ajustar = ajustar + 2;
    if(ajustar > 16) ajustar = 0;
  }
  if(ajustar){
    piscar(ajustar - 2);
  }
  else showNum(inicio,fim);
  lcd.setCursor(p - 8,1); lcd.print("."); lcd.setCursor(p - 5,1); lcd.print(".");
}

void horario(){
  Ajuste = digitalRead(button3);
  if((!Ajuste) && (millis() - butTime > 500)){
    ajustar = ajustar + 2;
    if(ajustar > 6) ajustar = 0;
  }
  if(ajustar){
    piscar(ajustar-2);
  }
  else showNum(inicio,fim);
  lcd.setCursor(p - 2,0); lcd.write(byte(6)); lcd.setCursor(p - 2,1); lcd.write(byte(6));
  lcd.setCursor(p - 5,0); lcd.write(byte(6)); lcd.setCursor(p - 5,1); lcd.write(byte(6));
}

void contarTempo(){
  if((millis() - changeTime) > 1000){
    seg++; changeTime = millis();
  }
  if(seg > 59){seg = 0; min++;}
  if(min > 59){min = 0; hora++;}
  if(hora > 23){hora = 0; dia++;}
  if(dia > 30){dia = 1; mes++;}
  if(mes > 12){mes = 1; ano1++;}
  if(ano1 > 99){ano1 = 0; ano2++;}
  if(ano2 > 99)ano2 = 0;
  cont[0] = seg%10; cont[1] = seg/10; cont[2] = min%10;
  cont[3] = min/10; cont[4] = hora%10; cont[5] = hora/10;
  cont[6] = dia%10; cont[7] = dia/10; cont[8] = mes%10;
  cont[9] = mes/10; cont[10] = ano1%10; cont[11] = ano1/10;
  cont[12] = ano2%10; cont[13] = ano2/10;
}

void setup() {
  pinMode(rw, OUTPUT); digitalWrite(rw, LOW);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
  lcd.begin(16, 2); Serial.begin(9600);
  changeTime, butTime, ajusteTime = millis();
  lcd.createChar(0, C0); lcd.createChar(1, C1); lcd.createChar(2, C2); lcd.createChar(3, C3);
  lcd.createChar(4, C4); lcd.createChar(5, C5); lcd.createChar(6, C6); lcd.createChar(7, C7);
  quad[0] = 13; quad[1] = 12; quad[2] = 10; quad[3] = 9; quad[4] = 7;
  quad[5] = 6; quad[6] = 4; quad[7] = 3; quad[8] = 7; quad[9] = 6;
  quad[10] = 12; quad[11] = 11; quad[12] = 10; quad[13] = 9;
  seg = 0; min = 30; hora = 10; dia = 2; mes = 7;
  ano1 = 19; ano2 = 20;
}

void loop(){
  Funcao = digitalRead(button4);
  if((!Funcao) && (millis() - butTime > 300) && (!ajustar)){
    funcao++; Serial.print("Pulso. Função = ");
    if(funcao > 5) funcao = 0; Serial.println(funcao);
    lcd.clear();
  }
  switch(funcao){
    case 0: //Odômetro(99999km)
    		break;
    case 1: //Data(DD/MM/AAAA)
    		inicio = 6; fim = 14; data(); break;
    case 2: //Horário(HH:MM:SS)
    		inicio = 0; fim = 6; horario(); break;
    case 3: //Consumo(999l)
    		break;
    case 4: //Media(99,9km/l)
    		break;
    case 5: //Autonomia(999km)
    		break;
  }
  contarTempo();
}
