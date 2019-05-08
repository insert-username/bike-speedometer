#ifndef UNITTESTS
#define UNITTESTS

#include "BikeDisplay.h"
#include "PinReader.h"
#include "TriggerIntervalTracker.h"

class MockPinReader : public PinReader {

  private:
    int value = LOW;

  public:
    void setup() {
      // do nothing;
    }

    int readPin() {
      return value;
    }

    void setValue(int value) {
      this->value = value;
    }
};

class MockBikeDisplay : public BikeDisplay {

  public:
    void updateSpeedReading(long sensorInterval) {
      // do nothing.
    }

    void render() {
      // do nothing.
    }
};

class UnitTests {

  private:
    BikeDisplay* bikeDisplay = new MockBikeDisplay();
    
    MockPinReader* pinReader = new MockPinReader();
    
    TriggerIntervalTracker triggerIntervalTracker;

    UnitTests() : triggerIntervalTracker(bikeDisplay, pinReader) {
      
    }

  public:

    // runs each unit test, and displays the results.
    static void run() {
      Serial.println("Running unit tests...");
      Serial.println();
      
      UnitTests().testStartsAwaitingInitialReading();
      UnitTests().testStillAwaitingInitialReadingAfterSensorReadsLow();
    }

    void testStartsAwaitingInitialReading() {
      TriggerState state = triggerIntervalTracker.getState();

      if (state == AWAIT_INITIAL_READ) {
        Serial.println("PASS:    testStartsAwaitingInitialReading");
      } else {
        Serial.print("FAIL:    testStartsAwaitingInitialReading: ");
        Serial.println(state);
      }
    }

    void testStillAwaitingInitialReadingAfterSensorReadsLow() {
      pinReader->setValue(LOW);
      triggerIntervalTracker.update();

      TriggerState state = triggerIntervalTracker.getState();
      if (state == AWAIT_INITIAL_READ) {
        Serial.println("PASS:    testStillAwaitingInitialReadingAfterSensorReadsLow");
      } else {
        Serial.print("FAIL:    testStartsAwaitingInitialReading: ");
        Serial.println(state);
      }
    }
};

#endif
