/**
 * CommNets
 * node.h
 * Purpose: Nodes are points of the network, i.e. hosts and routers
 * 
 * @author Eui Han
 * @version 0.1 04/05/16
 */

#ifndef NODE_H_
#define NODE_H_

#include <map>
#include <vector>
#include "link.h"
#include "packet.h"
class EventManager;

extern EventManager event_manager;
class Node{
  public: 
    Node(const std::string id);
    void AddLink(Link&);
    void AddNode(Node&);
    const std::string GetId();
    std::vector<Link> GetLinks();
    std::vector<Node> GetConnectedNodes();
    virtual void SendPacket(Packet&, double);
    virtual void RecievePacket(Packet&, double);

  protected:
    int bits_sent_=0;
    const std::string id_;
    double  time_=-1;
    //maps id of each device to the actual object
    std::map<std::string, Link&> neighbors_; 
    std::map<std::string, Node> nodes_;
    std::map<std::string, Link> links_;
    std::map<std::string, Packet> received_packets_;
    // bool routerorhostnode?
};

#endif
