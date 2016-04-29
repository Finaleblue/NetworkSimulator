/**
 * CommNets
 * node.cc
 * 
 * @author Eui Han
 * @version 0.1 04/05/16
 */

#include "node.h"
#include "packet.h"
#include "link.h"

Node::Node(const std::string id) : id_(id){}
Node::~Node(){}

void Node::AddNeighbor(Node &n, Link &l){
  neighbors_.insert({n.id(),l});
  AddLink(l);
  AddNode(n);
}

void Node::AddLink(Link &l){
  links_.emplace(l.id(),l);
}

void Node::AddNode(Node &n){
  nodes_.emplace(n.id(), n);
}
std::string Node::id() const{
  return id_;
}
std::map<std::string, Link&> Node::GetLinks(){
  return links_;
}

std::map<std::string, Node&> Node::GetConnectedNodes(){
  return nodes_;
}

void Node::SendPacket(Packet, double) const{}
void Node::ReceivePacket(Packet, double){}

  
