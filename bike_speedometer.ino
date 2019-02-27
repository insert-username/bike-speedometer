// Uncomment to run test suite instead of
// standard operations
//#define PERFORM_UNIT_TESTS

#ifdef PERFORM_UNIT_TESTS

  #include "bike_speedometer_unit_test.h"

#else

  // digital read pin for hall effect sensor.
  #define HALL_SENSOR_PIN 3

  #include "bike_speedometer_run.h"

#endif
