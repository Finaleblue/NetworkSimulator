#include "network.h"

void Network::AddHost(const std::string id){
  devices_.insert(id, Host(id));
}

void Network::AddRouter(const std::string id){
  devices_.insert(id, Router(id));
}

void Network::AddLink(const std::string id, const std::string end1_id, const std::string end2_id,
                      double datarate, double delay, double buffer){

  Node& end1 = devices_.at(end1_id);
  Node& end2 = devices_.at(end2_id);

  links_.insert(id, Link(id, end1, end2, datarate, delay, buffer));
}

void Network::AddFlow(const std::string id, double start_time, int size,
                      const std::string src_id, const std::string dst_id, 
                      std::string protocol){

  Node& src = devices_.at(src_id);
  Node& dst = devices_.at(dst_id);
  flows_.insert(id, Flow(id, start_time, size, dynamic_cast<Host&>(src), dynamic_cast<Host&>(dst), protocol) );
}

std::map<Flow>& Network::GetFlows() const{
  return flows_;
}

std::map<Link>& Network::GetLinks() const{
  return links_;
}

std::map<Node>& Network::GetDevices() const{
  return devices_;
}

