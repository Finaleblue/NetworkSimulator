#ifndef EVENT_H_
#define EVENT_H_

#include "flow.h"
#include "link.h"
#include "node.h"
#include "packet.h"

class Event{
  public:
    Event(double);
    bool operator < (const Event&) const;
    bool operator > (const Event&) const;
    bool operator == (const Event&) const;
    void Start();
    double GetScheduledTime();

  protected:
    double schedule_at_;
};

class ReceivePacketEvent: public Event{
  public:
    ReceivePacketEvent(Node&, const Packet, double);
    void Start();
  private:
    Node& target_;
    const Packet packet_to_receive_;
};

class TransmitPacketEvent: public Event{
  public:
    TransmitPacketEvent(const Link&, const Packet, double);
    void Start();
  private:
    const Link& target_;
    const Packet packet_to_send_;
};

class FlowEndEvent: public Event{
  public:
    FlowEndEvent(const Flow&, double);
    void Start();
  private:
    const Flow& flow_to_end_;
};

class FlowStartEvent: public Event{
  public:
    FlowStartEvent(const Flow&, double);
    void Start();
  private:
    const Flow& flow_to_start_;
};

class SendPacketEvent: public Event{
  public:
    SendPacketEvent(const Node&, const Packet, double);
    void Start();
  private:
    const Node& target_;
    const Packet packet_to_send_;
};
#endif
