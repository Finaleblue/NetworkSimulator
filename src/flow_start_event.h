#ifndef FLOWSTARTEVENT_H_
#define FLOWSTARTEVENT_H_
#include "event.h"
class FlowStartEvent: public Event{
  public:
    FlowStartEvent(Flow, double);

  private:
    const Flow& flow_to_start_;
};
#endif
