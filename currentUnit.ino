//resistor vals (Ohms)
int resistor = 22;
// Analog pins to read voltage over resistors
int analogPin[] = {A0,A1,A2,A3,A4};

// name this arduino for the RasPi to ask for below
String unitName = "current";
String endCommand = "stop";

void setup() {
   // Set baud rate to match RasPi @ 9600
  Serial.begin(9600);
}

/*
  Main body of code, loops until serial command sends "stop"
*/
void loop() {
  // wait for HIGH signal from RasPi
  while (!Serial.available()){}
  
  String command = Serial.readStringUntil('\n');
  // Above line gets which arduino raspi is asking for

  // Read analog pin for resistor value and send pin no. with current through resistor
  if (command == unitName) {
    float current = 0;
    float currentArray[30] = {};
      // Read pins 1-5
      for (int i = 0; i < 5; i++) {
        // take 30 measurements on analog pin and add to currentArray
        for (int j = 0; j < 30; j++) {
          current = currentFunc(i);
          currentArray[j] = current;
        }
        // Send the pin number over serial to RasPi
        Serial.println(String(i));
        // Send each voltage reading value independently (as floats), to 4 decimals
        for (int i = 0; i < 30; i ++) {
          Serial.print(String(currentArray[i]));
        }
        // Print newline after data is read over serial send (for each pin read)
        Serial.print('\n');
      }
  }
}

/*
  When called, takes pinNum for analog pin address 
  Returns current through resistor
*/
float currentFunc(int pinNum) {
  int val = 0;
  float voltageRead = 0;
  val = analogRead(analogPin[pinNum]);
        voltageRead = val * (5.0/1023.0);
        return voltageRead/resistors;
}
