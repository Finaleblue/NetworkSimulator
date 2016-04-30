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
  last_transmit_time_ = t; //keep sent time for RTTE
  event_manager.push(std::shared_ptr<TransmitPacketEvent>(new TransmitPacketEvent(l, n, p, t)));
  if(p.type() == 'D'){
    //Start ACK Timer 
    event_manager.push(std::shared_ptr<AckTimeoutEvent>(new AckTimeoutEvent(*this, Packet(p.fid(), 'A', p.seqNum(), p.GetDst(), p.GetSrc()), t+event_manager.Net().GetFlow(p.fid()).RTTE() )));
  }
  return;
}

void Host::ReceivePacket(Link& from, Packet p, double t){
  from.flush(t);
  if(p.type() == 'D'){ //only execute this when the received packet is a data packet
    auto itr = received_packets_.find(p.fid());
    if (itr == received_packets_.end()){ //if this is the first packet of the flow
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
    //std::cout<<"ACK RECEIVED"<<std::endl;
    if(ack_stack_.find(p.fid()) == ack_stack_.end()){ //if this is the first ack from the flow
    //std::cout<<"first ack of the flow"<<std::endl;
      std::map<int,int> inner;
      inner.insert({p.seqNum(), 1});
      ack_stack_.insert({p.fid(), inner});
      //std::cout<<"adding ack at: "<<ack_stack_.at(p.fid()).at(p.seqNum())<<std::endl;
    }
    else if(ack_stack_.at(p.fid()).find(p.seqNum()) == ack_stack_.at(p.fid()).end()){
      ack_stack_.at(p.fid()).insert({p.seqNum(),1});
      //std::cout<<"ack added at "<<p.seqNum()<<std::endl;
    }
    else{
      if(++ack_stack_.at(p.fid()).at(p.seqNum()) >= 3){
        std::cout<<"Triple Duplicate of "<<p.fid()<<p.id()<<". Retransmit."<<std::endl;
        event_manager.Net().GetFlow(p.fid()).Congestion();
        ReSend(Packet(p.fid(), 'D', p.seqNum(), *this, p.GetSrc()), t);
      }
    }
    //Tell flow to update RTTE
    event_manager.Net().GetFlow(p.fid()).RTT_Update(t - last_transmit_time_); 
  }
  else {} //when receive CTRL Packet, do nothing. 
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
//  std::cout<<"looking for ACK: "<<p.fid()<<p.seqNum()<<std::endl;
  auto itr = ack_stack_.find(p.fid()); //for this flow 
  if (itr == ack_stack_.end()) {std::cout<<"ACK fid"<<p.fid()<<"was not found"<<std::endl;return false;} //first packet of the flow
  auto iitr = itr->second.find(p.seqNum()); //do we have this seq num in our stack?
  return (iitr != itr->second.end()); //return true if we do have it
}

//Selective repeat. Not, Go Back N.
void Host::ReSend(Packet p, double t){
  Packet packet_to_resend(p.fid(), 'D', p.seqNum(), p.GetDst(), p.GetSrc()); 
  SendPacket(packet_to_resend, t);
}

int Host::num_received_packets(){
  return received_packets_.size();
}

Link& Host::GetLink(){
  return event_manager.Net().GetLink(links_[0]);
}
