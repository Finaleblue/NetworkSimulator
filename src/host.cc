#include "host.h"
#include "link.h"

Host(const std::string id){
  id_ = id;
}

void SendPacket(const Packet &p, const double time){
  links_[0].ReceivePacket(p, time, nodes_[0]);
}

void RecievePacket(const Packet &p, const double time){
  cout<< "Packet " << p.id() << " received"<< " at time "<< time<<std::endl;
  received_packets_.push_back(p); 
  event_manager.push(SendPacketEvent( Packet("A", seqNum(), this, p.GetSrc()), time); 
} 

bool allowedToTransmit(){
  return links_[0].isAvailable();
}
