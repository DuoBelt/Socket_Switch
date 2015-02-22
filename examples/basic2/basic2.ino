#include <Socketswitch.h>

Socketswitch mySwitch(12);

void setup() {
}

void loop() {
  // Device channel 0-15

  // Turn on channel 0 on device
  mySwitch.channelOn(0x34FCFF,0);
  delay(1000);

  // Turn off channel 0 on device
  mySwitch.channelOff(0x34FCFF,0);
  delay(1000);

  // Turn on all 16 channels on device
  mySwitch.groupOn(0x34FCFF);
  delay(1000);

  // Turn off all 16 channels on device
  mySwitch.groupOff(0x34FCFF);
  delay(1000);
}



