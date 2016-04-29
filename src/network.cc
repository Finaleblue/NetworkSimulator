#include <iostream>
#include "network.h"

void Network::AddHost(std::string id){
  devices_.insert({id, Host(id)});
  std::cout<<"Host "<<id<<" added"<<std::endl;
}

void Network::AddRouter(std::string id){
  devices_.insert({id, Router(id)});
  std::cout<<"Router "<<id<<" added"<<std::endl;
}

void Network::AddLink(std::string id, std::string end1_id, std::string end2_id,
                      double datarate, double delay, double buffer){

  Node& end1 = devices_.at(end1_id);
  Node& end2 = devices_.at(end2_id);

  links_.insert({id, Link(id, end1, end2, datarate, delay, buffer)});
  std::cout<<"Link "<<id<<" added"<<std::endl;

}

void Network::AddFlow(std::string id, double start_time, int size,
                      std::string src_id, std::string dst_id, 
                      std::string protocol){
  Host& src = static_cast<Host&>(devices_.at(src_id));
  Host& dst = static_cast<Host&>(devices_.at(dst_id));
  flows_.insert({id, Flow(id, start_time, size, src, dst, protocol)} );

  std::cout<<"Flow "<<id<<" added"<<std::endl;

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


