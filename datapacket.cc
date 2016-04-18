#include "datapacket.h"

DataPacket(std::string id, node* src, node* dst, flow* fl, bool timeout){
  id_ = id;
  origin_ = src;
  dest_ = dst;
  flow_ = fl;
  timeout_ = timeout;
}
