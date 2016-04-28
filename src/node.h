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
    Node(const std::string id);
    void AddLink(const Link&);
    void AddNode(const Node&);
    void AddNeighbor(const Node&, const Link&);
    std::string id() const;
    std::map<std::string, const Link&> GetLinks();
    std::map<std::string, const Node&> GetConnectedNodes();
    void SendPacket(const Node&, const Packet, double) const;
    void ReceivePacket(const Packet, double);

  protected:
    int bits_sent_=0;
    const std::string id_;
    double  time_=-1;
    //maps id of each device to the actual object
    std::map<std::string, const Link&> neighbors_; 
    std::map<std::string, const Node&> nodes_;
    std::map<std::string, const Link&> links_;
    std::map<std::string, Packet> received_packets_;
    // bool routerorhostnode?
};

#endif
