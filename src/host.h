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
    int NextAck(std::string);
  private:
    std::map<std::string, std::map<int, int> > ack_stack_;
    std::map<std::string, std::set<int> > received_packets_;
    int next_ack_=1;
};
#endif
