#ifndef EVENT_H_
#define EVENT_H_

#include "flow.h"
#include "link.h"
#include "node.h"
#include "packet.h"

class Event{
  public:
    Event(double);
    virtual ~Event();
    bool operator < (const Event&) const;
    bool operator > (const Event&) const;
    bool operator == (const Event&) const;
    virtual void Start();
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
    TransmitPacketEvent(Link&, const Packet, double);
    void Start();
  private:
    Link& target_;
    const Packet packet_to_send_;
};

class FlowEndEvent: public Event{
  public:
    FlowEndEvent(Flow&, double);
    void Start();
  private:
    Flow& flow_to_end_;
};

class FlowStartEvent: public Event{
  public:
    FlowStartEvent(Flow&, double);
    void Start();
  private:
    Flow& flow_to_start_;
};

class SendPacketEvent: public Event{
  public:
    SendPacketEvent(Node&, const Packet, double);
    void Start();
  private:
    Node& target_;
    const Packet packet_to_send_;
};
#endif
