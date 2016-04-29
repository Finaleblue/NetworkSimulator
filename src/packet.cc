/**
 * CommNets
 * @Author Eui Han
 */
#include <string>
#include <sstream>
#include "packet.h"
#include "global.h"

Packet::Packet(std::string id, Node& src, Node& dst) :
  id_(id), type_(ToType(id)), src_(src), seq_(ToSeq(id)), size_(global::PacketSize(type_)), dst_(dst)
{}

Packet::Packet(std::string type, int seq, Node& src, Node& dst):
  id_(type + std::to_string(seq)), type_(type), seq_(seq), src_(src), size_(global::PacketSize(type_)), dst_(dst)
{}

Node& Packet::GetSrc() const{
  return src_;
}

std::string Packet::id() const{
  return id_;
}

Node& Packet::GetDst() const{
  return dst_;
}

int Packet::size() const{
  return size_;
}

int Packet::seqNum() const{
  return seq_;
}

std::string Packet::type() const{
  return type_;
}

std::string Packet::ToType(std::string id){
  std::stringstream ss;
  ss<<id[0];
  std::string s;
  ss>>s;
  return s;
}

int Packet::ToSeq(std::string id){
  return id[1]-'0';
}
