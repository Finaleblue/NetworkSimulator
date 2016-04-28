#include <iostream>
#include "event.h"
#include "flow.h"
#include "link.h"
#include "node.h"
#include "packet.h"

Event::Event(double t): schedule_at_(t){}
bool Event::operator < (const Event& e) const{
  return (*this).schedule_at_ < e.schedule_at_;
}
bool Event::operator > (const Event& e) const{
  return (*this).schedule_at_ > e.schedule_at_;
}
bool Event::operator == (const Event& e) const{
  return (*this).schedule_at_ == e.schedule_at_;
}

double Event::GetScheduledTime(){
  return schedule_at_;
}

ReceivePacketEvent::ReceivePacketEvent(Node &target, const Packet p, double t)
  :Event(t), target_(target), packet_to_receive_(p){}


void ReceivePacketEvent::Start(){
  std::cout<<"Packet Received"<<std::endl;
  target_.ReceivePacket(packet_to_receive_, schedule_at_);
}

TransmitPacketEvent::TransmitPacketEvent(const Link &target, const Packet p, double t)
  :target_(target), packet_to_send_(p), Event(t){}

void TransmitPacketEvent::Start(){
  target_.ReceivePacket(packet_to_send_, schedule_at_);
}

FlowEndEvent::FlowEndEvent(const Flow &f, double t)
  :flow_to_end_ (f), Event(t){}


void FlowEndEvent::Start(){
 // flow_to_end_.End();
}

FlowStartEvent::FlowStartEvent(const Flow &f, double t) 
  : flow_to_start_(f), Event(t){}

void FlowStartEvent::Start(){
  //flow_to_start_.Start();
}

SendPacketEvent::SendPacketEvent(const Node &target, const Packet p, double t)
  :target_(target), packet_to_send_(p), Event(t){}


void SendPacketEvent::Start(){
  target_.SendPacket(target_, packet_to_send_, schedule_at_);
}
