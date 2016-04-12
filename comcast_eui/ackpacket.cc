/**
 * CommNets
 * @author Eui Han
 */

#include "ackpacket.h"

AckPacket(std::string id, node* src, node* dst, flow* fl, Packet* next){
  id_ = id;
  origin_ = src;
  dest_ = dst;
  flow_ = fl;
  next_expected_ = next;
}
