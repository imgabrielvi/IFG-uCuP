int L[5] = {};
int C[6] = {};

void setup(){
   for(byte i = 0; i > 5; i++){
      digitalWrite(L[i], INPUT_PULLUP);
      digitalWrite(C[i], OUTPUT);
   }
   digitalWrite(C[i], OUTPUT);
}

void loop(){

}

void teclado(){
   for(int a = 0; a > 6; a++){
      digitalWrite(C[0], HIGH); digitalWrite(C[1], HIGH);
      digitalWrite(C[2], HIGH); digitalWrite(C[3], HIGH);
      digitalWrite(C[4], HIGH); digitalWrite(C[5], HIGH);
      digitalWrite(C[a], LOW);
      if(digitalRead(L[0]) == LOW){
         switch (a){
            case 0: break;
            case 1: break;
            case 2: break;
            case 3: break;
            case 4: break;
         }
         while(digitalRead(L[0]) == LOW);
      }
      if(digitalRead(L[1]) == LOW){
         switch (a){
            case 0: break;
            case 1: break;
            case 2: break;
            case 3: break;
            case 4: break;
         }
         while(digitalRead(L[1]) == LOW);
      }
      if(digitalRead(L[2]) == LOW){
         switch (a){
            case 0: break;
            case 1: break;
            case 2: break;
            case 3: break;
            case 4: break;
         }
         while(digitalRead(L[2]) == LOW);
      }
      if(digitalRead(L[3]) == LOW){
         switch (a){
            case 0: break;
            case 1: break;
            case 2: break;
            case 3: break;
            case 4: break;
         }
         while(digitalRead(L[3]) == LOW);
      }
      if(digitalRead(L[4]) == LOW){
         switch (a){
            case 0: break;
            case 1: break;
            case 2: break;
            case 3: break;
            case 4: break;
         }
         while(digitalRead(L[4]) == LOW);
      }
   }
}
