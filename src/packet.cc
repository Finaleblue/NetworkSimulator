/**
 * CommNets
 * @Author Eui Han
 */
#include <string>
#include <sstream>
#include "packet.h"
#include "global.h"

Packet::Packet(std::string id, Node& src, Node& dst) :
  id_(id), type_(id[0]), src_(src), seq_(ToSeq(id)), size_(global::PacketSize(type_)), dst_(dst)
{}

Packet::Packet(char type, int seq, Node& src, Node& dst):
  id_(std::string(1,type) + std::to_string(seq)), type_(type), seq_(seq), src_(src), size_(global::PacketSize(type_)), dst_(dst)
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

char Packet::type() const{
  return type_;
}

int Packet::ToSeq(std::string id){
  return id[1]-'0';
}
