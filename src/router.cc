#include "router.h"
#include "event.h"
#include "event_manager.h"

Router::Router(const std::string id): Node(id){}

void Router::SendPacket(const Link& target, const Packet &p, double time) const{
  event_manager.push(TransmitPacketEvent(target, p, time));
}

void Router::ReceivePacket(const Packet &p, double time){
  if (p.type() == "C"){ //if the received packet is control type
    ReceiveControl(p);
  }
  else{
    SendPacket(GetRoute(p.GetDst().id()), p, time);
  }
} 

bool Router::allowedToTransmit(){
  //return links_[0].isAvailable();
}

Link& Router::GetRoute(std::string host_id){
  return links_[next_hop_[host_id]];
}

//separate vectors for router and host?
void Router::UpdateTable(std::string router_id){
  routing_table_[router_id] = dynamic_cast<Router&>(nodes_[router_id]).RoutingVector();
  UpdateCost();
}

//Implementation of Bellman-Ford
void Router::UpdateCost(){ // updates cost vector every time step
  for(auto const &neighbor : neighbors_){
    cost_[neighbor.first] = neighbor.second.GetCost(); // sum (packetSize/rate)
  }
  for(auto const r : routing_table_){
    for(auto const &c : r.second){
      double temp = c.second + cost_[r.first];
        if (temp < routing_table_[Node::id_][c.first]){
          routing_table_[Node::id_][c.first] = temp;
          next_hop_[c.first] = r.first;
        }
    }
  }
}

void Router::SendControl() const{
  int i = 0;
  for(auto const &node : nodes_){
    event_manager.push(ReceivePacketEvent(node.second, Packet('C', i, *this, node.second), event_manager.global_time()));
    ++i;
  }
}

void Router::ReceiveControl(const Packet& p){
  UpdateTable(p.GetSrc().id());
}

std::map<std::string, double> Router::RoutingVector() const{
  return routing_table_[Node::id_];
}


//initiate with greedy algorithm
