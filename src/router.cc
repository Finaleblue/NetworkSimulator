#include <memory>
#include "router.h"
#include "event.h"
#include "event_manager.h"

extern EventManager event_manager;

Router::Router(const std::string id): Node(id){}

bool Router::SendPacket(Packet p, double t) {
  Link& l = GetRoute(p.GetDst().id());
  event_manager.push(std::shared_ptr<Event>(new TransmitPacketEvent(l, l.GetConnectedNode(*this), p, t)));
  return true;
}

bool Router::ReceivePacket(Packet p, double time){
  if (p.type() == "C"){ //if the received packet is control type
    return ReceiveControl(p);
  }
  else{
    return SendPacket(p, time);
  }
} 

bool Router::allowedToTransmit(){
  //return links_[0].isAvailable();
}

Link& Router::GetRoute(std::string host_id){
  return Node::links_.at(next_hop_.at(host_id));
}

//separate vectors for router and host?
void Router::UpdateTable(std::string router_id){
  routing_table_.at(router_id) = dynamic_cast<Router&>(Node::nodes_.at(router_id)).RoutingVector();
  UpdateCost();
}

//Implementation of Bellman-Ford
void Router::UpdateCost(){ // updates cost vector every time step
  for(auto const &neighbor : Node::neighbors_){
    cost_.at(neighbor.first) = neighbor.second.GetCost(); // sum (packetSize/rate)
  }
  for(auto const &r : routing_table_){
    for(auto const &c : r.second){
      double temp = c.second + cost_.at(r.first);
        if (temp < routing_table_.at(Node::id_).at(c.first)){
          routing_table_.at(Node::id_).at(c.first) = temp;
          next_hop_.at(c.first) = r.first;
        }
    }
  }
}

bool Router::SendControl(){
  int i = 0;
  for(auto &node : nodes_){
    event_manager.push(std::shared_ptr<Event>(new ReceivePacketEvent(node.second, Packet("C", i, *this, node.second), event_manager.time())));
    ++i;
  }
  return true;
}

bool Router::ReceiveControl(Packet p){
  UpdateTable(p.GetSrc().id());
  return true;
}

std::map<std::string, double> Router::RoutingVector() const{
  return routing_table_.at(Node::id_);
}


//initiate with greedy algorithm
