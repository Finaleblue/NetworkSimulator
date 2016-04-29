#include <memory>
#include "router.h"
#include "event.h"
#include "event_manager.h"

extern EventManager event_manager;

Router::Router(const std::string id): Node(id){}

void Router::SendPacket(Packet p, double t) {
  Link& l = GetRoute(p.GetDst().id());
  event_manager.push(std::shared_ptr<Event>(new TransmitPacketEvent(l, l.GetConnectedNode(*this), p, t)));
  return;
}

void Router::ReceivePacket(Packet p, double time){
  if (p.type() == 'C'){ //if the received packet is control type
     ReceiveControl(p);
  }
  else{
     SendPacket(p, time);
  }
} 

bool Router::allowedToTransmit(){
  //return links_[0].isAvailable();
}

Link& Router::GetRoute(std::string host_id){
  std::string lid = neighbors_.at(next_hop_.at(host_id));
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
  for(auto &node : nodes_){
    Node& n = event_manager.Net().GetNode(node);
    event_manager.push(std::shared_ptr<Event>(new ReceivePacketEvent(n, Packet('C', i, *this, n), event_manager.time())));
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


