#ifndef FLOW_H_
#define FLOW_H_

#include <set>
#include <vector>
#include <stack>
#include <string>
#include "global.h"

class Host;
class Packet;

class Flow{
  public:
    Flow(std::string id, double start_time, int size, 
         Host& src, Host& dst, std::string protocol);
    void Start(int, double); //start the flow by sending packets
    void Pack(); //slice data into packets
    double GetStartTime() const;   
    std::string id() const;
    void Congestion(int);
    void RTT_Update(int, double); //updates RTT info when ACK is received
    double TimeOutEst(); //return rtte_;
    void Push(Packet&);
  private:
    std::ofstream *RTTSS_;
    std::ofstream *CWNDSS_;
    bool slow_start=true;
    double CWND = global::INIT_CWND; //unit: number of bits 
    double SSTHRESH = global::INIT_SSTHRESH; // unit: number of bits 
    double rtte_ = global::INIT_RTTE; //estimated Round Trip Time
    double most_recent_rtt_;
    double flow_num_=0;
    int acks_received_ = 0;
    std::string id_; //unique id to distinguish different flows
    Host& src_; //source node (host)
    Host& dst_; //destinatio node (host)
    double start_time_;
    std::string protocol_;
    int size_; //size of the flow   unit: bits
    int pack_to_send = 0;
    int num_packs_; //number of packets
    std::set<int> rtt_book_;
    std::set<int> congestion_book_;
    std::stack<Packet> packets_;
};

#endif
