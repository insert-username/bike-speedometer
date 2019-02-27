#ifndef BIKESPEEDOMETERRUN
#define BIKESPEEDOMETERRUN

#include "PinReader.h"
#include "BikeDisplay.h"
#include "TriggerIntervalTracker.h"

BikeDisplay* bikeDisplay = new DefaultBikeDisplay();
PinReader* hallPinReader = new DigitalPinReader(3);

TriggerIntervalTracker triggerIntervalTracker(bikeDisplay, hallPinReader);

void setup() {
  Serial.begin(9600);
}

void loop() {
  triggerIntervalTracker.update();
}

#endif
