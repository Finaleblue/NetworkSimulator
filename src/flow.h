#ifndef FLOW_H_
#define FLOW_H_

#include <string>
#include <vector>
#include <iterator>
#include "global.h"

class Flow{
  private:
    std::string id_; //unique id to distinguish different flows
    Host& src_; //source node (host)
    Host& dst_; //destinatio node (host)
    double start_time_;
    std::string protocol_;
    std::string alpha_;
    int size_; //size of the flow   unit: bits
    int num_packs_; //number of packets
    std::vector<Packet> packets_;
  public:
    Flow(std::string id, double start_time, int size, Host& src, Host& dst,
          std::string protocol, std::string alpha);
    void Start(); //start the flow by sending packets
    void Pack(); //slice data into packets
    double GetStartTime();   
};

#endif
