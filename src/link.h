#ifndef LINK_H_
#define LINK_H_

class Node;
#include "packet.h"

class Link{
  private:
    const std::string id_;
    const double datarate_;
    const double buffer_size_;
    double occupancy_;
    const double delay_;
    const Node& end1_;
    const Node& end2_;
    bool transmitting_ = false;
    Packet& packet_to_transmit_;
    int num_packs_in_buffer_ = 0; 
    Packet buffer_[10];
  public:
    Link(std::string, Node&, Node&, double, double, double);
    const bool isAvailable() const;
    void ReceivePacket(Packet&, double, Node&);
    void SendPacket(Packet&, double, Node&);
    void DoneTransmitting();
    double GetCost() const;
     
};
#endif
