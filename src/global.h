#ifndef GLOBAL_H_
#define GLOBAL_H_

namespace global{
  static double MAX_SIMULATION_TIME = 200.0; //seconds
  static const int ACK_PACKET_SIZE = 1; //1kbits
  static const int DATA_PACKET_SIZE = 10; //10kbits
  static const int CTRL_PACKET_SIZE = 2; // 2kbits
  static const int INIT_CWND = 1;
  static const int INIT_SSTHRESH = 10;
  static const int INIT_RTTE = 100;
  static const int PacketSize(char s){
    if (s=='C') {return CTRL_PACKET_SIZE;}
    else if (s=='A') {return ACK_PACKET_SIZE;}
    else {return DATA_PACKET_SIZE;}
  }
};
#endif
