/**
 * CommNets
 * @Author Eui Han
 */
#ifndef NODE_H_
#define NODE_H_
#include <string>
#include "node.h"
class Packet{
      private:
        std::string id_;
        flow* flow_;
        node* origin_;//sender of the packet(same as the sender of the flow)
        node* dest_;//destination of the packet (same as the destination of the flow)
        int size_; //size of the packet. Unit: bits
        int seqNum_; //The sequence number of the packet.
        std::string data_; //The actual data packet carries (I don't know if we need this for the simulation but I am including it for completeness.
    public:
        //constructors
        Packet(std::string id, node* origin, node* dest, flow* fl);

        Node* origin(); //returns the sender info
        Node* dest(); //returns the destination info
        int size(); //returns the size of the packet
        int seqNum(); //returns the sequence number of the packet
        std::string data(); //returns the data inside the packet (whatever it is)
};
#endif
