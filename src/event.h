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

endif
