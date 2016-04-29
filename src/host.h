#ifndef HOST_H_
#define HOST_H_

#include "node.h"

class Host: public Node{
  public:
    Host(const std::string id);
    virtual bool SendPacket(Packet, double);
    virtual bool ReceivePacket(Packet, double);
    bool allowedToTransmit() const;
};
#endif
