#include "send_packet_event.h"

SendPacketEvent::SendPacketEvent(const Node &target, const Packet p, double t)
  :target_(target), packet_to_send_(p), schedule_at_(t){}


void SendPacketEvent::Start(){
  target_.SendPacket(packet_to_send_, schedule_at_);
}
