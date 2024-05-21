const int led1 = 8;  // Pin voor de eerste LED
const int led2 = 10; // Pin voor de tweede LED
const int button = 12; // Pin voor de knop

int counter = 0; // Teller voor het bijhouden van het aantal drukken op de knop
int lastButtonState = HIGH; // Variabele voor het opslaan van de vorige knopstatus
const int debounceDelay = 50; // Debounce tijd in milliseconden

void setup() {
  pinMode(led1, OUTPUT); // Stel de eerste LED-pin in als output
  pinMode(led2, OUTPUT); // Stel de tweede LED-pin in als output
  pinMode(button, INPUT_PULLUP); // Stel de knop-pin in als input met interne pull-up weerstand
}

void loop() {
   toggleSwitchLeds(); // Roep de functie aan om de LED's te schakelen op basis van knopdrukken
}

/**
 * De functie toggleSwitchLeds leest de status van de knop en schakelt
 * de LED's aan en uit op basis van het aantal keer dat de knop is ingedrukt.
 * De functie maakt gebruik van een eenvoudige debounce-methode met delay().
 */
void toggleSwitchLeds(){
  int buttonState = digitalRead(button); // Lees de status van de knop

  // Controleer of de knop zojuist is ingedrukt (van hoog naar laag)
  if (buttonState == LOW && lastButtonState == HIGH) {
    counter++; // Verhoog de teller bij elke druk op de knop
    delay(debounceDelay); // Wacht voor de debounce tijd om storingen te voorkomen

    // Als de teller even is, zet de eerste LED aan en de tweede uit
    if (counter % 2 == 0) {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
    } 
    // Als de teller oneven is, zet de eerste LED uit en de tweede aan
    else {
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
    }
  }

  lastButtonState = buttonState; // Bewaar de knopstatus voor de volgende loop
}