// DavidMaitland.me 2015
// See LICENSE file for licensing details

const int coinSelector = A0; // Analog input pin that the coin selector uses
const int signalCostFactor = 5; // Each signal pulse is worth 5p

int signalValue = 0; // For storing value from analog input

int state; // Current state
int lastState = 0; // Last state

int balance = 0; // Pence
int coinValue = 0; // Curent coin value

int update = 1; // Used for sending an update

long updateDebounceTime = 0; // The last time we sent an update
long updateDebounceDelay = 500; // Update 500ms after last singal pulse

void setup() {

  pinMode(13, OUTPUT); // Status LED

  Serial.begin(9600); // Setup serial at 9600 baud

  delay(2000); // Don't start main loop until we're sure that the coin selector has started

  Serial.println("Ready..");

}

void loop() {

  signalValue = analogRead(coinSelector); // Read analog value from coin selector

  if (signalValue > 1000) {

    state = 1; // State is 1 as we're high

  } else {

    state = 0;

    // Should we send a balance update

    if (update == 0) {

      if ((millis() - updateDebounceTime) > updateDebounceDelay) {

        Serial.print("Coin Value: ");
        Serial.println(coinValue); // WARNING: The coin value will be wrong if coins are inserted within the updateDebounceDelay, adjust the delay and test

        Serial.print("Balance: ");
        Serial.println(balance); // This should be the most accurate as we should get the same ammount of pulses even if multiple coins get inserted at once

        coinValue = 0; // Reset current coin value

        update = 1; // Make sure we don't run again, till next coin

      }

    }

  }

  if (state != lastState) {

    // Process new signal

    if (state == 1) {

      digitalWrite(13, HIGH); // Turn status LED on to show signal

      balance = balance + signalCostFactor; // Update balance

      coinValue = coinValue + signalCostFactor; // Update coin value

      updateDebounceTime = millis(); // Update last time we processed a signal

      update = 0; // Time to send a update now?

    } else {

      digitalWrite(13, LOW);  // Turn status LED off

    }

    lastState = state; // Update last state

  }

  delay(1);

}
