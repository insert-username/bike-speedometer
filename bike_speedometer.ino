#define HALL_PIN 3
#include "TriggerIntervalTracker.h"
#include "PinReader.h"

BikeDisplay* bikeDisplay = new BikeDisplay();
PinReader* hallPinReader = new DigitalPinReader(HALL_PIN);

TriggerIntervalTracker triggerIntervalTracker(bikeDisplay, hallPinReader);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}


void loop() {
  triggerIntervalTracker.update();
}
