/**
 * CommNets
 * @Author Eui Han
 */
#include <string>
#include <sstream>
#include "packet.h"
#include "global.h"

Packet::Packet(std::string flow_id, int flow_num, std::string id, Node& src, Node& dst) :
  fid_(flow_id), id_(id), type_(id[0]), src_(src), seq_(ToSeq(id)), size_(global::PacketSize(type_)), dst_(dst), flow_num_(flow_num)
{}

Packet::Packet(std::string flow_id, int flow_num, char type, int seq, Node& src, Node& dst):
  fid_(flow_id), id_(std::string(1,type) + std::to_string(seq)), type_(type), seq_(seq), src_(src), size_(global::PacketSize(type_)), dst_(dst), flow_num_(flow_num)
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

double Packet::size() const{
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

std::string Packet::fid(){
  return fid_;
}
