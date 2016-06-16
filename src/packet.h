/**
 * Cooper Union Communication Networks Final Project
 * Author: Eui Han
 * Version: 1.4
 **/

#ifndef PACKET_H_
#define PACKET_H_
#include <string>
#include "node.h"

class Packet{
  public:
    //constructors
    Packet(std::string, int, std::string, Node&, Node&);
    Packet(std::string, int, char, int, Node&, Node&);
    
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
    int flow_num_;
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
