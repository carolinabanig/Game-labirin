#include <AccelStepper.h>
#include <max6675.h>
#define EN  2
#define CW  3
#define CLK 4
#define POT A0
int thermoDO = 10;
int thermoCS = 9;
int thermoCLK = 8;
const int PINA0 = A0;
const int PINA1 = A1;
const int PINA2 = A2;
const int PINA3 = A3;
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
int vccPin = 3;
int gndPin = 2;
AccelStepper stepper(1, CLK, CW);

int vel, val;
String inString = "";    // string to hold input
void setup() {
  Serial.begin(9600);
  // use Arduino pins
  pinMode(vccPin, OUTPUT); digitalWrite(vccPin, HIGH);
  pinMode(gndPin, OUTPUT); digitalWrite(gndPin, LOW);
  pinMode(PINA0, OUTPUT);// set pin 10 as output for thermocouple1
  pinMode(PINA1, OUTPUT);// set pin 10 as output for thermocouple1
  pinMode(PINA2, OUTPUT);// set pin 10 as output for thermocouple1
  pinMode(PINA3, OUTPUT);// set pin 10 as output for thermocouple1
    pinMode(EN, OUTPUT);
     stepper.setMaxSpeed(5000);
  Serial.println("Robojax: MAX6675 test");
  // wait for MAX chip to stabilize
}
void loop() {
  // basic readout test, just print the current temp
  // Robojax.com MAX6675 Temperature reading on Serial monitor
  Serial.print("C = ");
  Serial.print(thermocouple.readCelsius());
  hidup();
  motor();

  delay(500);
}
void hidup() {
  if (thermocouple.readCelsius() < 60.00) {
    digitalWrite(PINA0, LOW);
    digitalWrite(PINA1, LOW);
    digitalWrite(PINA2, LOW);
    digitalWrite(PINA3, LOW);

  }
  else {
    if (thermocouple.readCelsius() > 60.00) {
    digitalWrite(PINA0, HIGH);
    digitalWrite(PINA1, LOW);
    digitalWrite(PINA2, LOW);
    digitalWrite(PINA3, HIGH);


    }
    delay(10000);
  }
}
void motor()
{
  digitalWrite(EN, HIGH);
  //////////////////////////////////////////////////////
  while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
    }
    // if you get a newline, print the string, then the string's value:
    if (inChar == '\n') {
      val = inString.toInt();
      Serial.print("Value:");
      Serial.println(val);
      // clear the string for new input:
      inString = "";
    }
  }
  //////////////////////////////////////////////////////
  stepper.setSpeed(val);
//  vel = map(analogRead(POT), 0, 1024, 0, 1000);
//  stepper.setSpeed(vel);
  stepper.runSpeed();
}
