

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

    int Led;

    sscanf(command.c_str(), "LED:%d", &Led);

    Serial.print("setPlayerLEDs:");
    Serial.print(Led);
    Serial.println("");

    setPlayerLEDs(Led);  //Turn on the 4 LED. Each bit represents one LED.

  } else if (command.startsWith("COLOUR:")) {

    uint8_t r, g, b;

    sscanf(command.c_str(), "COLOUR:%d,%d,%d", &r, &g, &b);

    Serial.print("COLOUR:");
    Serial.print(r);
    Serial.print(",");
    Serial.print(g);
    Serial.print(",");
    Serial.print(b);
    Serial.println("");

    setColourLED(r, g, b);  //Turn on the colour LEDs
    
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
