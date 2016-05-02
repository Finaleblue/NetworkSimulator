#ifndef GLOBAL_H_
#define GLOBAL_H_
#include <iostream>
#include <fstream>

namespace global{
  static double MAX_SIMULATION_TIME = 3000.0; //seconds
  static double MAX_TIMEOUT = 100;
  static const double ACK_PACKET_SIZE = 64; // 500 bytes
  static const double DATA_PACKET_SIZE = 1024; // 64 kbytes
  static const double CTRL_PACKET_SIZE = 64; // 2 kbytes
  static const double INIT_CWND = DATA_PACKET_SIZE;
  static const double INIT_SSTHRESH = DATA_PACKET_SIZE*10;
  static const double INIT_RTTE = 50; //seconds
  static const double PacketSize(char s){
    if (s=='C') {return CTRL_PACKET_SIZE;}
    else if (s=='A') {return ACK_PACKET_SIZE;}
    else {return DATA_PACKET_SIZE;}
  }
};
#endif
