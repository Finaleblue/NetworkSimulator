#ifndef GLOBAL_H_
#define GLOBAL_H_

namespace global{
  static double MAX_SIMULATION_TIME = 1000.0; //seconds
  static const int ACK_PACKET_SIZE = 1; //1kbits
  static const int DATA_PACKET_SIZE = 5; //10kbits
  static const int CTRL_PACKET_SIZE = 2; // bits
  static const int TIME_OUT = 30;
  static const int PacketSize(char s){
    if (s=='C') {return CTRL_PACKET_SIZE;}
    else if (s=='A') {return ACK_PACKET_SIZE;}
    else {return DATA_PACKET_SIZE;}
  }
};
#endif
