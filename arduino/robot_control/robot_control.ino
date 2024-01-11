#include <Servo.h>

Servo motorA, motorB, motorC, motorD;

void setup() {
  Serial.begin(9600); // To start serial communication
  // Attaching the servo motors to their respective pins
  motorA.attach(9);
  motorB.attach(10);
  motorC.attach(11);
  motorD.attach(12);
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    executeCommand(command);
  }
}

void executeCommand(String command) {
  int spaceIndex = command.indexOf(' ');
  String action = command.substring(0, spaceIndex);
  int duration = command.substring(spaceIndex + 1).toInt();

  if (action == "moveForward") {
    moveForward(duration);
  } else if (action == "moveBackward") {
    moveBackward(duration);
  } else if (action == "moveLeft") {
    moveLeft(duration);
  } else if (action == "moveRight") {
    moveRight(duration);
  } else if (action == "emergencyStop") {
    emergencyStop();
  } else {
    Serial.println("Unknown command: " + command);
  }
}


void moveForward(int duration) {
  // To move forward, retract A and B, release C and D
  motorA.write(120); // Retract Motor A
  motorB.write(120); // Retract Motor B
  motorC.write(70);  // Release Motor C
  motorD.write(70);  // Release Motor D
  delay(duration);
  stopAllMotors();
  Serial.println("Moved forward for " + String(duration) + " milliseconds.");
}

void moveBackward(int duration) {
  // To move forward, retract A and B, release C and D
  motorA.write(70); // Release Motor A
  motorB.write(70); // Release Motor B
  motorC.write(110);  // Retract Motor C
  motorD.write(110);  // Retract Motor D
  delay(duration);
  stopAllMotors();
  Serial.println("Moved backward for " + String(duration) + " milliseconds.");
}

void moveLeft(int duration) {
  // To move forward, retract A and B, release C and D
  motorA.write(110); // Retract Motor A
  motorB.write(70); // Release Motor B
  motorC.write(110);  // Retract Motor C
  motorD.write(70);  // Release Motor D
  delay(duration); // moving for duration ms
  stopAllMotors();
  Serial.println("Moved left for " + String(duration) + " milliseconds.");
}

void moveRight(int duration) {
  motorA.write(70); // Retract Motor A
  motorB.write(110); // Release Motor B
  motorC.write(70);  // Retract Motor C
  motorD.write(110);  // Release Motor D
  delay(duration);
  stopAllMotors();
  Serial.println("Moved right for " + String(duration) + " milliseconds.");
}


void moveAonly(int duration) {
  motorA.write(70); // Retract Motor A
  motorB.write(90); // Neutral Motor B
  motorC.write(90);  // Neutral Motor C
  motorD.write(90);  // Neutral Motor D
  delay(duration);
  stopAllMotors();
}

void moveBonly(int duration) {
  motorA.write(90); // Neutral Motor A
  motorB.write(95); // Retract Motor B
  motorC.write(90);  // Neutral Motor C
  motorD.write(90);  // Neutral Motor D
  delay(duration);
  stopAllMotors();
}

void moveConly(int duration) {
  motorA.write(90); // Neutral Motor A
  motorB.write(90); // Neutral Motor B
  motorC.write(110);  // Retract Motor C
  motorD.write(90);  // Neutral Motor D
  delay(duration);
  stopAllMotors();
}

void moveDonly(int duration) {
  motorA.write(90); // Neutral Motor A
  motorB.write(90); // Neutral Motor B
  motorC.write(90);  // Retract Motor C
  motorD.write(110);  // Neutral Motor D
  delay(duration);
  stopAllMotors();
  
}

void stopAllMotors() {
  // Stop all motors by setting them to their neutral position
  motorA.write(90); // Stop Motor A
  motorB.write(90); // Stop Motor B
  motorC.write(90); // Stop Motor C
  motorD.write(90); // Stop Motor D
}

void emergencyStop(){
  motorA.detach();  // Motor A at pin 9
  motorB.detach(); // Motor B at pin 10
  motorC.detach(); // Motor C at pin 11
  motorD.detach(); // Motor D at pin 12
  Serial.println("Emergency stop activated.");
}