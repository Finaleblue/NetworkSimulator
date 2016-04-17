/**
 * CommNets
 * @Author Eui Han
 */
#include <string>
#include <sstream>
#include "packet.h"

Packet(std::string id, Node* src, Node* dst){
  id_ = id;
  type_ = id[0];
  origin_ = src;
  dest_ = dst;
  seq_num_ = atoi(id.substr(1));
}

Packet(std::string type, int seq, Node* src, Node* dst){
  sstream out << seq;
  type_ = type + out.str();
  seq_ = seq;
  src_ = src;
  dst_ = dst;
}

Node* GetSrc(){
  return src;
}

Node* GetDest(){
  return dest_;
}
int size(){
  return size_;
}
int seqNum(){
  return seq_num_;
}
