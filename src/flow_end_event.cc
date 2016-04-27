#include "flow_end_event.h"

FlowEndEvent::FlowEndEvent(const Flow &f, double t)
  :flow_to_end_ (f), schedule_at_(t){}


void FlowEndEvent::Start(){
  flow_to_end_.End();
}
