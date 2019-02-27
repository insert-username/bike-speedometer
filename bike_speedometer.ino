#define HALL_PIN 3
#include "TriggerIntervalTracker.h"

BikeDisplay bikeDisplay;

TriggerIntervalTracker triggerIntervalTracker(HALL_PIN, bikeDisplay);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}


void loop() {
  triggerIntervalTracker.update();
}
