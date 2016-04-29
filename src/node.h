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
class Link;
class Packet;

class Node{
  public: 
    Node(std::string id);
    virtual ~Node();
    void AddLink(Link&);
    void AddNode(Node&);
    void AddNeighbor(Node&, Link&);
    std::string id() const;
    std::map<std::string, Link&> GetLinks();
    std::map<std::string, Node&> GetConnectedNodes();
    virtual void SendPacket(Packet, double) const;
    virtual void ReceivePacket(Packet, double);

  protected:
    int bits_sent_=0;
    std::string id_;
    double  time_=-1;
    //maps id of each device to the actual object
    std::map<std::string, Link&> neighbors_; 
    std::map<std::string, Node&> nodes_;
    std::map<std::string, Link&> links_;
    std::vector<Packet> received_packets_;
    // bool routerorhostnode?
};

#endif
