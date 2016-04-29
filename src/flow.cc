#include "flow.h"
#include "packet.h"
#include "host.h"
#include "global.h"
#include "event_manager.h"

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
    packets_.push_back(Packet("D",i,src_, dst_));
    ++i;
    data -= global::DATA_PACKET_SIZE;
  }
  num_packs_ = packets_.size();
}

void Flow::Start(double t){
  event_manager.push(SendPacketEvent(src_, packets_[pack_to_send], t)); 
}

std::string Flow::id() const{
  return id_;
}
