#include "flow.h"

Flow(std::string id, double start_time, int size, Host& src, Host& dst,
      std::string protocol, std::string alpha){
  id_ = id;
  start_time_ = start_time;
  size_ = size;
  src_ = src;
  dst_ = dst;
  protocol_ = protocol;
  alpha_ = alpha;
  packets_();
}

double GetStartTime(){
  return start_time_;
}

void Pack(){
  data = size_;
  int i=1;
  while (data!=0){
    packets_.push_back(Packet("D",i,src_, dst_));
    ++i;
    data -= Glboal::PACKET_SIZE;
  }
  num_packs_ = packets_.size();
}

void Start(){
  const std::vector<Packet>::iterator itr = packets_.begin();
  if (itr == packets_.end()){
    event_manager.add(FlowEndEvent(this, event_manager.global_time());
  }

  else if (src_.allowedToTransmit()){
    event_manager.add(SendPacketEvent(*itr, event_manager.global_time()));
  }
}
