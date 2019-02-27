#define HALL_PIN 3
#include "DeviceState.h"

void setup() {
  // put your setup code here, to run once:
  pinMode(HALL_PIN, INPUT);
  Serial.begin(9600);
}

// greater than 10 seconds, reset the timer.
const unsigned long maximumAllowableIntervalMillis = 5000;

// at least 200 millis of continuous
// zero reading before it can be considered properly zero.
// this is because the sensor sometimes triggers
// as the magnet is being pulled away.
const unsigned long relaxationTimeMillis = 20;

DeviceState deviceState = AWAIT_INITIAL_READ;

unsigned long t0;

unsigned long t0_relax;

int lastSensorRead;

void updateSpeedReading(long sensorInterval) {
  Serial.print("Updated Interval Reading: ");
  Serial.println(sensorInterval);
  Serial.println(sensorInterval / 1000.0);
}

void updateDeviceState(DeviceState newState) {
  Serial.print("Device State Transition: ");
  Serial.print(deviceState);
  Serial.print(" -> ");
  Serial.println(newState);
  deviceState = newState;
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
    updateDeviceState(UNDERGOING_READ);
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
      updateDeviceState(AWAIT_NEXT_READ);
    }
  } else {
    t0_relax = millis();
  }
}

void readNextSensorValue(int sensorValue) {
  long t1 = millis();
  long interval = getInterval(t0, t1);

  if (sensorValue == 1) {
    updateDeviceState(UNDERGOING_READ);
    updateSpeedReading(interval);
    t0_relax = t1;
    t0 = t1;
  } else if (interval > maximumAllowableIntervalMillis) {
    Serial.println("Too long since last sensor read, resetting to require initial read.");
    Serial.println(interval);
    Serial.println(maximumAllowableIntervalMillis);
    updateDeviceState(AWAIT_INITIAL_READ);
  }
}

void loop() {
  int sensorValue = digitalRead(HALL_PIN);

  if (sensorValue == 0) {
//    Serial.println(sensorValue);
  }
  

  if (deviceState == AWAIT_INITIAL_READ) {
    readInitialSensorValue(sensorValue);
  } else if (deviceState == UNDERGOING_READ) {
    readUndergoingSensorValue(sensorValue);
  } else if (deviceState == AWAIT_NEXT_READ) {
    readNextSensorValue(sensorValue);
  }

  lastSensorRead = sensorValue;
}
