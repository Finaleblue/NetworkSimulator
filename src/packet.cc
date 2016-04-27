/**
 * CommNets
 * @Author Eui Han
 */
#include <string>
#include <sstream>
#include "packet.h"

Packet::Packet(const std::string id, const Node& src, const Node& dst):
  id_(id),
  type_(id[0]),
  origin_(src),
  dest_(dst),
  seq_num_(atoi(id.substr(1))){}

Packet::Packet(const std::string type, int seq, const Node& src, const Node& dst):{
  sstream out << seq;
  id_ = type + out.str();
  type_ = type;
  seq_ = seq;
  src_ = src;
  dst_ = dst;
}

Node& Packet::GetSrc() const{
  return src_;
}

std::string id() const{
  return id_;
}

Node& Packet::GetDest() const{
  return dest_;
}

int Packet::size() const{
  return size_;
}

int Packet::seqNum() const{
  return seq_num_;
}

std::string Packet::type() const{
  return type_;
}
