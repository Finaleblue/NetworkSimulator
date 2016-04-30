#include <iostream>
#include <memory>
#include "flow.h"
#include "global.h"
#include "packet.h"
#include "host.h"
#include "event.h"
#include "event_manager.h"

extern EventManager event_manager;

Flow::Flow(std::string id, double start_time, int size, Host& src, 
           Host& dst, std::string protocol):
  id_(id),
  start_time_(start_time),
  size_(size),
  src_(src),
  dst_(dst),
  protocol_(protocol)
{}



double Flow::GetStartTime() const{
  return start_time_;
}

void Flow::Pack(){
  int data = size_;
  int i=1;
  while (data > 0){
    packets_.push_back(Packet(id_, 'D', i ,src_, dst_));
    ++i;
    data -= global::DATA_PACKET_SIZE;
  }
  num_packs_ = packets_.size();
  std::cout<<"total packets: "<<num_packs_<<std::endl;
}

void Flow::Start(double t){
  //std::cout<<"flow starts now"<<std::endl;
  if (pack_to_send >= num_packs_)  {return;}
  else{
    event_manager.push(std::shared_ptr<FlowStartEvent>(new FlowStartEvent(*this, t+5)));
    event_manager.push(std::shared_ptr<SendPacketEvent>(new SendPacketEvent(src_, packets_[pack_to_send], t))); 
    ++pack_to_send;
  }
}

std::string Flow::id() const{
  return id_;
}
