#ifndef TRIGGERINTERVALTRACKER
#define TRIGGERINTERVALTRACKER

#include "BikeDisplay.h"
#include "PinReader.h"

enum TriggerState {

  // wait for the first high signal.
  AWAIT_INITIAL_READ,
  
  // pin is still high. Wait for a low signal.
  UNDERGOING_READ,

  // wait for the next high signal.
  AWAIT_NEXT_READ
};

// greater than 10 seconds, reset the timer.
const unsigned long maximumAllowableIntervalMillis = 5000;

// at least 200 millis of continuous
// zero reading before it can be considered properly zero.
// this is because the sensor sometimes triggers
// as the magnet is being pulled away.
const unsigned long relaxationTimeMillis = 20;

class TriggerIntervalTracker {
  private:
    TriggerState triggerState = AWAIT_INITIAL_READ;

    BikeDisplay* bikeDisplay;

    PinReader* pinReader;

    unsigned long t0;

    unsigned long t0_relax;

    int lastSensorRead;

  public:
    TriggerIntervalTracker(
      BikeDisplay* bikeDisplay,
      PinReader* pinReader) : 
        bikeDisplay(bikeDisplay),
        pinReader(pinReader){
      
    }

    TriggerState getState() {
      return triggerState;
    }

    void update() {
      int sensorValue = pinReader->readPin();

      if (triggerState == AWAIT_INITIAL_READ) {
        readInitialSensorValue(sensorValue);
      } else if (triggerState == UNDERGOING_READ) {
        readUndergoingSensorValue(sensorValue);
      } else if (triggerState == AWAIT_NEXT_READ) {
        readNextSensorValue(sensorValue);
      }
    
      lastSensorRead = sensorValue;
    }

  private:
    void updateTriggerState(TriggerState newState) {
        Serial.print("Trigger State Transition: ");
        Serial.print(triggerState);
        Serial.print(" -> ");
        Serial.println(newState);
        triggerState = newState;
      }
  
      long getInterval(long initialTimerRead, long finalTimerRead) {
        if (finalTimerRead >= initialTimerRead) {
          return finalTimerRead - initialTimerRead;
        } else if (finalTimerRead < initialTimerRead) {
          // overflow occurred, leave for now
        }
      }
  
      void readInitialSensorValue(int sensorValue) {
        if (sensorValue == 1) {
          t0 = millis();
          t0_relax = t0;
          Serial.println("Sensor Read HIGH");
          updateTriggerState(UNDERGOING_READ);
        }
      }
      
      void readUndergoingSensorValue(int sensorValue) {
        if (sensorValue == 0) {
          long t = millis();
          long relaxationInterval = getInterval(t0_relax, millis());
          if (relaxationInterval > relaxationTimeMillis) {
            Serial.print("Sensor has relaxed ");
            Serial.print(t0_relax);
            Serial.print(" -> ");
            Serial.println(t);
            updateTriggerState(AWAIT_NEXT_READ);
          }
        } else {
          t0_relax = millis();
        }
      }
      
      void readNextSensorValue(int sensorValue) {
        long t1 = millis();
        long interval = getInterval(t0, t1);
      
        if (sensorValue == 1) {
          updateTriggerState(UNDERGOING_READ);
          bikeDisplay->updateSpeedReading(interval);
          t0_relax = t1;
          t0 = t1;
        } else if (interval > maximumAllowableIntervalMillis) {
          Serial.println("Too long since last sensor read, resetting to require initial read.");
          Serial.println(interval);
          Serial.println(maximumAllowableIntervalMillis);
          updateTriggerState(AWAIT_INITIAL_READ);
        }
      }
};

#endif
