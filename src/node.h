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
    bool operator == (const Node&) const;
    virtual ~Node();
    void AddLink(Link&);
    void AddNode(Node&);
    void AddNeighbor(Link&, Node&);
    std::string id() const;
    std::map<std::string, std::string> GetLinks();
    std::map<std::string, std::string> GetConnectedNodes();
    virtual bool SendPacket(Packet, double);
    virtual bool ReceivePacket(Packet, double);

  protected:
    Node(std::string id);
    int bits_sent_=0;
    std::string id_;
    double  time_=-1;
    //maps id of each device to the actual object
    std::map<std::string, std::string> neighbors_; //map <link id, node id>
    std::vector<std::string> nodes_; //vector <node id> 
    std::vector<std::string> links_; //vector <link id>
    std::vector<Packet> received_packets_;
    // bool routerorhostnode?
};

#endif
