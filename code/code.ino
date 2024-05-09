#include <Bluepad32.h>
#include <Wire.h>

void setup() {
  
  Serial.begin(115200);

  setup_i2c();

  setup_dualsense();

}

void loop() {

  // This call fetches all the controllers' data.
  loop_dualsense();

  delay(50);
}

