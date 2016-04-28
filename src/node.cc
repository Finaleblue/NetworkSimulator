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

void Node::AddNeighbor(const Node &n, const Link &l){
  neighbors_.emplace(n.id(),l);
  AddLink(l);
  AddNode(n);
}

void Node::AddLink(const Link &l){
  links_.emplace(l.id(),l);
}

void Node::AddNode(const Node &n){
  nodes_.emplace(n.id(), n);
}
std::string Node::id() const{
  return id_;
}
std::map<std::string, const Link&> Node::GetLinks(){
  return links_;
}

std::map<std::string, const Node&> Node::GetConnectedNodes(){
  return nodes_;
}

void Node::SendPacket(const Node&, const Packet, double) const{}
void Node::ReceivePacket(const Packet p, double){}


  
