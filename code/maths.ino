


uint8_t calculateAxisHour(int32_t axisRX, int32_t axisRY) {

  //  Serial.print("calculateAxisHour:");
  //  Serial.print(axisRX);
  //  Serial.print(",");
  //  Serial.println(axisRY);

  const uint8_t deadzone = 40;

  // Apply deadzone to eliminate small movements
  if (abs(int(axisRX)) < deadzone) {
    axisRX = 0;
  }
  if (abs(int(axisRY)) < deadzone) {
    axisRY = 0;
  }

  if (axisRX == 0 && axisRY == 0) {
    return 0;  //in the deadzone on both axis
  } else {

    double atan2Value = atan2(axisRX, axisRY);

    int angle = floor(atan2Value * 180 / PI);

    if (angle < 0) {
      angle += 360;
    }

    //Serial.print("Angle:");
    //Serial.println(angle);

    // Convert rotated angle to hour format (1-12)
    int hourAngle = floor((angle / 30) % 12);  // Ensures 1-12 format

    if (hourAngle == 0) {
      hourAngle = 12;
    }

 //    Serial.print("Hour:");
 //  Serial.println(hourAngle);

    //  blah.innerHTML += "Hour:" + hourAngle + "<br>";
    return hourAngle;
  }
}
