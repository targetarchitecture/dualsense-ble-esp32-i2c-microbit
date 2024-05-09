

void setup_i2c() {

  Wire.begin(121);                 // Join I2C bus as the slave with address 1
  Wire.onReceive(performCommand);  // When the data transmition is detected call receiveEvent function
  Wire.onRequest(SendData);

  pinMode(LED_BUILTIN, OUTPUT);  // Sets the DO_Blink as output
}

String requestDataFromMicrobit;

/*Function/Event call****************************************************************************/
void performCommand(int howMany) {

  String command;

  while (Wire.available()) {
    char c = Wire.read();
    Serial.print(c);
    command.concat(c);
  }

  Serial.println("performCommand");

  if (command.startsWith("TEST:1")) {
    digitalWrite(LED_BUILTIN, HIGH);  // Sets the LAD On
  } else if (command.startsWith("TEST:0")) {
    digitalWrite(LED_BUILTIN, LOW);  // Sets the LAD Off
  } else if (command.startsWith("RUMBLE")) {
    playDualRumble();  //Perform controller rumble
  } else if (command.startsWith("LED:")) {
    String strLed = command.substring(3);
  Serial.println("strLed:" + strLed);
    setPlayerLEDs(1);  //Turn on the 4 LED. Each bit represents one LED.
  } else {
    requestDataFromMicrobit = command;
    Serial.print("requestDataFromMicrobit:");
    Serial.println(command);
  }
}

void SendData() {
  char txt[32];  // respond with message of 32 bytes (the max wire.h supports)

  int j = snprintf(txt, sizeof txt, "You want: %s\n", requestDataFromMicrobit);

  Serial.println(txt);
  Wire.write(txt);
}
