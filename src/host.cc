#include <iostream>
#include <memory>
#include "host.h"
#include "link.h"
#include "event.h"
#include "event_manager.h"
#include "global.h"

extern EventManager event_manager;

Host::Host(std::string id) : Node::Node(id){}

void Host::SendPacket(Packet p, double t){
  Link& l = event_manager.Net().GetLink(links_[0]);
  Node& n = event_manager.Net().GetNode(neighbors_.at(l.id()));
  event_manager.push(std::shared_ptr<TransmitPacketEvent>(new TransmitPacketEvent(l, n, p, t)));
  if(p.type() == 'D'){
    event_manager.push(std::shared_ptr<AckTimeoutEvent>(new AckTimeoutEvent(*this, Packet(p.fid(), 'A', p.seqNum(), p.GetDst(), p.GetSrc()), t+global::TIME_OUT)));
  }
  return;
}

void Host::ReceivePacket(Link& from, Packet p, double t){
  from.flush(t);
  if(p.type() == 'D'){ //only execute this when the received packet is a data packet
    auto itr = received_packets_.find(p.fid());
    if (itr == received_packets_.end()){
      std::set<int> subset;
      subset.insert(p.seqNum());
      received_packets_.insert({p.fid(), subset});
      SendPacket(Packet(p.fid(), 'A', NextAck(p.fid()), *this, p.GetSrc()),t);

    }
    else{
      received_packets_.at(p.fid()).insert(p.seqNum());
      SendPacket(Packet(p.fid(), 'A', NextAck(p.fid()), *this, p.GetSrc()),t);
    }
  }
  else if (p.type() == 'A'){
    if(ack_stack_.find(p.fid()) == ack_stack_.end()){
      std::map<int,int> inner;
      inner.insert({p.seqNum(), 1});
      ack_stack_.insert({p.fid(), inner});
    }
    else if(ack_stack_.at(p.fid()).find(p.seqNum()) == ack_stack_.at(p.fid()).end()){
      ack_stack_.at(p.fid()).insert({p.seqNum(),1});
    }
    else{
      if(++ack_stack_.at(p.fid()).at(p.seqNum()) >= 3){
        //TODO: triple duplicate event;
      }
    }
  }
  //TODO: implement case when it receives ACK and CTRL Packages
} 

bool Host::allowedToTransmit() const{
  //return links_[0].isAvailable();
  return true;
}

int Host::NextAck(std::string fid){
  next_ack_=0;
  auto itr = received_packets_.find(fid);
  while( itr ->second.find(++next_ack_) != itr->second.end() ){
  }
  return --next_ack_;
}

bool Host::CheckAck(Packet p){
  auto itr = ack_stack_.find(p.fid()); //for this flow 
  if (itr == ack_stack_.end()) {return false;} //first packet of the flow
  auto iitr = itr->second.find(p.seqNum()); //do we have this seq num in our stack?
  return (iitr != itr->second.end()); //return true if we do have it
}

void Host::ReSend(Packet p, double t){
  Packet packet_to_resend(p.fid(), 'D', p.seqNum(), p.GetDst(), p.GetSrc()); 
  SendPacket(packet_to_resend, t);
}
