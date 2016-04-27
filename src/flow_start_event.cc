#include "flow_staft_event.h"

FlowStartEvent::FlowStartEvent(const Flow &f, double t) 
  : flow_to_start_(f), schedule_at_(t){}

void FlowStartEvent::Start(){
  flow_to_start_.Start();
}

