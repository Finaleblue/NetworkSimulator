#ifndef GLOBAL_H_
#define GLOBAL_H_

namespace global{
  static double MAX_SIMULATION_TIME = 300.0; //seconds
  static const int ACK_PACKET_SIZE = 1024; //1kbits
  static const int DATA_PACKET_SIZE = 10240; //10kbits
  static const int CTRL_PACKET_SIZE = 512; // bits
  
  static const int PacketSize(std::string s){
    if (s=="C") {return CTRL_PACKET_SIZE;}
    else if (s=="A") {return ACK_PACKET_SIZE;}
    else {return DATA_PACKET_SIZE;}
  }
};
#endif
