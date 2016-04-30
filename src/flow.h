#ifndef FLOW_H_
#define FLOW_H_

#include <vector>
#include <string>
#include "global.h"

class Host;
class Packet;

class Flow{
  public:
    Flow(std::string id, double start_time, int size, 
         Host& src, Host& dst, std::string protocol);
    void Start(double t); //start the flow by sending packets
    void Pack(); //slice data into packets
    double GetStartTime() const;   
    std::string id() const;
    void Congestion();
    void RTT_Update(double rtt); //updates RTT info when ACK is received
    double RTTE(); //return rtte_;
  private:
    bool slow_start=true;
    int CWND = global::INIT_CWND; //unit: number of packets
    int SSTHRESH = global::INIT_SSTHRESH; // unit: number of packets
    double rtte_ = global::INIT_RTTE; //estimated Round Trip Time
    int acks_received_ = 0;
    std::string id_; //unique id to distinguish different flows
    Host& src_; //source node (host)
    Host& dst_; //destinatio node (host)
    double start_time_;
    std::string protocol_;
    int size_; //size of the flow   unit: bits
    int pack_to_send = 0;
    int num_packs_; //number of packets
    std::vector<Packet> packets_;
};

#endif
