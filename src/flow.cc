#include "flow.h"
#include "packet.h"
#include "host.h"
#include "global.h"

Flow::Flow(const std::string id, double start_time, int size, const Host& src, 
           const Host& dst, const std::string protocol):
  id_(id),
  start_time_(start_time),
  size_(size),
  src_(src),
  dst_(dst),
  protocol_(protocol){}



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

void Flow::Start(){
}
