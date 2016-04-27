#ifndef FLOWENDEVENT_H_
#define FLOWENDEVENT_H_
#include "event.h"
class FlowEndEvent: public Event{
  public:
    FlowEndEvent(Flow, double);

  private:
    const Flow& flow_to_end_;
};
#endif
