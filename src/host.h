#ifndef HOST_H_
#define HOST_H_

#include "node.h"
class EventManager;
extern EventManager event_manager;

class Host: public Node{
  public:
    Host(const std::string id);
    void SendPacket(Packet, double);
    void RecievePacket(Packet, double);
    bool allowedToTransmit() const;
};
#endif
