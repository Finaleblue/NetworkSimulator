#ifndef ROUTER_H_
#define ROUTER_H_

#include "node.h"
class Network;
class Packet;

class Router: public Node{
  public:
    Router(const std::string id);
    void SendPacket(const Packet &p, const double time);
    void RecievePacket(const Packet &p, const double time);
    bool allowedToTransmit();
    link& GetRoute(Packet&); // looks up the routing table and returns the link
    void UpdateTable(); // updates the routing table every x time step
  private:
    std::unordered_map< std::string /*router id */, std::vector< std::pair<int /*distance*/, std::string /*link to next hop*/> > > routing_table;
    std::vector<int> cost_vector;
};
#endif
