#include "network.h"
#include <iostream>
Network::Network() : debug_(1){}

void Network::AddHost(std::string id){
  devices_.insert({id, Host(id)});
}

void Network::AddRouter(std::string id){
  devices_.insert({id, Router(id)});
}

void Network::AddLink(std::string id, std::string end1_id, std::string end2_id,
                      double datarate, double delay, double buffer){

  Node& end1 = devices_.at(end1_id);
  Node& end2 = devices_.at(end2_id);

  links_.insert({id, Link(id, end1, end2, datarate, delay, buffer)});
}

void Network::AddFlow(const std::string id, double start_time, int size,
                      const std::string src_id, const std::string dst_id, 
                      std::string protocol){

  Node& src = devices_.at(src_id);
  Node& dst = devices_.at(dst_id);
  flows_.insert({id, Flow(id, start_time, size, dynamic_cast<Host&>(src), dynamic_cast<Host&>(dst), protocol)} );
}

std::map<std::string, Flow> Network::GetFlows() const{
  return flows_;
}

std::map<std::string, Link> Network::GetLinks() const{
  return links_;
}

std::map<std::string, Node> Network::GetDevices() const{
  return devices_;
}

void Network::debug(){
  std::cout<<debug_<<std::endl;
}

