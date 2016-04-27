#include "transmit_packet_event.h"

TransmitPacketEvent::TransmitPacketEvent(const Link &target, const Packet p, double t)
  :target_(target), packet_to_send_(p), schedule_at_(t){}


void TransmitPacketEvent::Start(){
  target_.ReceivePacket(packet_to_send_, schedule_at_);
}
