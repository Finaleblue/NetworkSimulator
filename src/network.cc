/**
 * Cooper Union Communication Networks Final Project
 * Author: Eui Han
 * Version: 1.4
 **/

#include <iostream>
#include "network.h"

void Network::AddHost(std::string id){
  hosts_.insert({id, Host(id)});
  std::cout<<"Host "<<id<<" added"<<std::endl;
}

void Network::AddRouter(std::string id){
  routers_.insert({id, Router(id)});
  std::cout<<"Router "<<id<<" added"<<std::endl;
}

void Network::AddLink(std::string id, std::string end1_id, std::string end2_id,
                      double datarate, double delay, double buffer){

  Node *end1;
  Node *end2;
  if (end1_id[0] == 'H' || end1_id[0] == 'S' || end1_id[0] == 'T'){
    end1 = &hosts_.at(end1_id);
  }
  else{
    end1 = &routers_.at(end1_id);
  }

  if (end2_id[0] == 'R'){
    end2 = &routers_.at(end2_id);
  }
  else{
    end2 = &hosts_.at(end2_id);
  }
  Link l(id, *end1, *end2, datarate, delay, buffer);
  links_.insert({id,l});
  (*end1).AddNeighbor(l, *end2);
  (*end2).AddNeighbor(l, *end1);
  std::cout<<"Link "<<id<<" added"<<std::endl;

}

void Network::AddFlow(std::string id, double start_time, int size,
                      std::string src_id, std::string dst_id, 
                      std::string protocol){
  Host& src = hosts_.at(src_id);
  Host& dst = hosts_.at(dst_id);
  flows_.insert({id, Flow(id, start_time, size, src, dst, protocol)} );

  std::cout<<"Flow "<<id<<" added"<<std::endl;

}

std::map<std::string, Flow>& Network::GetFlows(){
  return flows_;
}

std::map<std::string, Link>& Network::GetLinks(){
  return links_;
}

std::map<std::string, Router>& Network::GetRouters(){
  return routers_;
}

std::map<std::string, Host>& Network::GetHosts(){
  return hosts_;
}

Link& Network::GetLink(std::string lid){
  return links_.at(lid);
}

Host& Network::GetHost(std::string hid){
  return hosts_.at(hid);
}

Router& Network::GetRouter(std::string rid){
  return routers_.at(rid);
}

Node& Network::GetNode(std::string nid){
  if (nid[0] == 'R'){return GetRouter(nid);}
  else  {return GetHost(nid);}
}

Flow& Network::GetFlow(std::string fid){
  return flows_.at(fid);
}
