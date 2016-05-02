#include <memory>
#include <cfloat>
#include "router.h"
#include "event.h"
#include "event_manager.h"

extern EventManager event_manager;
extern std::ostream *logger;
extern std::ostream *debugSS;

Router::Router(std::string id): Node(id){}

void Router::SendPacket(Packet p, double t) {
  Link& l = GetRoute(p.GetDst().id());
  Node& n = event_manager.Net().GetNode(neighbors_.at(l.id()));
  event_manager.push(std::shared_ptr<TransmitPacketEvent>(new TransmitPacketEvent(l, n, p, t)));
}

void Router::ReceivePacket(Link& from, Packet p, double t){
  from.flush(t);
  UpdateCost();
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
    if(neighbor.first[0] == 'R'){
      cost_.at(neighbor.second) = event_manager.Net().GetLink(neighbor.first).GetCost(); // sum (packetSize/rate)
    }
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
    event_manager.push(std::shared_ptr<Event>(new TransmitPacketEvent(l, n, Packet("FC", -1, 'C', i, *this, n), event_manager.time())));
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
  //*debugSS<<"GREEDY"<<id_<<std::endl;
  double min_cost = DBL_MAX;
  std::string min_link; 
  for( auto lid : links_){
    Link& l = event_manager.Net().GetLink(lid);   

    if (l == *received_from_) 
    {continue;}
    //*debugSS<<"GREEDY1.1"<<neighbors_.at(lid)<<std::endl;
    if (neighbors_.at(lid)[0] == 'H' || neighbors_.at(lid)[0] == 'T' || neighbors_.at(lid)[0] == 'S'){
      //*debugSS<<"GREEDY2"<<id_<<std::endl;
      //*debugSS<<"hid: "<<hid<<std::endl;
      if (neighbors_.at(lid) == hid){return l;}
      else {continue;}
    }
    
    if (l.GetCost() < min_cost){
      min_cost = l.GetCost();
      min_link = lid;
    }
  }
  if (min_link == "") {return *received_from_;}
  return event_manager.Net().GetLink(min_link);
}


void Router::Init(){
  std::map<std::string, double> inner;
  for (auto &itr : event_manager.Net().GetHosts()){
   //   std::cout<<
    for(auto &iitr : links_){
      if(neighbors_.at(iitr) == itr.first){ // if i am connected to a host,
        inner.insert({itr.first, 0});    // set distance to 0
      }
      else{
        inner.insert({itr.first, 1000000});  //set distance to every other host to million
      }
    }
  }

  routing_table_.insert({id_, inner});
  
  std::map<std::string, double> inner2;
  for (auto &itr : nodes_){ //for all my neighbor nodes
    if(itr[0] == 'H' || itr[0] == 'S' || itr[0] == 'T'){ // hosts do not have a routing table
      continue;
    }
    else{
      for(auto &h : event_manager.Net().GetHosts()){
        inner2.insert({h.first, 1000000}); // make everything million
      }
      routing_table_.insert({itr, inner2});
    }
  }

  for (auto &neighbor : nodes_){ //initialize the cost vector <neighboring router id, link cost>
  //  std::cout<<"r_table: {"<<neighbor<<", inner}"<<std::endl;
    if(neighbor[0] =='R'){
      cost_.insert({neighbor, 1000000});
    }
  }

  for(auto &itr : event_manager.Net().GetHosts()){
      for(auto &iitr : links_){
        if (itr.first == neighbors_.at(iitr)){
          next_hop_.insert({itr.first, iitr});
        }
        else{
          next_hop_.insert({itr.first, "DNE"}); //Does Not Exist
        }
      }
  }
  UpdateCost();
}






