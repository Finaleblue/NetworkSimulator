/**
 * CommNets
 * node.cc
 * 
 * @author Eui Han
 * @version 0.1 04/05/16
 */
#include <iostream>
#include "node.h"
#include "packet.h"
#include "link.h"

Node::Node(const std::string id) : id_(id){}
Node::~Node(){}

bool Node::operator == (const Node& n) const{
  return n.id() == (*this).id();
}

void Node::AddNeighbor(Link &l, Node &n){
  neighbors_.insert({l.id(),n.id()});
  AddLink(l);
  AddNode(n);
}

void Node::AddLink(Link &l){
  links_.push_back(l.id());
}

void Node::AddNode(Node &n){
  nodes_.push_back(n.id());
}
std::string Node::id() const{
  return id_;
}

bool Node::SendPacket(Packet, double){std::cout<<"node flag"<<std::endl;}
bool Node::ReceivePacket(Packet, double){}

  
