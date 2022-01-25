// Name the analog pins for measuring photodiode
int sensorPin[] = {A0,A1,A2,A3,A4};
int sensorVal[30] = {};
// Name of arduino that RasPi "asks for"
String unitName = "photoOne";
String endCommand = "stop";

void setup() {
  // Set up serial ports and initialize analog pins
  Serial.begin(9600);
  for (int i = 0; i < 5; i++) {
    pinMode(sensorPin[i], INPUT);
  }
  
}

void loop() {
  // wait for serial input from RasPi, breaks loop on first high bit read
  while (!Serial.available()){}
  
  String command = Serial.readStringUntil('\n');
  // Above line gets which arduino raspi is asking for (stops read on newline)
  
  // Read analog pin for 
  if (command == unitName) {
    // 
    for (int pin = 0; pin < 5; pin++) {
      // take 30 measurements on analog pin and add to voltageArray
      for (int j = 0; j < 30; j++) {
        sensorVal[j] = analogRead(pin);
      }
      // Send the pin number over serial to RasPi
      Serial.println(sensorPin[pin]);
      // Send each photodiode reading value independently (as ints)
      for (int j = 0; j < 30; j ++) {
        Serial.print(String(sensorVal[j]));
      }
      Serial.println();
    }
  }
}