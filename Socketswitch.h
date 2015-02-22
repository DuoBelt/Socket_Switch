/*
   Socketswitch.h - Library for controlling socket switches like Nexa and jula (www.jula.com).
   Created by Morten Salomon, February, 2015.
   Released into the public domain.
 */
 
#ifndef Socketswitch_h
#define Socketswitch_h

#include "Arduino.h"

#define SHORT_DELAY  250  
#define LONG_DELAY   (5*SHORT_DELAY)
#define START_DELAY  (10*SHORT_DELAY)
#define END_DELAY    (40*SHORT_DELAY)
#define TOTAL_DELAY  (8*SHORT_DELAY)
#define SYNC_DELAY   (29*SHORT_DELAY)

#define REPEATS      3
#define ON           0
#define OFF          1


class Socketswitch
{
   public:
     Socketswitch(byte pin);
	 void setDevice(unsigned long device);
     void groupOn();
     void groupOff();
	 void groupOn(unsigned long device);
     void groupOff(unsigned long device);
	 void channelOn(byte channel);
	 void channelOff(byte channel);
	 void channelOn(unsigned long device, byte channel);
	 void channelOff(unsigned long device, byte channel);
   private:
     byte _pin;
	 unsigned long _device;
	 void zero();
	 void one();
	 void send_bits(byte mybit);
	 void send_start();
	 void send_end();
	 void send_cmd(unsigned long data);
	 void cmd(unsigned long device,byte channel, byte group, byte action);
};

#endif