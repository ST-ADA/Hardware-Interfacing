const int ledAmount = 6; // Aantal LEDs
const int POTENTIOMETER_PIN = A0; // Pin voor de potentiometer

// Array met pin nummers voor de LEDs
const int LED_PINS[ledAmount] = {10, 9, 8, 7, 6, 5};

void setup() {
  // Configureer alle LED pinnen als output
  for (int i = 0; i < ledAmount; ++i) {
    pinMode(LED_PINS[i], OUTPUT);
  }
}

void loop() {
  updateLEDs();
  delay(50); // Voeg een kleine vertraging toe om snel knipperen te voorkomen
}

/**
 * Deze methode leest de huidige waarde van de potentiometer,
 * bepaalt welke LED moet worden ingeschakeld op basis van deze waarde,
 * en werkt de LEDs dienovereenkomstig bij. Slechts één LED wordt
 * tegelijk ingeschakeld.
 */
void updateLEDs() {
  int potentiometerValue = analogRead(POTENTIOMETER_PIN); // Lees de waarde van de potentiometer
  int segmentSize = 1024 / ledAmount; // Bereken de grootte van elk segment
  int ledIndex = potentiometerValue / segmentSize; // Bepaal welke LED moet worden ingeschakeld

  // Schakel de geselecteerde LED in en schakel de andere uit
  for (int i = 0; i < ledAmount; i++) {
    digitalWrite(LED_PINS[i], i == ledIndex ? HIGH : LOW);
  }
}
