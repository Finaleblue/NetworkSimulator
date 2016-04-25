#include "router.h"
#include "link.h"
#include "global.h"

Router::Router(const std::string id){
  id_ = id;
}

void Router::SendPacket(const Packet &p, const double time){
  links_[0].ReceivePacket(p, time, nodes_[0]);
}

void Router::RecievePacket(const Packet &p, const double time){
  cout<< "Packet " << p.id() << " received"<< " at time "<< time<<std::endl;
  received_packets_.push_back(p); 
  global::event_manager.push(SendPacketEvent( Packet("A", seqNum(), this, p.GetSrc()), time); 
} 

bool Router::allowedToTransmit(){
  return links_[0].isAvailable();
}
