#ifndef ROUTER_H_
#define ROUTER_H_

class Network;
class Packet;
class Link;
#include "node.h"
#include <map>

class EventManager;
extern EventManager event_manager;
class Router: public Node{
  public:
    Router(const std::string id);
    void SendPacket(const Link &target, const Packet p, double time) const;
    void ReceivePacket(const Packet p, double time);
    bool allowedToTransmit();
    Link& GetRoute(std::string); // looks up the routing table and returns the link
    void UpdateTable(std::string); // updates the routing table every x time step
    void UpdateCost();
    void SendControl() const;
    void ReceiveControl(const Packet p);
    std::map<std::string, double> RoutingVector();
  private:
    //each row represents each router's dist_ + cost_ vector
    std::map<const std::string, std::map<std::string, double> > routing_table_;

    //map <neighbor id, link cost>
    std::map<const std::string, double> cost_;
    
    //map <host id, distance int>
    std::map<const std::string, int> dist_;

    //map <hst id, neighbor id>
    std::map<const std::string, std::string> next_hop_;
};
#endif
