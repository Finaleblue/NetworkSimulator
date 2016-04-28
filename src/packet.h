/**
 * CommNets
 * @Author Eui Han
 */
#ifndef PACKET_H_
#define PACKET_H_
#include <string>
#include "node.h"

class Packet{
  public:
    //constructors
    Packet(std::string, const Node&, const Node&);
    Packet(std::string, int, const Node&, const Node&);
    
    //functions
    const Node& GetSrc() const; //returns the sender info
    const Node& GetDst() const; //returns the destination info
    const int size() const; //returns the size of the packet
    const int seqNum() const; //returns sequence number of this packet
    const std::string id() const;
    const std::string type() const; // returns the type of the packet
    std::string ToType(std::string);
    int ToSeq(std::string);
  private:
    const std::string id_;
    const std::string type_; //indicates if it is ACK or Data
    const Node& src_;//sender of the packet(same as the sender of the flow)
    const Node& dst_;//destination of the packet (same as the destination of the flow)
    const int size_; //size of the packet. Unit: bits
    const int seq_; //The sequence number of the packet.
};
#endif
