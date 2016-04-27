#ifndef EVENT_H_
#define EVENT_H_

class Packet;
class Node;
class Flow;

class Event{
  public:
    bool operator < (const Event&) const;
    bool operator > (const Event&) const;
    bool operator == (const Event&) const;
    void Start();
    double GetScheduledTime();

  protected:
    double schedule_at_;
};

class FlowStartEvent: public Event{
  public:
    FlowStartEvent(Flow, double);

  private:
    const Flow& flow_to_start_;
};

class FlowEndEvent: public Event{
  public:
    FlowEndEvent(Flow, double);

  private:
    const Flow& flow_to_end_;
};

class SendPacketEvent: public Event{
  public:
    SendPacketEvent(const &Node, const Packet, double);

  private:
    const Node& target_;
    const Packet packet_to_send;
};

class ReceivePacketEvent: public Event{
  public:
    ReceivePacketEvent(const &Node, const Packet, double);

  private:
    const Node& target_;
    const Packet packet_to_receive;
};

class TransmitPacketEvent: public Event{
  public:
    TransmitPacketEvent(const &Link, const Packet, double);
  private:
    const Link& target_;
    const Packet packet_to_receive;
};
#endif
