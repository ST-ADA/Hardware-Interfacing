#include <Servo.h>

const int button1Pin = 10; // Drukknop 1 pin
const int button2Pin = 11; // Drukknop 2 pin
const int servoPin = 7;    // Servomotor pin

Servo servo; // Maak een servo object aan

void setup() {
  pinMode(button1Pin, INPUT_PULLUP); // Drukknop 1 als input met pull-up weerstand
  pinMode(button2Pin, INPUT_PULLUP); // Drukknop 2 als input met pull-up weerstand
  servo.attach(servoPin);             // Servo aan pin 7
  servo.write(0);                     // Zet de servo in de startpositie (0 graden)
}

void loop() {
 delay(100); // Voeg een korte vertraging toe (100 milliseconden)


  if (digitalRead(button1Pin) == LOW && digitalRead(button2Pin) == LOW) { // Als beide knoppen worden ingedrukt
    moveServo(120, 5000, 500); // Beweeg servo naar 120° in 5 seconden, wacht 2 seconden, en keer terug in 0.5 seconden
  } else if (digitalRead(button1Pin) == LOW) { // Als drukknop 1 wordt ingedrukt
    moveServo(120, 5000, 5000);               // Beweeg servo naar 120° in 5 seconden en keer terug in 5 seconden
  } else if (digitalRead(button2Pin) == LOW) { // Als drukknop 2 wordt ingedrukt
    moveServo(120, 500, 500);                 // Beweeg servo naar 120° in 0.5 seconden en keer terug in 0.5 seconden
  }
}

// Functie om de servo te bewegen naar een bepaalde hoek in een bepaalde tijd
void moveServo(int angle, int durationForward, int durationBackward) {
  int initialAngle = servo.read(); // Huidige positie van de servo
  int angleChange = angle - initialAngle; // Hoekverandering die moet worden bereikt
  int stepDelay = durationForward / abs(angleChange); // Tijdsvertraging per stap

  // Beweeg de servo naar de gewenste hoek met de berekende tijdsvertraging
  for (int i = 0; i < abs(angleChange); i++) {
    if (angleChange > 0) {
      servo.write(initialAngle + i); // Verhoog de hoek
    } else {
      servo.write(initialAngle - i); // Verlaag de hoek
    }
    delay(stepDelay); // Wacht tot de volgende stap
  }

  delay(1000); // Voeg een kleine vertraging toe om de beweging zichtbaar te maken

  // Beweeg de servo terug naar de startpositie met de berekende tijdsvertraging
  for (int i = abs(angleChange); i > 0; i--) {
    if (angleChange > 0) {
      servo.write(initialAngle + i); // Verhoog de hoek
    } else {
      servo.write(initialAngle - i); // Verlaag de hoek
    }
    delay(durationBackward / abs(angleChange)); // Wacht tot de volgende stap
  }
}