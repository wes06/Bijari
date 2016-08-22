
const int c[] = {
  3, 5, 6, 9, 10, 11};//canais/pinos
int brightness[] = {
  0, 0, 0, 0, 0, 0}; //declara variaveis de brilho apagadas
volatile int animacao = 0; //animacao 0 = breath mais calmo
int lastCase = 3;//start com case diferente pra dar trigger no recomecar
boolean sentido[] = {
  true, true, true, true, true, true};
; //true == brightness++, start com brightness = 0

int respiradas = 0;

unsigned long lastWrite = 0;
//unsigned long writeInterval = 12000;

unsigned long lastBoom = 0;
unsigned long boomInterval = 1000000;

int explosao=0;

void setup() {
  for (int i = 0; i < 6; i++) {
    pinMode(c[i], OUTPUT);
  }
  //Serial.begin(9600);
  pinMode(2, INPUT_PULLUP); 
  attachInterrupt(1, buttonPressed, RISING); //pino 2
}

void loop() {
  if(explosao == 0){
    calc(animacao);
    writeBrightness();
  }
  else if(explosao == 1){
    //Serial.println("check2");
    pinoFade();
  }
  else if(explosao == 2){
    explode();
  }
 // delay(10);
}



void calc(int rotina) {
  switch (rotina) {
  case 0://fade in & out
    recomecarEm(0); // se veio de um case diferente
    breath(12000);
    lastCase = 0;
    break;

  case 1://boom
    recomecarEm(255); // se veio de um case diferente
    lastCase = 1;
    break;
  }

}




void writeBrightness() {
  for (int i = 0; i < 6; i++) {
    analogWrite(c[i], 255 - brightness[i]);
  }
}

void recomecarEm(int brightness) {
  if (lastCase != animacao) {
    for (int i = 0; i < 6; i++) {
      analogWrite(c[i], 255 - brightness);
    }
  }
}

int target[] = {
  250,250,250,250,250,250};
int soma[] = {
  1,1,1,1,1,1};
int a;

void explode(){
  for(int i =0;i<450;i++){
    digitalWrite(a = c[random(0,6)], LOW);
    digitalWrite(a = c[6-random(0,6)], LOW);
    delay(5);
    digitalWrite(a = c[6-random(0,6)], HIGH);
    digitalWrite(a = c[random(0,6)], HIGH);
  }
  explosao = 0;
}

void pinoFade(){
  
  for(int i = 0;i<256;i++){
    //Serial.print("pinoFade");
    analogWrite(11, i);
    delay(30);
  }
  digitalWrite(11, HIGH);
  delay(500);
      explosao = 2;
}



void breath(long freq){
  if (micros() - lastWrite > freq) {
    for (int i = 0; i < 6; i++) {
      if(explosao == 0){
        if(brightness[i] > 250 && sentido[i] == true){
          sentido[i] = false;
          if(respiradas > 40){
            explosao=1;
            respiradas = 0;
          }
          respiradas++;
        }
        else if(brightness[i] < 40 && sentido[i] == false){
          sentido[i] = true;
        }
        if (sentido[i]) {
          brightness[i]++;
        }
        else {
          brightness[i]--;
        }
      }
    }
    lastWrite = micros();
  }
}

void buttonPressed() {
  if(micros()-lastBoom > boomInterval){
    animacao++;
    animacao = animacao % 2;
    lastBoom = micros();
    //Serial.println(animacao);
  }
}




