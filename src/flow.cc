#include <iostream>
#include <memory>
#include "flow.h"
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
  std::cout<<num_packs_<<" packets from "<<id_<<std::endl;
}

void Flow::Start(double t){
  int count=0;
  //std::cout<<"flow starts now"<<std::endl;
  while (count < CWND){
    if (pack_to_send >= num_packs_)  {return;}
    else{
      event_manager.push(std::shared_ptr<FlowStartEvent>(new FlowStartEvent(*this, t+5)));
      event_manager.push(std::shared_ptr<SendPacketEvent>(new SendPacketEvent(src_, packets_[pack_to_send], t))); 
      ++pack_to_send;
      ++count;
    }
  }
}

void Flow::RTT_Update(double rtt){
  //estimate RTTE
  rtte_ = (rtte_ * (acks_received_) + rtt) / (++acks_received_);
  ++CWND;
}

void Flow::Congestion(){
  if (protocol_ == "TAEHO"){
    CWND = 1;
    SSTHRESH = CWND/2;
  }
  else if(protocol_ == "RENO"){
    CWND /= 2;
    SSTHRESH = CWND/2;
  }
}

double Flow::RTTE(){
  return rtte_;
}
std::string Flow::id() const{
  return id_;
}
