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

FlowStartEvent::FlowStartEvent(const Flow &f, double t) 
  : flow_to_start_(f), schedule_at_(t){}

double Event::GetScheduledTime(){
  return schedule_at_;
}

void FlowStartEvent::Start(){
  flow_to_start_.Start();
}

FlowEndEvent::FlowEndEvent(const Flow &f, double t)
  :flow_to_end_ (f), schedule_at_(t){}


void FlowEndEvent::Start(){
  flow_to_end_.End();
}

SendPacketEvent::SendPacketEvent(const Node &target, const Packet p, double t)
  :target_(target), packet_to_send_(p), schedule_at_(t){}


void SendPacketEvent::Start(){
  target_.SendPacket(packet_to_send_, schedule_at_);
}

ReceivePacketEvent::ReceivePacketEvent(const Node &target, const Packet p, double t)
  :target_(target), packet_to_receive_(p), schedule_at_(t){}


void ReceivePacketEvent::Start(){
  std::cout<<"Packet Received"<<std::endl;
  target_.ReceivePacket(packet_to_receive_, schedule_at_);
}

