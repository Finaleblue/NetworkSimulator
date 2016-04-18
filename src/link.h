#ifndef LINK_H_
#define LINK_H_

#include "node.h"
#include "packet.h"

class Link{
  private::
    const std::string id_;
    const int datarate_;
    const int buffer_size_;
    const double delay_;
    const Node& end1_;
    const Node& end2_;
    bool transmitting_=false;
    Packet& packet_to_transmit_;
    num_packs_in_buffer_=0; 
    Packet[] buffer_;
  public:
    Link(std::string, int, int, double, Node&, Node&);
    bool isAvailable();
    void ReceivePacket(Packet&, double, Node&);
    void SendPacket(Packet&, double, Node&);
    void DoneTransmitting();
}
#endif
