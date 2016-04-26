#ifndef ROUTER_H_
#define ROUTER_H_

#include "node.h"
#include "event_manager.h"
class Network;
class Packet;

class Router: public Node{
  public:
    Router(const std::string id);
    void SendPacket(const Node &target, const Packet &p, const double time);
    void RecievePacket(const Node &target, const Packet &p, const double time);
    bool allowedToTransmit();
    link& GetRoute(std::string); // looks up the routing table and returns the link
    void UpdateTable(); // updates the routing table every x time step
    void UpdateCost();
    void SendControl();
    void ReceiveControl(Packet& p);
  private:
    //each row represents each router's dist_ + cost_ vector
    std::map<std::string, std::map<std::string, double> > routing_table_;

    //map <neighbor id, link cost>
    std::map<std::string, double> cost_;
    
    //map <host id, distance int>
    std::map<std::string, int> dist_;

    //map <host id, neighbor id>
    std::map<std::string, std::string> next_hop_;
};
#endif
