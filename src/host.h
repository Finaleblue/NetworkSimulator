/**
 * Cooper Union Communication Networks Final Project
 * Author: Eui Han
 * Version: 1.4
 **/
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
    int num_received_packets();
    virtual Link& GetLink();
  private:
    std::map<std::string, std::map<int, int> > ack_stack_; //received acks
    std::map<std::string, std::set<int> > received_packets_;
    std::map<std::string, int> sent_packets_; //keep track of sent times;
    std::map<std::string, int> next_ack_;
    std::set<std::string> resent_; //we dont want to send same packets over and over again.
};
#endif
