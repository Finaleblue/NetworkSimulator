#ifndef TRANSMITPACKETEVENT_H_
#define TRANSMITPACKETEVENT_H_
#include "event.h"
#include "link.h"
#include "packet.h"

class TransmitPacketEvent: public Event{
  public:
    TransmitPacketEvent(const Link&, const Packet, double);

  private:
    const Link& target_;
    const Packet packet_to_send;
};
#endif
