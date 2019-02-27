#ifndef BIKEDISPLAY
#define BIKEDISPLAY

class BikeDisplay {
  public:
    virtual void updateSpeedReading(long sensorInterval) = 0;
};

class DefaultBikeDisplay : public BikeDisplay {

  public:
    DefaultBikeDisplay() {
      
    }
  
    void updateSpeedReading(long sensorInterval) {
      Serial.print("Updated Interval Reading: ");
      Serial.println(sensorInterval);
      Serial.println(sensorInterval / 1000.0);
    }
};

#endif
