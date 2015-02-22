#include <Socketswitch.h>

Socketswitch mySwitch(12);

void setup() {
  // Set device base address (0x0 - 0xFFFFFF). Device is a group of 16 channels (16 RF Socket Switches)
  mySwitch.setDevice(0x34FCFF);
}

void loop() {
  // Device channel 0-15

  // Turn on channel 0 on device
  mySwitch.channelOn(0);
  delay(1000);

  // Turn off channel 0 on device
  mySwitch.channelOff(0);
  delay(1000);

  // Turn on all 16 channels on device
  mySwitch.groupOn();
  delay(1000);

  // Turn off all 16 channels on device
  mySwitch.groupOff();
  delay(1000);
}



