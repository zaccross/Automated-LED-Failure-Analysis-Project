// Initialize vars
//Digital Switching pins
int ledPin[] = {9,10};
//resistor vals (Ohms)
int resistors[] = {100,1000,10000};
// Analog pins to read voltage over resistors
int analogPin = A0;
// input levels for duty cycle as a percentage
int dutyCycle[] = {50,75};
// name this arduino for the RasPi to ask for below
String unitName = "driver";
// Send this from Pi to arduino to enter infinite loop
String endCommand = "stop";


void setup() {
  // Set baud rate to match RasPi @ 9600
  Serial.begin(9600);
  // initialize pinModes
  for (int index = 0; index<2; index++) {
    pinMode(ledPin[index], OUTPUT);
  }
  // Test pin on arduino unit to check for working duty cycle - pin 13
  pinMode(13, OUTPUT);
}

// Set pins to appropriate duty cycles, wait for prompt from rasPi to give report
void loop() {
  // Turn on LEDs
  for (int index = 0; index < 2; index++){
    ledOn(ledPin[index],dutyCycle[index]);
  }
  // Turn on test pin 13
  analogWrite(13,200);
  // wait for HIGH signal from RasPi
  while (!Serial.available()){}
  
  String command = Serial.readStringUntil('\n');
  // Above line gets which arduino raspi is asking for

  // Read analog pin for resistor value and send pin no. with voltage drop over resistor
  if (command == unitName) {
    float current = 0;
    float currentArray[30] = {};
      // Read pins 1-5
      for (int i = 0; i < 1; i++) {
        // take 30 measurements on analog pin and add to voltageArray
        for (int j = 0; j < 30; j++) {
          current = currentFunc();
          currentArray[j] = current;
        }
        // Send the pin number over serial to RasPi
        Serial.println(String(i));
        // Send each voltage reading value independently (as floats)
        for (int i = 0; i < 30; i ++) {
          Serial.print(String(currentArray[i]));
        }
        Serial.print('\n');
      }
  }
  if (command == endCommand) {
    ledOff();
  }
}

/*
 Turn on pin at specced duty cycle
 Input pin number and PERCENTAGE to run at
 Return void
*/
void ledOn(int pinNum, int dutyCycle) {
  int runVal = dutyCycle * 255 / 100;
  analogWrite(pinNum,dutyCycle);
}


/*
  Returns current through 22 Ohm resistor
*/
float currentFunc() {
  int val = 0;
  float voltageRead = 0;
  val = analogRead(analogPin);
        voltageRead = val * (5.0/1023.0);
        return voltageRead/22;
}


/*
 LEDs off, wait infinitely
 Return void
 */
void ledOff() {
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  while (true) {;}
}
