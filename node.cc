/**
 * CommNets
 * node.cc
 * 
 * @author Eui Han
 * @version 0.1 04/05/16
 */

#include "node.h"

Node(std::string id){
  name_ = id;
}
 
Node GetConnectedNode(){
  return neighbors_;
}

int AddNeighbor(Node &n){
  neighbors_.push_back(&n);
  AddLink(Link( // TODO:add default link spec)
  return 0;
}

int AddLink(Link &l){
  links_.push_back(&l);
  return 0;
}

void SendPacket(Packet &p){
  
}


  
