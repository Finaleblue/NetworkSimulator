#include <iostream>
#include <memory>
#include "host.h"
#include "link.h"
#include "event.h"
#include "event_manager.h"

extern EventManager event_manager;

Host::Host(std::string id) : Node::Node(id){}

bool Host::SendPacket(Packet p, double t){
  for(auto &l : links_){
    event_manager.push(std::shared_ptr<TransmitPacketEvent>(new TransmitPacketEvent(l.second, neighbors_.at(l.first), p, t)));
    std::cout<<"host flag "<<l.second.id()<<std::endl;
    return true;
  }
  return true;
}

bool Host::RecievePacket(Packet p, double t){
  received_packets_.push_back(p);
  return SendPacket(Packet("A",p.seqNum(), *this, p.GetSrc()),t);
} 

bool Host::allowedToTransmit() const{
  //return links_[0].isAvailable();
  return true;
}

