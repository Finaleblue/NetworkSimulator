/**
 * Cooper Union Communication Networks Final Project
 * Author: Eui Han
 * Version: 1.4
 **/
#ifndef LINK_H_
#define LINK_H_

class Node;
#include "packet.h"
#include <queue>

class Link{
  public:
    bool operator == (Link& l){ return l.id() == this->id();}
    Link(std::string, Node&, Node&, double, double, double);
    bool isAvailable() const;
    void ReceivePacket(Node&, Packet, double);
    void SendPacket(Node&, Packet, double);
    void DoneTransmitting();
    double GetCost() const;
    double rate();
    std::string id() const;
    Node& GetConnectedNode(Node&) const;
    void flush(double);
  private:
    std::string id_;
    double datarate_;
    double buffer_size_;
    double occupancy_=0;
    double delay_;
    Node& end1_;
    Node& end2_;
    bool transmitting_ = false;
    int num_packs_in_buffer_ = 0; 
    std::queue<std::pair<Packet,Node&> > buffer_;
    std::ofstream *OCCUPANCYSS_;
    std::ofstream *LOSTPACKSS_;
     
};
#endif
