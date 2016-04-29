#include <iostream>
#include <memory>
#include "host.h"
#include "link.h"
#include "event.h"
#include "event_manager.h"

extern EventManager event_manager;

Host::Host(std::string id) : Node::Node(id){}

bool Host::SendPacket(Packet p, double t){
  Link& l = event_manager.Net().GetLink(links_[0]);
  Node& n = event_manager.Net().GetNode(neighbors_.at(links_[0]));
  event_manager.push(std::shared_ptr<TransmitPacketEvent>(new TransmitPacketEvent(l, n, p, t)));
  return true;
}

bool Host::ReceivePacket(Packet p, double t){
  event_manager.Net().GetLink(links_[0]).flush(t);
  if(p.type() == 'D'){ //only execute this when the received packet is a data packet
    received_packets_.push_back(p);
    return SendPacket(Packet('A',p.seqNum(), *this, p.GetSrc()),t);
  }
  //TODO: implement case when it receives ACK and CTRL Packages
} 

bol Host::allowedToTransmit() const{
  //return links_[0].isAvailable();
  return true;
}

