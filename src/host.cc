#include <iostream>
#include "host.h"
#include "event_manager.h"
#include "link.h"
#include "event.h"



Host::Host(std::string id) : Node::Node(id){}

void Host::SendPacket(Packet p, double t){
  for(auto &l : links_){
    for(auto &n : nodes_){
      event_manager.push(TransmitPacketEvent(l.second, n.second, p, t));
      break; //break because there is only one node
    }
    break; //break because there is only one link for host
  }
}

void Host::RecievePacket(Packet p, double t){
  received_packets_.push_back(p);
  SendPacket(Packet("A",p.seqNum(), *this, p.GetSrc()),t);
} 

bool Host::allowedToTransmit() const{
  //return links_[0].isAvailable();
  return true;
}

