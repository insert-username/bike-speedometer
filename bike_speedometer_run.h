#ifndef BIKESPEEDOMETERRUN
#define BIKESPEEDOMETERRUN

#include "PinReader.h"
#include "PinWriter.h"
#include "BikeDisplay.h"
#include "TriggerIntervalTracker.h"

// 7 segment display (common anode) digital pins
// no special reason for using analog pins, just
// running out of digital pins to use.
PinWriter* digit1Enable = new DigitalPinWriter(A3);
PinWriter* digit2Enable = new DigitalPinWriter(A4);
PinWriter* digit3Enable = new DigitalPinWriter(A2);

PinWriter* segA_Enable = new DigitalPinWriter(2);
PinWriter* segB_Enable = new DigitalPinWriter(9);
PinWriter* segC_Enable = new DigitalPinWriter(6);
PinWriter* segD_Enable = new DigitalPinWriter(4);
PinWriter* segE_Enable = new DigitalPinWriter(3);
PinWriter* segF_Enable = new DigitalPinWriter(8);
PinWriter* segG_Enable = new DigitalPinWriter(7);
PinWriter* segDP_Enable = new DigitalPinWriter(5);

SevenSegmentPinWriter* sevenSegmentPinWriter = new CommonAnodeSevenSegmentPinWriter(
    segA_Enable,
    segB_Enable,
    segC_Enable,
    segD_Enable,
    segE_Enable,
    segF_Enable,
    segG_Enable,
    segDP_Enable
  );

BikeDisplay* bikeDisplay = new SevenSegmentBikeDisplay(
  digit1Enable,
  digit2Enable,
  digit3Enable,
  sevenSegmentPinWriter
  );
PinReader* hallPinReader = new DigitalPinReader(HALL_SENSOR_PIN);

TriggerIntervalTracker triggerIntervalTracker(bikeDisplay, hallPinReader);

void setup() {
  Serial.begin(9600);
}

void loop() {
  triggerIntervalTracker.update();
}

#endif
