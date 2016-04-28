#ifndef HOST_H_
#define HOST_H_

#include "node.h"
#include "event_manager.h"

extern EventManager event_manager;
class Host: public Node{
  public:
    Host(const std::string id);
    void SendPacket(const Link&, const Packet, double);
    void RecievePacket(const Packet, double);
    bool allowedToTransmit() const;
};
#endif
