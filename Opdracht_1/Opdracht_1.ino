const int ledBlue = 10; // Pin voor de blauwe LED
const int ledRed = 13;  // Pin voor de rode LED
const int time = 1500;  // Tijdvertraging in milliseconden

void setup()
{
  pinMode(ledBlue, OUTPUT); // Stel de blauwe LED-pin in als output
  pinMode(ledRed, OUTPUT);  // Stel de rode LED-pin in als output
}

void loop()
{
  switchLeds(); // Roep de functie aan om de LEDs te wisselen
}

/**
 * Wisselt de status van de blauwe en rode LED met een vertraging.
 */
void switchLeds(){
  digitalWrite(ledBlue, HIGH); // Zet de blauwe LED aan
  digitalWrite(ledRed, LOW);   // Zet de rode LED uit
  delay(time);                 // Wacht voor de opgegeven tijd (1500 ms)
  
  digitalWrite(ledBlue, LOW);  // Zet de blauwe LED uit
  digitalWrite(ledRed, HIGH);  // Zet de rode LED aan
  delay(time);                 // Wacht voor de opgegeven tijd (1500 ms)
}