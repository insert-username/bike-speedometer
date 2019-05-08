#ifndef BIKEDISPLAY
#define BIKEDISPLAY

#include "PinWriter.h"

class BikeDisplay {
  public:
    virtual void updateSpeedReading(long sensorInterval) = 0;

    /**
     * Called once every update loop. May be used to render
     * to 7-Segment Displays.
     */
    virtual void render() = 0;
};

class SerialBikeDisplay : public BikeDisplay {

  public:
    SerialBikeDisplay() {
      
    }

    void updateSpeedReading(long sensorInterval) {
      Serial.print("Updated Interval Reading: ");
      Serial.println(sensorInterval);
      Serial.println(sensorInterval / 1000.0);
    }

    void render() {
      
    }
};

class SevenSegmentBikeDisplay : public BikeDisplay {

  PinWriter* digit1Enable;
  PinWriter* digit2Enable;
  PinWriter* digit3Enable;

  SevenSegmentPinWriter* sevenSegmentPinWriter;

  long sensorInterval = 0;

  void renderDigit(int digit, int value) {
      digit1Enable->writePin(LOW);
      digit2Enable->writePin(LOW);
      digit3Enable->writePin(LOW);

      // note, this should be rendered BEFORE enabling the
      // digit pin, otherwise you'll get "ghosting" of the
      // previously rendered digit.
      sevenSegmentPinWriter->renderDigit(value, false);

      digit1Enable->writePin(digit == 1 ? HIGH : LOW);
      digit2Enable->writePin(digit == 2 ? HIGH : LOW);
      digit3Enable->writePin(digit == 3 ? HIGH : LOW);

      // flash the digit for 1ms. Puny human eyes will
      // integrate this and average it over much longer,
      // making it seem as if it is constantly on.
      delay(1);

      digit1Enable->writePin(LOW);
      digit2Enable->writePin(LOW);
      digit3Enable->writePin(LOW);
      delay(1);
  }

  // renders the three least significant digits of a number.
  // If the number has more than 3 digits, they will not be shown.
  void renderNumber(int number) {
    int firstDigit = (number / 100) % 10;
    int secondDigit = (number / 10) % 10;
    int thirdDigit = number % 10;

    // calling render for each digit, even when they are not necessarily
    // displayed, will ensure a consistent render time.
    renderDigit(1, firstDigit != 0 ? firstDigit: -1);
    renderDigit(2, (secondDigit != 0 || firstDigit != 0) ? secondDigit : -1);
    renderDigit(3, thirdDigit);
  }

  public:
    SevenSegmentBikeDisplay(
      PinWriter* digit1Enable,
      PinWriter* digit2Enable,
      PinWriter* digit3Enable,
      SevenSegmentPinWriter* sevenSegmentPinWriter) :
      digit1Enable(digit1Enable),
      digit2Enable(digit2Enable),
      digit3Enable(digit3Enable), 
      sevenSegmentPinWriter(sevenSegmentPinWriter) {
      
    }
  
    void updateSpeedReading(long sensorInterval) {
      this->sensorInterval = sensorInterval;
    }

    void render() {
      renderNumber(sensorInterval);
    }
};

#endif
