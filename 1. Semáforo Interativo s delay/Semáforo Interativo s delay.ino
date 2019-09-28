#define carRed 12
#define carYellow 11
#define carGreen 10
#define pedRed 9
#define pedGreen 8
#define button 2
#define buzzer 3
#define crossTime 5
#define multTime 100
unsigned long changeTime;
bool state;

void setup() {
    /*Pinos dos LEDs dos carros*/
        pinMode(carRed, OUTPUT);
        pinMode(carYellow, OUTPUT); 
        pinMode(carGreen, OUTPUT);
    
    /*Pinos dos LEDs e da botoeira dos pedestres*/
        pinMode(pedRed, OUTPUT); 
        pinMode(pedGreen, OUTPUT);
        pinMode(button, INPUT_PULLUP);
    
    /*Inicialização*/
        digitalWrite(carGreen, HIGH); 
        digitalWrite(pedRed, HIGH); 
        changeTime = millis();
}

void loop() {
  state = digitalRead(button);
  if (state == LOW && (millis() - changeTime) > (2*multTime)) {
    changeLights();
  }
}

void changeLights() {
  long ChangeTime; changeTime = millis();
  do {
      digitalWrite(buzzer, HIGH);
  } while((millis() - changeTime) < (.5*multTime)); digitalWrite(buzzer, LOW);
  do {
      digitalWrite(carYellow, HIGH); digitalWrite(carGreen, LOW);
  } while((millis() - changeTime) < (2.5*multTime));
  do {
      digitalWrite(carYellow, LOW); digitalWrite(carRed, HIGH);
  } while((millis() - changeTime) < (3.5*multTime));
  do {
      digitalWrite(pedRed, LOW); digitalWrite(pedGreen, HIGH);
  } while((millis() - changeTime) < ((crossTime + 3.5)*multTime));
  digitalWrite(pedGreen, LOW);
  for(int x=0; x<3; x++) {
      ChangeTime = millis();
      do {
          digitalWrite(pedRed, HIGH);
      } while((millis() - ChangeTime) < (.25*multTime));
      do {
          digitalWrite(pedRed, LOW);
      } while((millis() - ChangeTime) < (.5*multTime));
  }
  digitalWrite(carGreen, HIGH);
  digitalWrite(pedRed, HIGH);
  digitalWrite(carRed, LOW);
  changeTime = millis();
}
