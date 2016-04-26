/**
 * CommNets
 * @Author Eui Han
 */
#ifndef PACKET_H_
#define PACKET_H_
#include <string>
#include "node.h"

class Packet{
  private:
    const std::string id_;
    const std::string type_; //indicates if it is ACK or Data
    const Node* origin_;//sender of the packet(same as the sender of the flow)
    const Node* dest_;//destination of the packet (same as the destination of the flow)
    const int size_; //size of the packet. Unit: bits
    const int seq_num_; //The sequence number of the packet.
  public:
    //constructors
    Packet(const std::string id, const Node* src, const Node* dst);
    Packet(const std::string type, int seq, const Node* src, const Node* dst);
    
    //functions
    Node* GetSrc() const; //returns the sender info
    Node* GetDst() const; //returns the destination info
    int size() const; //returns the size of the packet
    int seqNum() const; //returns sequence number of this packet
    std::string id() const;
    std::string type() const; // returns the type of the packet
    
};
#endif
