#ifndef LINK_H_
#define LINK_H_

class Node;
#include "packet.h"
#include <queue>

class Link{
  public:
    Link(const std::string, const Node&, const Node&, double, double, double);
    bool isAvailable() const;
    void ReceivePacket(const Packet, double);
    void SendPacket(const Packet, double);
    void DoneTransmitting();
    double GetCost() const;
    std::string id() const;
  private:
    const std::string id_;
    const double datarate_;
    const double buffer_size_;
    double occupancy_;
    const double delay_;
    const Node& end1_;
    const Node& end2_;
    bool transmitting_ = false;
    int num_packs_in_buffer_ = 0; 
    std::queue<Packet> buffer_;
     
};
#endif
