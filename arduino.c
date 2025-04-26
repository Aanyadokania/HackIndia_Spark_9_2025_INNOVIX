#define trigPin 6
#define echoPin 7
#define relayPin 4

// Motor control pins
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

// Enable pins (PWM)
#define ENA 5
#define ENB 6

long duration;
int distance;
int motorSpeed = 150; // Set speed (0-255), lower = slower

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(relayPin, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  digitalWrite(relayPin, HIGH); // Relay ON by default
  stopMotors(); // Ensure motors are off at startup

  Serial.begin(9600);
}

void loop() {
  // Ultrasonic distance measurement
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 20000); // Timeout after 20ms
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > 0 && distance < 20) {
    // Obstacle detected
    stopMotors();
    digitalWrite(relayPin, LOW); // Cut power via relay
  } else if (distance >= 20 && distance < 400) {
    // Safe to move
    forward();
    digitalWrite(relayPin, HIGH); // Power ON via relay
  }

  delay(50); // Reduced delay for quicker response
}

void forward() {
  // Set speed using PWM
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);

  // Motor direction (forward)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopMotors() {
  // Stop motors by disabling enable pins
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}