/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogReadSerial
*/

String currentCommand = "";

void setup() {
  Serial.begin(9600);

  pinMode(2, INPUT);
}

void loop() {
  float xMovementThreshold = 0.2;
  float yMovementThreshold = 0.4;

  int leftSensorValue = analogRead(A3) - 200;
  int rightSensorValue = analogRead(A0);
  int clickState = digitalRead(2);

  float leftScaledValue = (leftSensorValue) / 1024.0;
  float rightScaledValue = rightSensorValue / 1024.0;

  //if (rightScaledValue > 0.05) {
  //  rightScaledValue = 5 * (1 - 1 / (1 + 0.1 * pow(rightScaledValue - 0.5, 2))) * rightScaledValue;
  //}


  float xMovement = rightScaledValue - leftScaledValue;
  float yMovement = rightScaledValue + leftScaledValue;

  String commandString = "";
  if (xMovement < -xMovementThreshold) {
    commandString += "-1";
  } else if (xMovement > xMovementThreshold) {
    commandString += "1";
  } else {
    commandString += "0";
  }

  commandString += " ";

  if (yMovement > yMovementThreshold) {
    commandString += "1";
  } else {
    commandString += "0";
  }

  commandString += " ";

  if (clickState == HIGH) { // Assuming clickThreshold is a fraction of 1024
    commandString += "1";
  } else {
    commandString += "0";
  }

  if (commandString != currentCommand) {
    currentCommand = commandString;
    Serial.println(currentCommand);
  }

  if (false) {
    Serial.print(leftSensorValue);

    Serial.print(" ");

    Serial.print(rightSensorValue);

    Serial.print(" ");

    Serial.print(clickState);

    Serial.println();
  }

  delay(100);
}
