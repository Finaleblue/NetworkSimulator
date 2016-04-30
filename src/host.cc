#include <iostream>
#include <memory>
#include "host.h"
#include "link.h"
#include "event.h"
#include "event_manager.h"

extern EventManager event_manager;

Host::Host(std::string id) : Node::Node(id){}

void Host::SendPacket(Packet p, double t){
  Link& l = event_manager.Net().GetLink(links_[0]);
  Node& n = event_manager.Net().GetNode(neighbors_.at(l.id()));
  event_manager.push(std::shared_ptr<TransmitPacketEvent>(new TransmitPacketEvent(l, n, p, t)));
  return;
}

void Host::ReceivePacket(Link& from, Packet p, double t){
  from.flush(t);
  if(p.type() == 'D'){ //only execute this when the received packet is a data packet
    received_packets_.push_back(p);
    SendPacket(Packet('A',p.seqNum(), *this, p.GetSrc()),t);
  }
  //TODO: implement case when it receives ACK and CTRL Packages
} 

bool Host::allowedToTransmit() const{
  //return links_[0].isAvailable();
  return true;
}

