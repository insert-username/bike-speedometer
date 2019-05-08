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

// if the wheel takes longer than this to turn, consider
// the reading invalid and go back to awaiting the initial
// reading.
const unsigned long maximumAllowableIntervalMillis = 5000;

// minimum time to wait after a reading before the next
// positive reading can be taken.
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

      bikeDisplay->render();
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
          bikeDisplay->updateSpeedReading(0);
          updateTriggerState(AWAIT_INITIAL_READ);
        }
      }
};

#endif
