#ifndef BIKESPEEDOMETERRUN
#define BIKESPEEDOMETERRUN

BikeDisplay* bikeDisplay = new BikeDisplay();
PinReader* hallPinReader = new DigitalPinReader(3);

TriggerIntervalTracker triggerIntervalTracker(bikeDisplay, hallPinReader);

void setup() {
  Serial.begin(9600);
}

void loop() {
  triggerIntervalTracker.update();
}

#endif
