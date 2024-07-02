const int ledPins[] = {2, 3, 4, 5}; // Pins where the LEDs are connected
const int buttonPins[] = {6, 7, 8, 9}; // Pins where the buttons are connected
const int buzzerPin = 10; // Pin where the buzzer is connected

int pattern[] = {0, 1, 2, 3}; // Game pattern example
int playerPattern[4]; // array to store player sequence
int playerIndex = 0; // Current index in player sequence

void setup() { // Initial setup when the program starts
  for (int i = 0; i < 4; i++) { // Set the LED pins as outputs
    pinMode(ledPins[i], OUTPUT); // Configure pin i as output for the LED
    pinMode(buttonPins[i], INPUT_PULLUP); // Configure pin i as input with pull-up resistor for the button
  }
  pinMode(buzzerPin, OUTPUT); // Configure the pin for the buzzer as output
}

void loop() { // main loop

  // show the led pattern (line 39)
  showPattern();

  // wait for the player to repeat the led pattern (line 53)
  waitForPlayer();

  if (checkPattern()) { // Check if the player's pattern matches the original pattern (line 77)

    // If it matches, increase the pattern and continue the game
    playerIndex = 0;
    addNewStep();

  } else {

    // If it does not match, the player loses and the game restarts
    playerIndex = 0;
    loseGame();
  }
}

void showPattern() { // show the led pattern
  for (int i = 0; i < 4; i++) {

    digitalWrite(ledPins[pattern[i]], HIGH);
    
    tone(buzzerPin, 1000 + 100 * pattern[i], 300); // Emit tone based on LED, sounds different for each LED
    delay(500);

    digitalWrite(ledPins[pattern[i]], LOW);

    delay(200);
  }
}

void waitForPlayer() { // wait for the player to repeat the led pattern

  int buttonPressed = -1;

  while (playerIndex < 4) {

    for (int i = 0; i < 4; i++) {

      if (digitalRead(buttonPins[i]) == LOW) {
        buttonPressed = i;

      }
    }

    if (buttonPressed != -1) {
      playerPattern[playerIndex] = buttonPressed;
      playerIndex++;
      delay(300); // Avoid bounces
      buttonPressed = -1;

    }
  }
}

bool checkPattern() { // Check if the player's pattern matches the original pattern
  for (int i = 0; i < 4; i++) {
    if (playerPattern[i] != pattern[i]) {
      return false;
    }
  }
  return true;
}

void addNewStep() { // in other cases, add more random patterns here
  pattern[3] = random(0, 4);
}

void loseGame() { // when the player loses the game, the buzzer rings and the LEDs flash in order

  for (int i = 0; i < 4; i++) {

    digitalWrite(ledPins[i], HIGH);

    delay(200);

    digitalWrite(ledPins[i], LOW);

  }

  delay(1000); // wait time before restart the game

  pattern[0] = random(0, 4); // restart the pattern for a new game
}
