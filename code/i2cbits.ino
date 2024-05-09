#include <Wire.h>

void setup_i2c() {

  Wire.begin(121);               // Join I2C bus as the slave with address 1
  Wire.onReceive(BlinkLED);      // When the data transmition is detected call receiveEvent function
  Wire.onRequest(SendData);

  pinMode(LED_BUILTIN, OUTPUT);  // Sets the DO_Blink as output

}

volatile char requestDataFromMicrobit;

/*Function/Event call****************************************************************************/
void BlinkLED(int howMany) {
  // byte I2C_OnOff = Wire.read();  // Reads the data sent via I2C

  int i = 0;
  char res[howMany] = "";

  while (Wire.available()) {
    char c = Wire.read();
    Serial.print(c);
    res[i] = c;
    i++;
  }

  Serial.println("BlinkLED");

  if (res[0] == '1') {
    digitalWrite(LED_BUILTIN, HIGH);  // Sets the LAD On
  } else if (res[0] == '0') {
    digitalWrite(LED_BUILTIN, LOW);  // Sets the LAD Off
  } else {
    requestDataFromMicrobit = res[0];
    Serial.print("requestDataFromMicrobit:");
    Serial.println(requestDataFromMicrobit);
  }
}

void SendData() {
  char txt[32];  // respond with message of 32 bytes (the max wire.h supports)

  int j = snprintf(txt, sizeof txt, "You want: %c\n", requestDataFromMicrobit);

  Serial.println(txt);
  Wire.write(txt);  
}
