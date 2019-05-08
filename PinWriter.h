#ifndef PINWRITER
#define PINWRITER

class PinWriter {
    public:
      virtual void writePin(int output) = 0;
};

class DigitalPinWriter : public PinWriter {
    private:
      int pin;
    
    public:
      DigitalPinWriter(int pin) : pin(pin) {
        pinMode(pin, OUTPUT);
      }

      void writePin(int output) {
        digitalWrite(pin, output);
      }
};

class SevenSegmentPinWriter {
  public:
    virtual void renderDigit(int digit, bool isDPShown) = 0;
};

class CommonAnodeSevenSegmentPinWriter : public SevenSegmentPinWriter {

  PinWriter* segA_Enable;
  PinWriter* segB_Enable;
  PinWriter* segC_Enable;
  PinWriter* segD_Enable;
  PinWriter* segE_Enable;
  PinWriter* segF_Enable;
  PinWriter* segG_Enable;
  PinWriter* segDP_Enable;

public:
  CommonAnodeSevenSegmentPinWriter(
    PinWriter* segA_Enable, 
    PinWriter* segB_Enable, 
    PinWriter* segC_Enable, 
    PinWriter* segD_Enable, 
    PinWriter* segE_Enable, 
    PinWriter* segF_Enable, 
    PinWriter* segG_Enable, 
    PinWriter* segDP_Enable) : 
      segA_Enable(segA_Enable), 
      segB_Enable(segB_Enable), 
      segC_Enable(segC_Enable), 
      segD_Enable(segD_Enable), 
      segE_Enable(segE_Enable), 
      segF_Enable(segF_Enable), 
      segG_Enable(segG_Enable), 
      segDP_Enable(segDP_Enable)
    {
      
    }

    void renderDigit(int digit, bool isDPShown) {
      // set all pins to high first.
      segA_Enable->writePin(HIGH);
      segB_Enable->writePin(HIGH);
      segC_Enable->writePin(HIGH);
      segD_Enable->writePin(HIGH);
      segE_Enable->writePin(HIGH);
      segF_Enable->writePin(HIGH);
      segG_Enable->writePin(HIGH);
      
      // render DP.
      segDP_Enable->writePin(isDPShown ? LOW : HIGH);
      
      switch(digit) {
        case 0:
          segA_Enable->writePin(LOW);
          segB_Enable->writePin(LOW);
          segC_Enable->writePin(LOW);
          segD_Enable->writePin(LOW);
          segE_Enable->writePin(LOW);
          segF_Enable->writePin(LOW);
          segG_Enable->writePin(HIGH);
          return;
        case 1:
          segA_Enable->writePin(HIGH);
          segB_Enable->writePin(LOW);
          segC_Enable->writePin(LOW);
          segD_Enable->writePin(HIGH);
          segE_Enable->writePin(HIGH);
          segF_Enable->writePin(HIGH);
          segG_Enable->writePin(HIGH);
          return;
        case 2:
          segA_Enable->writePin(LOW);
          segB_Enable->writePin(LOW);
          segC_Enable->writePin(HIGH);
          segD_Enable->writePin(LOW);
          segE_Enable->writePin(LOW);
          segF_Enable->writePin(HIGH);
          segG_Enable->writePin(LOW);
          return;
        case 3:
          segA_Enable->writePin(LOW);
          segB_Enable->writePin(LOW);
          segC_Enable->writePin(LOW);
          segD_Enable->writePin(LOW);
          segE_Enable->writePin(HIGH);
          segF_Enable->writePin(HIGH);
          segG_Enable->writePin(LOW);
          return;
        case 4:
          segA_Enable->writePin(HIGH);
          segB_Enable->writePin(LOW);
          segC_Enable->writePin(LOW);
          segD_Enable->writePin(HIGH);
          segE_Enable->writePin(HIGH);
          segF_Enable->writePin(LOW);
          segG_Enable->writePin(LOW);
          return;
        case 5:
          segA_Enable->writePin(LOW);
          segB_Enable->writePin(HIGH);
          segC_Enable->writePin(LOW);
          segD_Enable->writePin(LOW);
          segE_Enable->writePin(HIGH);
          segF_Enable->writePin(LOW);
          segG_Enable->writePin(LOW);
          return;
        case 6:
          segA_Enable->writePin(LOW);
          segB_Enable->writePin(HIGH);
          segC_Enable->writePin(LOW);
          segD_Enable->writePin(LOW);
          segE_Enable->writePin(LOW);
          segF_Enable->writePin(LOW);
          segG_Enable->writePin(LOW);
          return;
        case 7:
          segA_Enable->writePin(LOW);
          segB_Enable->writePin(LOW);
          segC_Enable->writePin(LOW);
          segD_Enable->writePin(HIGH);
          segE_Enable->writePin(HIGH);
          segF_Enable->writePin(HIGH);
          segG_Enable->writePin(HIGH);
          return;
        case 8:
          segA_Enable->writePin(LOW);
          segB_Enable->writePin(LOW);
          segC_Enable->writePin(LOW);
          segD_Enable->writePin(LOW);
          segE_Enable->writePin(LOW);
          segF_Enable->writePin(LOW);
          segG_Enable->writePin(LOW);
          return;
        case 9:
          segA_Enable->writePin(LOW);
          segB_Enable->writePin(LOW);
          segC_Enable->writePin(LOW);
          segD_Enable->writePin(LOW);
          segE_Enable->writePin(HIGH);
          segF_Enable->writePin(LOW);
          segG_Enable->writePin(LOW);
          return;
      }
    }
  
};

#endif
