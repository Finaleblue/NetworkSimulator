#ifndef HOST_H_
#define HOST_H_

#include "node.h"
#include "event.h"
#include "event_manager.h"

class Host: public Node{
  private:
    EventManager event_manager;
  public:
    Host(const std::string id);
    void SendPacket(const Packet &p, const double time);
    void RecievePacket(const Packet &p, const double time);
    bool allowedToTransmit();
};
#endif
