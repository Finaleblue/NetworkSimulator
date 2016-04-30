#include <iostream>
#include "event.h"
#include "flow.h"
#include "link.h"
#include "node.h"
#include "packet.h"
#include "event_manager.h"

extern EventManager event_manager;

Event::Event(double t): schedule_at_(t), debugmsg("Event"){}
Event::~Event(){}

double Event::GetScheduledTime(){
  return schedule_at_;
}

void Event::Start(){
  std::cout <<"default event. do nothing" <<std::endl;
}


ReceivePacketEvent::ReceivePacketEvent(Link& from, Node &target, Packet p, double t)
  :Event(t), from_(from), target_(target), packet_to_receive_(p){}


void ReceivePacketEvent::Start(){
  std::cout<<"@time: "<<schedule_at_<<", "
           <<target_.id()<<" received Packet "
           <<packet_to_receive_.fid()<<packet_to_receive_.id()<<" From "
           <<from_.GetConnectedNode(target_).id()<<std::endl;

  target_.ReceivePacket(from_, packet_to_receive_, schedule_at_);
}

TransmitPacketEvent::TransmitPacketEvent(Link &target, Node& next, Packet p, double t)
  :target_(target), packet_to_send_(p), next_(next), Event(t){}

void TransmitPacketEvent::Start(){
  std::cout<<"@time: "<<schedule_at_<<", "
           <<target_.GetConnectedNode(next_).id()<<" pushed Packet "
           <<packet_to_send_.fid()<<packet_to_send_.id()<<" to "<<next_.id()<<std::endl;
  target_.ReceivePacket(next_, packet_to_send_, schedule_at_);
}

FlowEndEvent::FlowEndEvent(Flow &f, double t)
  :flow_to_end_ (f), Event(t){}


void FlowEndEvent::Start(){
 // flow_to_end_.End();
}

FlowStartEvent::FlowStartEvent(Flow &f, double t) 
  : flow_to_start_(f), Event(t){}

void FlowStartEvent::Start(){
  flow_to_start_.Start(schedule_at_);
}

SendPacketEvent::SendPacketEvent(Node &target, Packet p, double t)
  :target_(target), packet_to_send_(p), Event(t){}


void SendPacketEvent::Start(){
  std::cout<<"@time: "<<schedule_at_<<", "
           <<target_.id() <<" initiated "
           <<packet_to_send_.id()<< " to " 
           << packet_to_send_.GetDst().id()<<std::endl;
  target_.SendPacket(packet_to_send_, schedule_at_);
}

AckTimeoutEvent::AckTimeoutEvent(Host& target, Packet p, double t) //this packet must be ACK type
  :target_(target), ack_packet_(p), Event(t){}

void AckTimeoutEvent::Start(){
  if (target_.CheckAck(ack_packet_)) {return;}
  std::cout<<"@time: "<<schedule_at_<<", "
           <<"ACK "<<ack_packet_.id()<<" timeout."
           <<" Resending the packet."<<std::endl;
  target_.ReSend(ack_packet_, schedule_at_);
}
