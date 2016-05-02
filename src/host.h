#ifndef HOST_H_
#define HOST_H_

#include <set>
#include "node.h"

class Host: public Node{
  public:
    Host(const std::string id);
    virtual void SendPacket(Packet, double);
    virtual void ReceivePacket(Link&, Packet, double);
    void ReSend(Packet, double);
    bool allowedToTransmit() const;
    bool CheckAck(Packet p);
    void NextAck(std::string);
    int num_received_packets();
    Link& GetLink();
  private:
    std::map<std::string, std::map<int, int> > ack_stack_;
    std::map<std::string, std::set<int> > received_packets_;
    std::map<std::string, int> sent_packets_; //keep track of sent times;
    std::map<std::string, int> next_ack_;
};
#endif
