#ifndef LINK_H_
#define LINK_H_

class Node;
#include "packet.h"
#include <queue>

class Link{
  public:
    Link(std::string, Node&, Node&, double, double, double);
    bool isAvailable() const;
    void ReceivePacket(Node&, Packet, double);
    void SendPacket(Node&, Packet, double);
    void DoneTransmitting();
    double GetCost() const;
    std::string id() const;
    Node& GetConnectedNode(Node&) const;
    void flush(double);
  private:
    std::string id_;
    double datarate_;
    double buffer_size_;
    double occupancy_;
    double delay_;
    Node& end1_;
    Node& end2_;
    bool transmitting_ = false;
    int num_packs_in_buffer_ = 0; 
    std::queue<std::pair<Packet,Node&> > buffer_;
     
};
#endif
