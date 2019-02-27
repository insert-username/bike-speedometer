enum DeviceState {

  // wait for the first high signal.
  AWAIT_INITIAL_READ,
  
  // pin is still high. Wait for a low signal.
  UNDERGOING_READ,

  // wait for the next high signal.
  AWAIT_NEXT_READ
};
