#include "receive_packet_event.h"
ReceivePacketEvent::ReceivePacketEvent(const Node &target, const Packet p, double t)
  :target_(target), packet_to_receive_(p), schedule_at_(t){}


void ReceivePacketEvent::Start(){
  std::cout<<"Packet Received"<<std::endl;
  target_.ReceivePacket(packet_to_receive_, schedule_at_);
}

