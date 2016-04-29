#ifndef HOST_H_
#define HOST_H_

#include "node.h"

class Host: public Node{
  public:
    Host(const std::string id);
    virtual void SendPacket(Packet, double);
    virtual void ReceivePacket(Packet, double);
    bool allowedToTransmit() const;
};
#endif
