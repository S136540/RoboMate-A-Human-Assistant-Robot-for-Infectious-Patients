#include <AFMotor.h>
#include <SoftwareSerial.h>

SoftwareSerial bluetooth(0, 1); // RX, TX

#define Speed 170

// Create the motor objects
AF_DCMotor M1(1);
AF_DCMotor M2(2);
AF_DCMotor M3(3);
AF_DCMotor M4(4);

const int recordPin = 7;
const int playPin = 8;
const int loopPin = 9;

void setup() {
  // Start the serial communication
  Serial.begin(9600);
  bluetooth.begin(9600);

  // Set the motor speeds
  M1.setSpeed(Speed);
  M2.setSpeed(Speed);
  M3.setSpeed(Speed);
  M4.setSpeed(Speed);

  pinMode(recordPin, OUTPUT);
  pinMode(playPin, OUTPUT);
  pinMode(loopPin, OUTPUT);

  digitalWrite(recordPin, LOW);
  digitalWrite(playPin, LOW);
  digitalWrite(loopPin, LOW);
}

void loop() {
  bluetoothControl();
}

void executeCommand(char command);

void bluetoothControl() {
  // Get the Bluetooth control remote values
  if (bluetooth.available()) {
    char value = bluetooth.read();
    Serial.println(value);

    if (value == 'U') {
      moveForward();
    } else if (value == 'D') {
      moveBackward();
    } else if (value == 'L') {
      turnLeft();
    } else if (value == 'R') {
      turnRight();
    } else if (value == 'S') {
      stopMotors();
    } else {
      executeCommand(value);
    }
  }
}

/****************** Motor functions *****************/
void moveForward() {
  M1.run(FORWARD);
  M2.run(FORWARD);
  M3.run(FORWARD);
  M4.run(FORWARD);
}

void moveBackward() {
  M1.run(BACKWARD);
  M2.run(BACKWARD);
  M3.run(BACKWARD);
  M4.run(BACKWARD);
}

void turnRight() {
  M1.run(FORWARD);
  M2.run(FORWARD);
  M3.run(BACKWARD);
  M4.run(BACKWARD);
}

void turnLeft() {
  M1.run(BACKWARD);
  M2.run(BACKWARD);
  M3.run(FORWARD);
  M4.run(FORWARD);
}

void stopMotors() {
  M1.run(RELEASE);
  M2.run(RELEASE);
  M3.run(RELEASE);
  M4.run(RELEASE);
}

void startRecording() {
  Serial.println("Recording...");
  digitalWrite(recordPin, HIGH);
  delay(10);
  digitalWrite(recordPin, LOW);
  Serial.println("Recording finished.");
}

void playRecording() {
  Serial.println("Playing...");
  digitalWrite(playPin, HIGH);
  delay(10);
  digitalWrite(playPin, LOW);
  Serial.println("Playback finished.");
}

void loopPlayback() {
  Serial.println("Looping playback...");
  digitalWrite(loopPin, HIGH);
  delay(10);
  digitalWrite(loopPin, LOW);
  Serial.println("Looping playback finished.");
}

void executeCommand(char command) {
  switch (command) {
    case 'R': // Start recording
      startRecording();
      break;
    case 'P': // Play recording once
      playRecording();
      break;
    case 'L': // Loop playback
      loopPlayback();
      break;
  }
}
