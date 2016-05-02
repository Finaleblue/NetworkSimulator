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
    Packet(std::string, std::string, Node&, Node&);
    Packet(std::string, char, int, Node&, Node&);
    
    //functions
    Node& GetSrc() const; //returns the sender info
    Node& GetDst() const; //returns the destination info
    double size() const; //returns the size of the packet
    int seqNum() const; //returns sequence number of this packet
    std::string id() const;
    char type() const; // returns the type of the packet
    std::string ToType(std::string);
    int ToSeq(std::string);
    std::string fid();
  private:
    std::string id_;
    char type_; //indicates if it is ACK or Data
    std::string fid_; //id of flow it belongs to
    Node& src_;//sender of the packet(same as the sender of the flow)
    Node& dst_;//destination of the packet (same as the destination of the flow)
    double size_; //size of the packet. Unit: bits
    int seq_; //The sequence number of the packet.
};
#endif
