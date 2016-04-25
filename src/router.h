#ifndef ROUTER_H_
#define ROUTER_H_

#include "node.h"
class Packet;

class Router: public Node{
  public:
    Router(const std::string id);
    void SendPacket(const Packet &p, const double time);
    void RecievePacket(const Packet &p, const double time);
    bool allowedToTransmit();
};
#endif
