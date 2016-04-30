#ifndef EVENT_H_
#define EVENT_H_

#include <memory>
#include "flow.h"
#include "link.h"
#include "node.h"
#include "packet.h"

class Event{
  public:
    Event(double);
    virtual ~Event();
    virtual void Start() ;
    double GetScheduledTime();
    std::string debugmsg = "EVENT";

  protected:
    double schedule_at_;
};

struct EventCmp{
  bool operator() (std::shared_ptr<Event> e1, std::shared_ptr<Event> e2) const{
    return e1->GetScheduledTime() > e2->GetScheduledTime();
  }
};

class ReceivePacketEvent: public Event{
  public:
    ReceivePacketEvent(Link&, Node&, Packet, double);
    void Start();
  private:
    Link& from_;
    Node& target_;
    Packet packet_to_receive_;
};

class TransmitPacketEvent: public Event{
  public:
    TransmitPacketEvent(Link&, Node&, Packet, double);
    void Start();
    std::string debugmsg = "TX";
  private:
    Link& target_;
    Node& next_;
    Packet packet_to_send_;
};

class FlowEndEvent: public Event{
  public:
    FlowEndEvent(Flow&, double);
    void Start();
    std::string debugmsg = "FEND";
  private:
    Flow& flow_to_end_;
};

class FlowStartEvent: public Event{
  public:
    FlowStartEvent(Flow&, double);
    void Start();
    std::string debugmsg = "FSTART";
  private:
    Flow& flow_to_start_;
};

class SendPacketEvent: public Event{
  public:
    SendPacketEvent(Node&, Packet, double);
    void Start();
    std::string debugmsg = "SEND";
  private:
    Node& target_;
    Packet packet_to_send_;
};
#endif
