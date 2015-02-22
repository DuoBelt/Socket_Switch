#include "Arduino.h"
#include "Socketswitch.h"

Socketswitch::Socketswitch(byte pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
  _device = 0; // default device - change using setDevice
}

void Socketswitch::setDevice(unsigned long device) {
  // Device is a group of 16 channels, device number: 0x0 - 0xFFFFFF (0 - 16777215)
  _device = device;
}

void Socketswitch::groupOn() {
  cmd(_device,0, SET_ON, SET_ON);
}

void Socketswitch::groupOff() {
  cmd(_device,0, SET_ON, SET_OFF);
}

void Socketswitch::groupOn(unsigned long device) {
  cmd(device,0, SET_ON, SET_ON);
}

void Socketswitch::groupOff(unsigned long device) {
  cmd(device,0, SET_ON, SET_OFF);
}

void Socketswitch::channelOn(byte channel){
  cmd(_device,channel, SET_OFF, SET_ON);
}	

void Socketswitch::channelOff(byte channel){
  cmd(_device,channel, SET_OFF, SET_OFF);
}

void Socketswitch::channelOn(unsigned long device, byte channel){
  cmd(device,channel, SET_OFF, SET_ON);
}

void Socketswitch::channelOff(unsigned long device, byte channel){
  cmd(device,channel, SET_OFF, SET_OFF);
}

void Socketswitch::zero() {
  digitalWrite(_pin, HIGH);
  delayMicroseconds(SHORT_DELAY);
  digitalWrite(_pin, LOW);
  delayMicroseconds(LONG_DELAY);
}

void Socketswitch::one() {
  digitalWrite(_pin, HIGH);
  delayMicroseconds(SHORT_DELAY);
  digitalWrite(_pin, LOW);
  delayMicroseconds(SHORT_DELAY);
}

void Socketswitch::send_bits(byte mybit) {
  // 0 = 01
  // 1 = 10

  if (mybit) {
    one();
    zero();
  } 
  else {
    zero();
    one();
  }
}

void Socketswitch::send_start() {
  digitalWrite(_pin, HIGH);
  delayMicroseconds(SHORT_DELAY);
  digitalWrite(_pin, LOW);
  delayMicroseconds(START_DELAY);
}

void Socketswitch::send_end() {
  digitalWrite(_pin, HIGH);
  delayMicroseconds(SHORT_DELAY);
  digitalWrite(_pin, LOW);
  delayMicroseconds(END_DELAY);
}

void Socketswitch::send_cmd(unsigned long data) {
  byte bits;
  send_start();
  for (bits=32;bits>0;bits--) 	{
    send_bits((data>>(bits-1))&1);
  }
  send_end();
}

void Socketswitch::cmd(unsigned long device,byte channel, byte group, byte action) {
  byte i;
  device = device << 6;				// add 6 bits to device (group on/off bit, channel on/off bit, 4 bits for the channels)
  device |= ((group & 1) << 5);		// add group bit
  device |= ((action & 1) << 4);	// add on/off bit
  device |= ((~channel) & 15);	    // add device number	
  for (i=0;i<REPEATS;i++) {
    send_cmd(device);               // send the data
    delayMicroseconds(SYNC_DELAY);
  }
}
