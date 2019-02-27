#ifndef BIKESPEEDOMETERUNITTEST
#define BIKESPEEDOMETERUNITTEST

#include "UnitTests.h"

void setup() {
  Serial.begin(9600);
  UnitTests::run();
}

void loop() {
  // do nothing.
}

#endif
