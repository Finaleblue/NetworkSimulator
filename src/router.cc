#include <memory>
#include <cfloat>
#include "router.h"
#include "event.h"
#include "event_manager.h"

extern EventManager event_manager;

Router::Router(std::string id): Node(id){}

void Router::SendPacket(Packet p, double t) {
  Link& l = GetRoute(p.GetDst().id());
  Node& n = event_manager.Net().GetNode(neighbors_.at(l.id()));
  event_manager.push(std::shared_ptr<TransmitPacketEvent>(new TransmitPacketEvent(l, n, p, t)));
}

void Router::ReceivePacket(Link& from, Packet p, double t){
  from.flush(t);
  received_from_ = &from;
  if (p.type() == 'C'){ //if the received packet is control type
     ReceiveControl(p);
  }
  else{
     SendPacket(p, t);
  }
  if (t > last_control_ + 20){
    last_control_ = t;
    SendControl();
   }
} 

bool Router::allowedToTransmit(){
  //return links_[0].isAvailable();
}

Link& Router::GetRoute(std::string host_id){
  auto itr = next_hop_.find(host_id);
  if(itr->second == "DNE"){
    //if no info on the routing table, just be greedy
    Link& l = Greedy(host_id);
    next_hop_.at(host_id) = l.id();
    return l;
  }
  std::string lid;
  return event_manager.Net().GetLink(next_hop_.at(host_id));
}

//separate vectors for router and host?
void Router::UpdateTable(std::string router_id){
  routing_table_.at(router_id) = event_manager.Net().GetRouter(router_id).RoutingVector();
  UpdateCost();
}

//Implementation of Bellman-Ford
void Router::UpdateCost(){ // updates cost vector every time step
  bool updated = false;
  for(auto &neighbor : neighbors_){
    cost_.at(neighbor.second) = event_manager.Net().GetLink(neighbor.first).GetCost(); // sum (packetSize/rate)
  }
  for(auto &r : routing_table_){
    for(auto &c : r.second){
      if(r.first == id_){continue;} //dont need to calculate the Cost to itself
      double temp = c.second + cost_.at(r.first);
      if (temp < routing_table_.at(id_).at(c.first)){ 
        routing_table_.at(id_).at(c.first) = temp;
        std::string lid;
        for (auto &itr : neighbors_){
          if (r.first == itr.second){
            lid = itr.first;
            break;
          }
        }
        next_hop_.at(c.first) = lid;
        updated = true;
     }
    }
  }
  //if (updated)  {SendControl();}  possibly this can congest the whole network 
}

void Router::SendControl(){
  int i = 0;
  for(auto &link : links_){
    Link& l = event_manager.Net().GetLink(link);
    Node& n = event_manager.Net().GetNode(neighbors_.at(link));
    event_manager.push(std::shared_ptr<Event>(new TransmitPacketEvent(l, n, Packet("FC", 'C', i, *this, n), event_manager.time())));
    ++i;
  }
}

void Router::ReceiveControl(Packet p){
  UpdateTable(p.GetSrc().id());
}

std::map<std::string, double> Router::RoutingVector() const{
  return routing_table_.at(id_);
}

//initiate with greedy algorithm
Link& Router::Greedy (std::string hid){
  double min_cost = DBL_MAX;
  std::string min_link; 
  for( auto lid : links_){
    Link& l = event_manager.Net().GetLink(lid);   
    if (l.GetConnectedNode(*this).id() == hid)
    {return l;}
    if (l == *received_from_) 
    {continue;}
    
    if (l.GetCost() < min_cost) {
      min_cost = l.GetCost();
      min_link = lid;
    }
  }
  return event_manager.Net().GetLink(min_link);
}


void Router::Init(){
  std::map<std::string, double> inner;
  for (auto &itr : event_manager.Net().GetHosts()){
   //   std::cout<<
    for(auto &iitr : nodes_){
      if(itr.first == iitr){
        inner.insert({itr.first, 0});
      }
    
      else{
        inner.insert({itr.first, 1000000});
      }
    }
  }
  for (auto &neighbor : nodes_){
  //  std::cout<<"r_table: {"<<neighbor<<", inner}"<<std::endl;
    routing_table_.insert({neighbor, inner});
    cost_.insert({neighbor, 1000000});
  }
  for(auto &itr : event_manager.Net().GetHosts()){
      for(auto &iitr : nodes_){
        if (itr.first == iitr){
          next_hop_.insert({itr.first, itr.second.GetLink().id()});
        }
        else{
          next_hop_.insert({itr.first, "DNE"}); //Does Not Exist
        }
      }
  }
  routing_table_.insert({id_, inner});
  cost_.insert({id_, 1000000});
  UpdateCost();
}

















