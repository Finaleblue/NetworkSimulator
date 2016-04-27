#include <iostream>
#include "event.h"
#include "node.h"
#include "packet.h"

bool Event::operator < (const Event& e) const{
  return this.schedule_at_ < e.schedule_at_;
}
bool Event::operator > (const Event& e) const{
  return this.schedule_at_ > e.schedule_at_;
}
bool Event::operator == (const Event& e) const{
  return this.schedule_at_ == e.schedule_at_;
}

double Event::GetScheduledTime(){
  return schedule_at_;
}


