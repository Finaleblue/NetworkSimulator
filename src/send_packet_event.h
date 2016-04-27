#ifndef SENDPACKETEVENT_H_
#define SENDPACKETEVENT_H_
#include "event.h"

class SendPacketEvent: public Event{
  public:
    SendPacketEvent(const &Node, const Packet, double);

  private:
    const Node& target_;
    const Packet packet_to_send;
};
#endif
