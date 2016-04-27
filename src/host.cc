#include <iostream>
#include "host.h"
#include "link.h"


Host::Host(const std::string id) : Node::Node(id){}

void Host::SendPacket(const Link &l, const Packet p, double time){
  event_manager.push(TransmitPacketEvent(l, p, time);
}

Event Host::RecievePacket(const Packet p, double time){
  SendPacket( Node::neighbors_.at(p.id()), p, time);
} 

const bool Host::allowedToTransmit() const{
  return links_[0].isAvailable();
}
