/**
 * CommNets
 * node.cc
 * 
 * @author Eui Han
 * @version 0.1 04/05/16
 */

#include "node.h"

Node(std::string id){
  id_ = id;
}

void AddNeighbor(Node &n, Link &l){
  neighbors_.insert({n.id(),l});
  AddLink(Link()) // TODO:add default link spec
}

void AddLink(Link &l){
  links_.push_back(l);
}

void AddNode(Node &n){
  nodes_.push_back(n);
}
const std::string GetId(){
  return id_;
}
std::vector<links*> GetLinks(){
  return links_;
}

std::vector<Node> GetConnectedNode(){
  return nodes_;
}


virtual void SendPacket(Packet &p, double time, Link &l, Node &dst){}
virtual void ReceivePacket(Packet &p, double time){}


  
