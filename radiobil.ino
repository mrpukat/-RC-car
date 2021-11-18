#include <Servo.h>

Servo servoStering;
#define ServoPin 10

#define enablePin 11
#define controllpin1 8
#define controllpin2 7

int servoFrount =  75;
int servoRight = 100;
int servoLeft = 40;

int inputState = '.';
String motorState = "stop";
String diraction = "netral";
String prevderation = "none";
int inputSpeed = 4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  while (!Serial) {delay(10);}

  pinMode(enablePin, OUTPUT);
  pinMode(controllpin1, OUTPUT);
  pinMode(controllpin2, OUTPUT);

  servoStering.attach(ServoPin);
  delay(10);
  if (servoStering.attached()) { servoStering.write(servoFrount);}

  Serial.println("connected");
  Serial.println("State: " + motorState + " Speed: " + inputSpeed + " diraction: " + diraction);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0) {

    inputState = Serial.read();

    //Serial.println(inputState); // Utput garbige
    
    if ((inputState == 's') or (inputState == 'S')) {motorState = "stop";}
    if ((inputState == 'b') or (inputState == 'B')) {motorState = "back";}
    if ((inputState == 'f') or (inputState == 'F')) {motorState = "forward";}
      
    if ((inputState == 'n') or (inputState == 'N')) {diraction = "netral";}
    if ((inputState == 'l') or (inputState == 'L')) {diraction = "left";}
    if ((inputState == 'r') or (inputState == 'R')) {diraction = "right";}

    if (inputState == '0') {inputSpeed = 0;}
    if (inputState == '1') {inputSpeed = 4;}
    if (inputState == '2') {inputSpeed = 5;}
    if (inputState == '3') {inputSpeed = 6;}
    if (inputState == '4') {inputSpeed = 7;}
    
    Serial.println("State: " + motorState + " Speed: " + inputSpeed + " diraction: " + diraction);
  }

  int realSpeed = map(inputSpeed,0,9,0,255);

  if (motorState == "stop") {realSpeed = 0;}

  analogWrite(enablePin, realSpeed); // Dose nor workd voltage is always 0 at the pin; setting realspeed to an static var dose not help

  if (motorState == "forward") {
    digitalWrite(controllpin1, HIGH);
    digitalWrite(controllpin2, LOW);
  }
  else if (motorState == "back") {
    digitalWrite(controllpin1, LOW);
    digitalWrite(controllpin2, HIGH);
  }
  
  if (servoStering.attached() and prevderation != diraction) {
    if (diraction == "netral") {
      servoStering.write(servoFrount);
      //delay(300);
    }
    else if (diraction == "left") {
      servoStering.write(servoLeft);
      //delay(300);
    }
    else if (diraction == "right") {
      servoStering.write(servoRight);
      //delay(300);
    }
    prevderation = diraction;
  }

  delay(100);
}
