#ifndef PINREADER
#define PINREADER

class PinReader {
    public:
      virtual int readPin() = 0;
};

class DigitalPinReader : public PinReader {
    private:
      int pin;
    
    public:
      DigitalPinReader(int pin) : pin(pin) {
        pinMode(pin, INPUT);
      }

      int readPin() {
        return digitalRead(pin);
      }
};

#endif
