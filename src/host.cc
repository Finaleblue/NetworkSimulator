#include <memory>
#include <string>
#include "host.h" 
#include "link.h"
#include "event.h"
#include "event_manager.h"
#include "global.h"

extern EventManager event_manager;
extern std::ostream *debugSS;
extern std::ostream* logger;
Host::Host(std::string id) : Node::Node(id){} 
void Host::SendPacket(Packet p, double t){
  //*debugSS<<"SendPacket Flag"<<std::endl;
  Link& l = event_manager.Net().GetLink(links_[0]);
  Node& n = event_manager.Net().GetNode(neighbors_.at(l.id()));
  if(p.type() == 'D'){
    sent_packets_.insert({p.fid()+p.id(), t}); //keep sent time for RTTE
    event_manager.push(std::shared_ptr<AckTimeoutEvent>
        (new AckTimeoutEvent(*this, Packet(p.fid(), p.flow_num_, 'A', p.seqNum(), p.GetDst(), p.GetSrc()), t+event_manager.Net().GetFlow(p.fid()).TimeOutEst() )));
  }
  event_manager.push(std::shared_ptr<TransmitPacketEvent>(new TransmitPacketEvent(l, n, p, t)));
  /*if(p.type() == 'D'){
    //Start ACK Timer 
  }*/
  return;
}

void Host::ReceivePacket(Link& from, Packet p, double t){
  from.flush(t);
  if(p.type() == 'C') {return;} //host does not respond to a control packet
  ////*debugSS<<"RCV PAckt floag"<<std::endl;
  //*debugSS<<"RCVPCKTFLAG1"<<std::endl;
  if(p.type() == 'D'){ //only execute this when the received packet is a data packet
    auto itr = received_packets_.find(p.fid());
    if (itr == received_packets_.end()){ //if this is the first packet of the flow
      std::set<int> subset; 
      subset.insert(p.seqNum());
      received_packets_.insert({p.fid(), subset});
      next_ack_.insert({p.fid(), p.seqNum()});
      NextAck(p.fid());
      /*event_manager.push(
          std::shared_ptr<AckTimeoutEvent>(
            new AckTimeoutEvent(*this, Packet(p.fid(), 'A', p.seqNum(), p.GetSrc(), p.GetDst()), t + event_manager.Net().GetFlow(p.fid()).TimeOutEst())));*/
      SendPacket(Packet(p.fid(), p.flow_num_, 'A', next_ack_.at(p.fid()), *this, p.GetSrc()),t);
    }
    else{
      //*logger<<"host flag1"<<std::endl;
      received_packets_.at(p.fid()).insert(p.seqNum()); // record the received packet seq num
      if (p.seqNum() >= next_ack_.at(p.fid())){
        NextAck(p.fid());
        SendPacket(Packet(p.fid(), p.flow_num_, 'A', next_ack_.at(p.fid()), *this, p.GetSrc()),t);
      }
    }
  }
  else if (p.type() == 'A'){
    //*logger<<"trigger next flow: "<<p.flow_num_+1<<std::endl;
    event_manager.push(std::shared_ptr<FlowStartEvent>(
        new FlowStartEvent(event_manager.Net().GetFlow(p.fid()), p.flow_num_+1, t)));
    //std::cout<<"ACK RECEIVED"<<p.id()<<std::endl;
    if(ack_stack_.find(p.fid()) == ack_stack_.end()){ //if this is the first ack from the flow
    //std::cout<<"first ack of the flow"<<p.id()<<std::endl;
      std::map<int,int> inner;
      inner.insert({p.seqNum(), 1});
      ack_stack_.insert({p.fid(), inner});
      //*debugSS<<"adding ack at: "<<ack_stack_.at(p.fid()).at(p.seqNum())<<std::endl;
    }
    //if this is the first ACK packet for this seq number
    else if(ack_stack_.at(p.fid()).find(p.seqNum()) == ack_stack_.at(p.fid()).end()){
      //*debugSS<<"ACKRCV2"<<p.id()<<std::endl;
      for (int i=1; i<=p.seqNum(); ++i){
        //*debugSS<<"ACKRCV3"<<std::endl;
        ack_stack_.at(p.fid()).insert({i,1});
        //*debugSS<<"ACKRCV3"<<p.id()<<std::endl;
      }
      //std::cout<<"ack added at "<<p.seqNum()<<std::endl;
    }
    else{
      if(++ack_stack_.at(p.fid()).at(p.seqNum()) >= 3){
        if(resent_.find(p.fid()+'A'+std::to_string(p.seqNum()+1)) != resent_.end()) {return;} //if we have already resent this packet, return
        if(p.seqNum() < NextAck(p.fid())) {return;}
        *logger<<"@time: "<< t
               <<", Triple Duplicate of "<<p.fid()<<p.id()<<". Retransmitting Data."<<std::endl;
        event_manager.Net().GetFlow(p.fid()).Congestion(p.flow_num_);
        ack_stack_.at(p.fid()).at(p.seqNum()) = 1;
        ReSend(Packet(p.fid(), p.flow_num_, 'A', p.seqNum()+1, p.GetSrc(), *this), t);
      }
    }
    //Tell flow to update RTTE
    event_manager.Net().GetFlow(p.fid()).RTT_Update(p.flow_num_, t - sent_packets_.at(p.fid()+"D"+std::to_string(p.seqNum()))); 
  }
  else {} //when receive CTRL Packet, do nothing. 
} 

bool Host::allowedToTransmit() const{
  //return links_[0].isAvailable();
  return true;
}

int Host::NextAck(std::string fid){
  auto itr = received_packets_.find(fid);
  if (itr == received_packets_.end()) {return 0;}
  int next_ack = next_ack_.at(fid);
  //*debugSS<<"NEXTACK"<<std::endl;
  while( itr ->second.find(++next_ack) != itr->second.end() ){
  }
  next_ack_.at(fid) = --next_ack;
  //*logger<<fid<<" next ack is "<<next_ack_.at(fid)<<std::endl;
  return next_ack_.at(fid);
}

bool Host::CheckAck(Packet p){
  //*debugSS<<"CHKACK"<<std::endl;
  //*logger<<"looking for ACK: "<<p.fid()<<p.seqNum()<<std::endl;
  auto itr = ack_stack_.find(p.fid()); //for this flow 
  if (itr == ack_stack_.end()) {return false;} //first packet of the flow
  auto iitr = itr->second.find(p.seqNum()); //do we have this seq num in our stack?
  return (iitr != itr->second.end()); //return true if we do have it
}

//Selective repeat. Not, Go Back N.
void Host::ReSend(Packet p, double t){
  if(resent_.find(p.fid() + p.id()) != resent_.end()) {return;}
  Packet packet_to_resend(p.fid(), p.flow_num_, 'D', p.seqNum(), p.GetDst(), p.GetSrc()); 
  resent_.insert(p.fid()+p.id());
  std::map<int, int> inner;
  inner.insert({p.seqNum(),1});
  ack_stack_.insert({p.fid(), inner});
  event_manager.Net().GetFlow(p.fid()).Push(packet_to_resend);
  event_manager.push(
      std::shared_ptr<FlowStartEvent>(new FlowStartEvent(event_manager.Net().GetFlow(p.fid()), p.flow_num_+1, t)));
}

int Host::num_received_packets(){
  return received_packets_.size();
}

Link& Host::GetLink(){
  return event_manager.Net().GetLink(links_[0]);
}
