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
    std::string id_;
    std::string type_; //indicates if it is ACK or Data
    Node* origin_;//sender of the packet(same as the sender of the flow)
    Node* dest_;//destination of the packet (same as the destination of the flow)
    int size_; //size of the packet. Unit: bits
    int seq_num_; //The sequence number of the packet.
  public:
    //constructors
    Packet(std::string id, Node* src, Node* dst);
    Packet(std::string type, int seq, Node* src, Node* dst);
    
    //functions
    Node* GetSrc(); //returns the sender info
    Node* GetDst(); //returns the destination info
    int size(); //returns the size of the packet
    int seqNum(); //returns sequence number of this packet
};
#endif
