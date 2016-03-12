#include <string>

class packet{
    private:
        std::string origin;//sender of the packet(same as the sender of the flow)
        std::string dest;//destination of the packet (same as the destination of the flow)
        int size; //size of the packet. Unit: bits
        int seqNum; //The sequence number of the packet.
        std::string data; //The actual data packet carries (I don't know if we need this for the simulation but I am including it for completeness.
    public:
        //constructors
        packet(std::string origin, std::string dest, int size, int seqNum, std::string data);
        packet(std::string origin, std::string dest, int size, int seqNum);
        packet(int size, int seqNum);
        packet(int size);

        std::string origin(); //returns the sender info
        std::string dest(); //returns the destination info
        int size(); //returns the size of the packet
        int seqNum(); //returns the sequence number of the packet
        std::string data(); //returns the data inside the packet (whatever it is)
}
