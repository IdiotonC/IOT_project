#include <Keypad.h>

const byte rows = 4;
const byte cols = 3;

int wrong =0;  // 비밀번호 관련 변수
int turnin = 0;

int speakerPin = 8;     //부저 관련 변수들
int numTones = 8;
int tones[] = {261, 277, 294, 311, 330, 349, 370, 392};

byte rowPins[ROWS] = { 9, 8, 7, 6 }; //키패드 관련
byte colPins[COLS] = { 5, 4, 3 };

int password[4] = {0000};
int changepass[4];

int inputpin = 0; // pir 센서 신호핀

char keys[rows][cols] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};

int led1;

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

void setup() {
// put your setup code here, to run once:
Serial.begin(9600);
pinMode(led1, OUTPUT);
setLocked(true);
}

void loop() {
char key = keypad.getKey();
val = digitalRead(inputPin);
int a = setLocked;
if(val && a ==0){
  for(int i = 0; i < numTones; i++)
{
tone(speakerPin, tones[i]);
blink();
delay(500);
}
noTone(speakerPin);
delay(1000);
}

if ((key>='0' && key <='9')|| (key == '*' )){      //키값이 눌렀는지 확인문
if(key == "*"){
turnin =0;
wrong = 0;
setLocked(true);
}
else if(key == password[turnin]){
turnin++;
wrong =0;
}
else if(key != password[turnin]){
turnin = 0;
setLocked(true);
wrong++;
blink(wrong);
}}
else if(key == '#'){ // 비밀번호 변경
for(int i=0; i<4; i++){
changepass[i]=key;
password[i] = changepass[i];
}
return 0;
}


if(turnin ==4){
setLocked(false);
digitalWrite(led1,LOW);
}

if(wrong == 4){
for(int i = 0; i < numTones; i++)
{
tone(speakerPin, tones[i]);
blink();
delay(500);
}
noTone(speakerPin);
delay(1000);
wrong = 0;
}



int setLocked(int locked){ // 잠금시와 해제시에 맞는 LED를 세팅해 주는 함수
if(locked) { 
digitalWrite(led1,HIGH);
return 1;
}
else digitalWrite(led1,LOW);
return 0;
}

void blink(int a){
for(int i=0; i<a; i++){
digitalWrite(led1,HIGH);
delay(500);
digitalWrite(led1,LOW);
delay(500);
}
}

}
