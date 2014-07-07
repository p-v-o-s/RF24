/*
 Copyright (C) 2012 James Coliz, Jr. <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

/**
 * Simplest possible example of using RF24Network,
 *
 * RECEIVER NODE
 * Listens for messages from the transmitter and prints them out.
 */

#include <RF24Network.h>
#include <RF24.h>

// nRF24L01(+) radio attached using Getting Started board 
//RF24 radio(9,10);
RF24 radio("/dev/spidev0.0",8000000 , 25);  //spi device, speed and CSN,only CSN is NEEDED in RPI

// Network uses that radio
RF24Network network(radio);


// Address of our node
const uint16_t this_node = 0;

// Address of the other node
const uint16_t other_node = 1;

// Structure of our payload
struct payload_t
{
  unsigned long ms;
  unsigned long counter;
};

void setup(void)
{
  //Serial.begin(57600);
  //Serial.println("RF24Network/examples/helloworld_rx/");
  printf("RF24Network/examples/helloworld_rx/");
 
  radio.begin();
  network.begin(/*channel*/ 90, /*node address*/ this_node);
}

void loop(void)
{
  // Pump the network regularly
  network.update();

  // Is there anything ready for us?
  while ( network.available() )
  {
    // If so, grab it and print it out
    RF24NetworkHeader header;
    payload_t payload;
    network.read(header,&payload,sizeof(payload));
    printf("Received packet #");
    printf("%d",payload.counter);
    printf(" at ");
    printf("%d\n" % payload.ms);
  }
}

int main(int argc, char** argv)
{
  setup();
  while(1)
    loop();
  return 0;
}


// vim:ai:cin:sts=2 sw=2 ft=cpp
