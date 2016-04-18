#ifndef GLOBAL_H
#define GLOBAL_H

#include "event_manager.h"
#include <math>

EventManager event_man = NULL;

int ACK_SIZE = 64*8; //BITS
int DATA_PACKET_SIZE = 1024*8; //BITS
int LINK_MAX_BITS_IN_SEQUENCE = std::math.power(10,6);

double DEFAULT_GRAPH_SLIDING_WINDOW_STEP = 0.1; //SEC
double DEFAULT_GRAPH_SLIDING_WINDOW_WIDTH = 1; //SEC

double SEND_ROUTING_PACKETS_EVERY = 0.2; //SEC
double SWITCH_ROUTING_TABLE_EVERY = 5; //SEC
double INITIAL_RTT_ESTIMATE = 0.1; //SEC

int NUM_OBSERVATIONS_FOR_RTT = (int)(std::math.power(1*10*10,6)) / DATA_PACKET_SIZE;
double MISSED_ACK_RTT_FACTOR = 1.2;

int TIMEOUT_RTT_MULTIPLIER = 3;
#endif
