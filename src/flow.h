#ifndef FLOW_H_
 #define FLOW_H_

#include <vector>

class Host;
class Packet;

class Flow{
  private:
    const std::string id_; //unique id to distinguish different flows
    const Host& src_; //source node (host)
    const Host& dst_; //destinatio node (host)
    double start_time_;
    const std::string protocol_;
    int size_; //size of the flow   unit: bits
    int num_packs_; //number of packets
    std::vector<Packet> packets_;
  public:
    Flow(const std::string id, double start_time, int size, 
         const Host& src, const Host& dst, const std::string protocol);
    void Start(); //start the flow by sending packets
    void Pack(); //slice data into packets
    double GetStartTime() const;   
};

#endif
