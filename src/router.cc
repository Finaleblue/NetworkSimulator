#include "router.h"
#include "link.h"
#include "global.h"
#include <vector>

Router::Router(const std::string id): Node(id){}


void Router::SendPacket(Node& target, const Packet &p, const double time){
  event_manager.push(ReceivePacketEvent(target, p, time));
}

void Router::ReceivePacket(const Packet &p, const double time){
  if (p.type() == "C"){ //if the received packet is control type
    ReceiveControl(p);
  }
  else{
    SendPacket(GetRoute(p.GetDst().id()), p, time);
  }
} 

bool Router::allowedToTransmit(){
  return links_[0].isAvailable();
}

Link& Router::GetRoute(std::string host_id){
  return next_hop_[host_id];
}

//separate vectors for router and host?
void Router::UpdateTable(std::string router_id){
  routing_table[router_id] = nodes_[router_id].RoutingVector();
  UpdateCost()
}

//Implementation of Bellman-Ford
void Router::UpdateCost(){ // updates cost vector every time step
  for(auto const &neighbor : neighbors_){
    cost_[neighbor.first] = neighbor.second.GetCost(); // sum (packetSize/rate)
  }
  for(auto const &r : routing_table_){
    for(auto const &c : routers.second){
      double temp = c.second + costs_[r];
        if (temp < routing_table_[id][c.first]){
          routing_table_[id][c.first] = temp;
          next_hop_[c.first] = r;
        }
    }
  }
}

void Router::SendControl() const{
  int i = 0;
  for(auto const &node : nodes_){
    event_manager.push(ReceivePacketEvent(node, Packet("C", i, *this, node), event_manager.global_time()));
    ++i;
  }
}

void Router::ReceiveControl(Packet& p){
  UpdateTable(p.GetSrc().id());
}

//initiate with greedy algorithm
