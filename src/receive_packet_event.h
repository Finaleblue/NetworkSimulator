#ifndef RECEIVEPACKETEVENT_H_
#define RECEIVEPACKETEVENT_H_
#include "event.h"
#include "node.h"
#include "packet.h"

class ReceivePacketEvent: public Event{
  public:
    ReceivePacketEvent(const Node&, const Packet, double);

  private:
    const Node& target_;
    const Packet packet_to_receive_;
};

#endif
