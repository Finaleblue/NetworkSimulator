#ifndef EVENT_H_
#define EVENT_H_

#include "packet.h"
#include "flow.h"
#include "event_manager.h"

class Event{
  private:
    double schedule_at_ = event_manager.global_time();
    EventManager event_manager_;
  public:
    bool operator < (const Event&) const;
    bool operator > (const Event&) const;
    bool operator == (const Event&) const;
    void Start();
};

class FlowStartEvent: public Event{
  private:
    const Flow& flow_to_start_;
  public:
    FlowStartEvent(Flow, double);
};

class FlowEndEvent: public Event{
  private:
    const Flow& flow_to_end_;
  public:
    FlowEndEvent(Flow, double);
};
class SendPacketEvent: public Event{
  private:
    const Packet& packet_to_send;
  public:
    SendPacketEvent(Packet, double);
};

class ReceivePacketEvent: public Event{
  private:
    const Packet& packet_to_receive;
  public
    ReceivePacketEvent(Packet, double);
};
#endif
