#include <Bluepad32.h>


ControllerPtr myControllers[BP32_MAX_GAMEPADS];

/*Setup loop************************************************************************************/
void setup() {
  
  Serial.begin(115200);

  setup_i2c();

  setup_dualsense();


}

/*Main loop**************************************************************************************/
void loop() {

  // This call fetches all the controllers' data.
  bool dataUpdated = BP32.update();
  if (dataUpdated)
    processControllers();

  delay(100);
}

