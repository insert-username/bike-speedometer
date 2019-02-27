#ifndef BIKEDISPLAY
#define BIKEDISPLAY

class BikeDisplay {

  public:
  
    void updateSpeedReading(long sensorInterval) {
      Serial.print("Updated Interval Reading: ");
      Serial.println(sensorInterval);
      Serial.println(sensorInterval / 1000.0);
    }
};

#endif
