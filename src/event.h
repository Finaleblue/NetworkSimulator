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
    virtual bool Start() ;
    double GetScheduledTime();

  protected:
    double schedule_at_;
};

class ReceivePacketEvent: public Event{
  public:
    ReceivePacketEvent(Node&, Packet, double);
    bool Start();
  private:
    Node& target_;
    Packet packet_to_receive_;
};

class TransmitPacketEvent: public Event{
  public:
    TransmitPacketEvent(Link&, Node&, Packet, double);
    bool Start();
  private:
    Link& target_;
    Node& next_;
    Packet packet_to_send_;
};

class FlowEndEvent: public Event{
  public:
    FlowEndEvent(Flow&, double);
    bool Start();
  private:
    Flow& flow_to_end_;
};

class FlowStartEvent: public Event{
  public:
    FlowStartEvent(Flow&, double);
    bool Start();
  private:
    Flow& flow_to_start_;
};

class SendPacketEvent: public Event{
  public:
    SendPacketEvent(Node&, Packet, double);
    bool Start();
  private:
    Node& target_;
    Packet packet_to_send_;
};
#endif
