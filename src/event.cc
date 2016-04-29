#include <iostream>
#include "event.h"
#include "flow.h"
#include "link.h"
#include "node.h"
#include "packet.h"
#include "event_manager.h"

extern EventManager event_manager;

Event::Event(double t): schedule_at_(t){}
Event::~Event(){}

bool Event::operator < (const Event& e) const{
  return (*this).schedule_at_ > e.schedule_at_;
}
bool Event::operator > (const Event& e) const{
  return (*this).schedule_at_ < e.schedule_at_;
}
bool Event::operator == (const Event& e) const{
  return (*this).schedule_at_ == e.schedule_at_;
}

double Event::GetScheduledTime(){
  return schedule_at_;
}

bool Event::Start(){
  std::cout <<"default event. do nothing" <<std::endl;
  return true;
}


ReceivePacketEvent::ReceivePacketEvent(Node &target, Packet p, double t)
  :Event(t), target_(target), packet_to_receive_(p){}


bool ReceivePacketEvent::Start(){
  std::cout<<"@time: "<<schedule_at_<<", "
           <<target_.id()<<" received Packet "
           <<packet_to_receive_.id()<<" From "
           <<packet_to_receive_.GetSrc().id()<<std::endl;

  return target_.ReceivePacket(packet_to_receive_, schedule_at_);
}

TransmitPacketEvent::TransmitPacketEvent(Link &target, Node& next, Packet p, double t)
  :target_(target), packet_to_send_(p), next_(next), Event(t){}

bool TransmitPacketEvent::Start(){
  std::cout<<"@time: "<<schedule_at_<<", "
           <<target_.id()<<" is transmitting"<<std::endl;
  return target_.ReceivePacket(next_, packet_to_send_, schedule_at_);
}

FlowEndEvent::FlowEndEvent(Flow &f, double t)
  :flow_to_end_ (f), Event(t){}


bool FlowEndEvent::Start(){
 // flow_to_end_.End();
}

FlowStartEvent::FlowStartEvent(Flow &f, double t) 
  : flow_to_start_(f), Event(t){}

bool FlowStartEvent::Start(){
  return flow_to_start_.Start(schedule_at_);
}

SendPacketEvent::SendPacketEvent(Node &target, Packet p, double t)
  :target_(target), packet_to_send_(p), Event(t){}


bool SendPacketEvent::Start(){
  std::cout<<"@time: "<<schedule_at_<<", "
           <<target_.id() <<" sent packet "
           <<packet_to_send_.id()<< " to " 
           << packet_to_send_.GetDst().id()<<std::endl;

  return target_.SendPacket(packet_to_send_, schedule_at_);
}
