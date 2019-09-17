int L[5];
int C[6];

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
   digitalWrite(B[1],HIGH); digitalWrite(B[4],HIGH);
   digitalWrite(B[5],HIGH); digitalWrite(B[7],HIGH);
   digitalWrite(B[10],HIGH);
}
