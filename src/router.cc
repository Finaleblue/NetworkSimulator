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
} 

bool Router::allowedToTransmit(){
  //return links_[0].isAvailable();
}

Link& Router::GetRoute(std::string host_id){
  std::map<std::string, std::string>::iterator itr = next_hop_.find(host_id);
  if(itr == next_hop_.end()) {return Greedy();}
  std::string lid = neighbors_.at(itr->second);
  return event_manager.Net().GetLink(lid);
}

//separate vectors for router and host?
void Router::UpdateTable(std::string router_id){
  routing_table_.at(router_id) = event_manager.Net().GetRouter(router_id).RoutingVector();
  UpdateCost();
}

//Implementation of Bellman-Ford
void Router::UpdateCost(){ // updates cost vector every time step
  for(auto const &neighbor : neighbors_){
    cost_.at(neighbor.second) = event_manager.Net().GetLink(neighbor.first).GetCost(); // sum (packetSize/rate)
  }
  for(auto const &r : routing_table_){
    for(auto const &c : r.second){
      double temp = c.second + cost_.at(r.first);
        if (temp < routing_table_.at(Node::id_).at(c.first)){
          routing_table_.at(id_).at(c.first) = temp;
          next_hop_.at(c.first) = r.first;
        }
    }
  }
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
  return routing_table_.at(Node::id_);
}

//initiate with greedy algorithm
Link& Router::Greedy(){
  double min_cost = DBL_MAX;
  std::string min_link; 
  for( auto lid : links_){
    Link& l = event_manager.Net().GetLink(lid);   
    if (l == *received_from_) {continue;}
    if (l.GetCost() < min_cost) {
      min_cost = l.GetCost();
      min_link = lid;
    }
  }
  return event_manager.Net().GetLink(min_link);
}

