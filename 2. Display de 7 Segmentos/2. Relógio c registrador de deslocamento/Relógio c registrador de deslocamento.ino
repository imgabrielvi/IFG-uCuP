#define SRCLR 9
#define RCLK 10 
#define OE 11
#define SER 12
#define SRCLK 13
#define Led 8

int display[4] = {A3, A2, A1, A0}, cont[4];
unsigned long tempo, tempo1;
bool state = HIGH;
byte digito[10][8]  = { {1,1,0,0,0,0,0,0},    // 0
                        {1,1,1,1,1,0,0,1},    // 1
                        {1,0,1,0,0,1,0,0},    // 2
                        {1,0,1,1,0,0,0,0},    // 3
                        {1,0,0,1,1,0,0,1},    // 4
                        {1,0,0,1,0,0,1,0},    // 5
                        {1,0,0,0,0,0,1,0},    // 6
                        {1,1,1,1,1,0,0,0},    // 7
                        {1,0,0,0,0,0,0,0},    // 8
                        {1,0,0,1,0,0,0,0} };  // 9

void setup(){
    /*Pinos do registrador de deslocamento*/
        pinMode(SRCLR, OUTPUT); pinMode(RCLK, OUTPUT);
        pinMode(OE, OUTPUT); pinMode(SER, OUTPUT);
        pinMode(SRCLK, OUTPUT);
    
    /*Pino dos LEDs*/
    pinMode(Led, OUTPUT);
    /*Inicialização*/
        digitalWrite(OE, LOW); digitalWrite(SRCLK, LOW);
        delay(2); digitalWrite(SRCLR, HIGH); 
        tempo, tempo1 = millis();
        for(byte x = 0; x < 4; x++){
            pinMode(display[x], OUTPUT); cont[x] = 5;
        }
}

void loop(){
    for(byte i = 0; i < 4; i++){
        desloca(cont[3-i]);
        digitalWrite(display[i], HIGH);
        delayMicroseconds(4900);
        digitalWrite(display[i], LOW);
    }
    if(millis() - tempo > 150){
        cont[3]++;                        	  // unidade de segundos
        if(cont[3] > 9){
            cont[3] = 0; cont[2]++;			      // dezena de segundos
            if(cont[2] > 5){
                cont[2] = 0; cont[1]++;			  // unidade de minutos
                if(cont[1] > 9){
                    cont[1] = 0; cont[0]++;		// dezena de minutos
                    if(cont[0] > 5){				
                        cont[0] = 0;
                    }
                }
            }
        }
        tempo = millis();
    }
    if(millis() - tempo1 > 300){
        state = !state;
        digitalWrite(Led, state);
        tempo1 = millis();
    }
}

void clock(byte pin){
    digitalWrite(pin, LOW); delay(2);
    digitalWrite(pin, HIGH);
}

void desloca(byte sinal){
    for(byte x = 0; x < 8; x++){
        digitalWrite(SER, digito[sinal][x]);
        clock(SRCLK);
    }
    clock(RCLK);
}
