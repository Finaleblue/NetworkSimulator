#ifndef HOST_H_
#define HOST_H_

#include "node.h"
#include "event.h"
#include "event_manager.h"

extern EventManager event_manager;
class Host: public Node{
  public:
    Host(const std::string id);
    void SendPacket(Link&, Packet, double);
    void RecievePacket(Packet, double);
    const bool allowedToTransmit() const;
};
#endif
