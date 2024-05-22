#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialiseer het LCD scherm met het I2C adres 0x27 en een 16x2 scherm
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Definieer de pinnen voor de start- en stopknoppen
const int startButton = 11;
const int stopButton = 10;

// Definieer variabelen voor het bijhouden van de timerstatus en tijden
bool running = false;
unsigned long startTime = 0;
unsigned long stopTime = 0;
unsigned long startButtonPressTime = 0;
unsigned long lapTime = 0;
bool lapRecorded = false;

void setup() {
  // Stel de pinnen voor de knoppen in als invoer
  pinMode(startButton, INPUT);
  pinMode(stopButton, INPUT);

  // Initialiseer het LCD scherm
  lcd.init();
  lcd.backlight();
  lcd.clear();

  // Stel de initiale tekst in op het LCD scherm
  lcd.setCursor(0, 0);
  lcd.print("Time: 00:00:000");
  lcd.setCursor(0, 1);
  lcd.print("Lap: 00:00:000");
}

void loop() {
  // Lees de status van de start- en stopknoppen
  int startButtonState = digitalRead(startButton);
  int stopButtonState = digitalRead(stopButton);

  // Reset de timer als beide knoppen ingedrukt zijn
  if (startButtonState == HIGH && stopButtonState == HIGH) {
    resetTimer();
  }

  // Start de timer als de startknop wordt ingedrukt en de timer niet loopt
  if (startButtonState == HIGH && !running) {
    startTimer();
  }

  // Stop de timer als de stopknop wordt ingedrukt en de timer loopt
  if (stopButtonState == HIGH && running) {
    stopTimer();
  }

  // Check of de startknop 1 seconde ingedrukt is om een lap-tijd op te slaan
  if (startButtonState == HIGH) {
    if (startButtonPressTime == 0) {
      startButtonPressTime = millis();
    } else if (millis() - startButtonPressTime >= 1000 && !lapRecorded) {
      recordLapTime();
    }
  } else {
    startButtonPressTime = 0;
    lapRecorded = false;
  }

  // Update het timerdisplay als de timer loopt
  if (running) {
    updateTimerDisplay();
  }
}

/**
 * Start de timer en houdt rekening met eventueel verstreken tijd
 */
void startTimer() {
  // Bereken de nieuwe starttijd door de tijd sinds de laatste stop op te tellen bij de huidige tijd
  startTime += millis() - stopTime;
  running = true;
}

/**
 * Stop de timer en bewaar de huidige tijd
 */
void stopTimer() {
  // Bewaar de huidige tijd als stopTime en stop de timer
  stopTime = millis();
  running = false;
}

/**
 * Reset de timer en het lap-display zonder de timer te starten
 */
void resetTimer() {
  // Reset de starttijd, stop de timer, reset de lap-tijd en status
  startTime = 0;
  stopTime = 0;
  running = false;
  lapTime = 0;
  lapRecorded = false;
  
  // Reset het timer- en lap-display op het LCD scherm
  lcd.setCursor(0, 0);
  lcd.print("Time: 00:00:000");
  lcd.setCursor(0, 1);
  lcd.print("Lap: 00:00:000");
}

/**
 * Registreer de lap-tijd en update het display
 */
void recordLapTime() {
  // Sla de lap-tijd op als deze nog niet geregistreerd is
  if (!lapRecorded) {
    lapTime = millis() - startTime;
    updateLapDisplay();
    lapRecorded = true;
  }
}

/**
 * Update het timerdisplay op het LCD scherm
 */
void updateTimerDisplay() {
  // Bereken de verstreken tijd in minuten, seconden en milliseconden
  unsigned long elapsedTime = millis() - startTime;
  unsigned long minutes = (elapsedTime / 60000) % 60;
  unsigned long seconds = (elapsedTime / 1000) % 60;
  unsigned long milliseconds = elapsedTime % 1000;

  // Update het timerdisplay op het LCD scherm
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  if (minutes < 10) {
    lcd.print("0");
  }
  lcd.print(minutes);
  lcd.print(":");
  if (seconds < 10) {
    lcd.print("0");
  }
  lcd.print(seconds);
  lcd.print(":");
  if (milliseconds < 100) {
    lcd.print("0");
  }
  if (milliseconds < 10) {
    lcd.print("0");
  }
  lcd.print(milliseconds);
}

/**
 * Update het lap-display op het LCD scherm
 */
void updateLapDisplay() {
  // Bereken de lap-tijd in minuten, seconden en milliseconden
  unsigned long minutes = (lapTime / 60000) % 60;
  unsigned long seconds = (lapTime / 1000) % 60;
  unsigned long milliseconds = lapTime % 1000;

  // Update het lap-display op het LCD scherm
  lcd.setCursor(0, 1);
  lcd.print("Lap: ");
  if (minutes < 10) {
    lcd.print("0");
  }
  lcd.print(minutes);
  lcd.print(":");
  if (seconds < 10) {
    lcd.print("0");
  }
  lcd.print(seconds);
  lcd.print(":");
  if (milliseconds < 100) {
    lcd.print("0");
  }
  if (milliseconds < 10) {
    lcd.print("0");
  }
  lcd.print(milliseconds);
}
