#ifndef LINK_H_
#define LINK_H_

class Node;
#include "packet.h"

class Link{
  public:
    Link(const std::string, const Node&, const Node&, double, double, double);
    bool isAvailable() const;
    void ReceivePacket(const Packet, double) const;
    void SendPacket(const Packet, double);
    void DoneTransmitting();
    double GetCost() const;
    std::string id() const;
  private:
    std::string id_;
    double datarate_;
    double buffer_size_;
    double occupancy_;
    double delay_;
    const Node& end1_;
    const Node& end2_;
    bool transmitting_ = false;
    Packet& packet_to_transmit_;
    int num_packs_in_buffer_ = 0; 
    const Packet buffer_[10];
     
};
#endif
