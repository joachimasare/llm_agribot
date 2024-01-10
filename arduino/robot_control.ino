#include <Servo.h>

Servo motorA, motorB, motorC, motorD;

void setup() {
  Serial.begin(9600); // Start serial communication
  // Attach the servo motors to their respective pins
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
  if (command == "moveForward") {
    moveForward();
  } else if (command == "moveBackward") {
    moveBackward();
  } else if (command == "moveLeft") {
    moveLeft();
  } else if (command == "moveRight") {
    moveRight();
  } else if (command == "moveAonly") {
    moveAonly();
  } else if (command == "moveBonly") {
    moveBonly();
  } else if (command == "moveConly") {
    moveConly();
  } else if (command == "moveDonly") {
    moveDonly();
  } else if (command == "emergencyStop") {
    emergencyStop();
  } else {
    // If the command is not recognized
    Serial.println("Unknown command: " + command);
  }
}

void moveForward() {
  // To move forward, retract A and B, release C and D
  motorA.write(120); // Retract Motor A
  motorB.write(120); // Retract Motor B
  motorC.write(70);  // Release Motor C
  motorD.write(70);  // Release Motor D
}

void moveBackward() {
  // To move forward, retract A and B, release C and D
  motorA.write(70); // Release Motor A
  motorB.write(70); // Release Motor B
  motorC.write(110);  // Retract Motor C
  motorD.write(110);  // Retract Motor D
}

void moveLeft() {
  // To move forward, retract A and B, release C and D
  motorA.write(110); // Retract Motor A
  motorB.write(70); // Release Motor B
  motorC.write(110);  // Retract Motor C
  motorD.write(70);  // Release Motor D
}

void moveRight() {
  // To move forward, retract A and B, release C and D
  motorA.write(70); // Retract Motor A
  motorB.write(110); // Release Motor B
  motorC.write(70);  // Retract Motor C
  motorD.write(110);  // Release Motor D
}


void moveAonly() {
  motorA.write(70); // Retract Motor A
  motorB.write(90); // Neutral Motor B
  motorC.write(90);  // Neutral Motor C
  motorD.write(90);  // Neutral Motor D
}

void moveBonly() {
  motorA.write(90); // Neutral Motor A
  motorB.write(95); // Retract Motor B
  motorC.write(90);  // Neutral Motor C
  motorD.write(90);  // Neutral Motor D
}

void moveConly() {
  motorA.write(90); // Neutral Motor A
  motorB.write(90); // Neutral Motor B
  motorC.write(110);  // Retract Motor C
  motorD.write(90);  // Neutral Motor D
}

void moveDonly() {
  motorA.write(90); // Neutral Motor A
  motorB.write(90); // Neutral Motor B
  motorC.write(90);  // Retract Motor C
  motorD.write(110);  // Neutral Motor D
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
}