#include <Keypad.h>

const byte rows = 4;
const byte cols = 3;

int wrong =0;  // 비밀번호 관련 변수
int turnin = 0;

int speakerPin = 3;     //부저 관련 변수들
int numTones = 8;
int tones[] = {261, 277, 294, 311, 330, 349, 370, 392};

byte rowPins[rows] = { 8, 7, 6, 5 }; //키패드 관련
byte colPins[cols] = { 9, 10, 11 };

char password[4] = {'0','0','0','0'};
char changepass[4];

int inputPin = 2; // pir 센서 신호핀

char keys[rows][cols] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};

int ledInput = 13;

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

void setup() {
// put your setup code here, to run once:
Serial.begin(9600);
pinMode(ledInput, OUTPUT);
setLocked(1);
}

int setLocked(int locked){ // 잠금시와 해제시에 맞는 LED를 세팅해 주는 함수
if(locked) {
digitalWrite(ledInput,HIGH);
return 1;
}

else digitalWrite(ledInput,LOW);

return 0;
}

void blink(int a){
for(int i=0; i<a; i++){
digitalWrite(ledInput,HIGH);
delay(500);
digitalWrite(ledInput,LOW);
delay(500);
}
}

void loop() {
char key = keypad.getKey();
int val = digitalRead(inputPin);
int a = setLocked(1);
if(key){
Serial.println(key);
}
if(val && a){
blink(wrong);
for(int i = 0; i < numTones; i++){
tone(speakerPin, tones[i]);
delay(500);
}
noTone(speakerPin);
delay(1000);
}

if ((key>='0' && key <='9')|| (key == '*' )){      //키값이 눌렀는지 확인문
if(key == "*"){
tone(speakerPin, tones[0]);
noTone(speakerPin);
turnin =0;
wrong = 0;
setLocked(1);
}


else if(key == password[turnin]){
  tone(speakerPin, tones[0]);
  noTone(speakerPin);
  turnin++;
  wrong =0;
}

else if(key != password[turnin]){
  tone(speakerPin, tones[0]);
  noTone(speakerPin);
  turnin = 0;
  setLocked(1);
  wrong++;
  blink(wrong);
}



}

if(turnin ==4){
setLocked(0);
digitalWrite(ledInput,LOW);

if(key == '#'){ // 비밀번호 변경
tone(speakerPin, tones[0]);
noTone(speakerPin);
keypad.setHoldTime(2000); // 키패드 2초동안 기다림


for(int i=0; i<4; i++){
  changepass[i]=key;
  password[i] = changepass[i];
}
}}

if(wrong == 4){
for(int i = 0; i < numTones; i++){
tone(speakerPin, tones[i]);
blink(wrong);
delay(500);
}

noTone(speakerPin);
delay(1000);
wrong = 0;
}
}
