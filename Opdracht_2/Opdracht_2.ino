const int pinArray[] = {2, 3, 4, 5, 6, 7, 8, 9}; // Pin-array voor de LEDs
const int numLeds = sizeof(pinArray) / sizeof(pinArray[0]); // Aantal LEDs berekenen
const int delayTime = 100; // Tijdvertraging in milliseconden

void setup()
{
  for (int count = 0; count < numLeds; count++) {
    pinMode(pinArray[count], OUTPUT); // Stel elke pin in als output
  }
}

void loop()
{
  // LEDs aanzetten van links naar rechts
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(pinArray[i], HIGH); // Zet de LED aan
    delay(delayTime);                // Wacht voor de opgegeven tijd (100 ms)
    digitalWrite(pinArray[i], LOW);  // Zet de LED uit
  }
  
  // LEDs aanzetten van rechts naar links
  for (int i = numLeds - 1; i >= 0; i--) {
    digitalWrite(pinArray[i], HIGH); // Zet de LED aan
    delay(delayTime);                // Wacht voor de opgegeven tijd (100 ms)
    digitalWrite(pinArray[i], LOW);  // Zet de LED uit
  }
}