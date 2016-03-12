#include <string>
#include <vector>
#include <iterator>
#include "node.h"
#include "packet.h"
class flow{
    friend class packet;
    
    public:
    /*
     * An iterator for the flow that enables iteration through packets inside the flow
    */
    class iterator:
        public std::iterator<std::forward_iterator_tag, packet>{
            private:
                packet* ref;
            public:
               inline iterator (packet* temp) : ref(temp){}
               inline iterator (const iterator& myitr) : ref(myitr.ref){}
               inline iterator& operator=(const iterator& x);
               inline iterator& operator++();
               inline iterator& operator++(int);
               inline reference operator*() const;
               inline pointer operator->() const;
               inline bool operator ==(const iterator& x) const;
               inline bool operator !=(const iterator& x) const;

    }
    class const_iterator:
        public std::iterator<std::forward_iterator_tag, const packet>{
            private:
                const packet* ref;
            public:
                friend class iterator;
                
                inline const_iterator(const packet* temp) : ref(temp){};
                inline const_iterator(const const_iterator& x) : ref(x.ref){};
                inline const_iterator(const iterator& x): ref(x.ref){};
                inline const_iterator& operator=(const const_iterator& x);
                inline const_iterator& operator=(const iterator& x);
                inline const_iterator& operator++();
                inline const_iterator& operator++(int);
                inline reference operator*() const;
                inline pointer operator->() const;
                inline bool operator==() const;
                inline bool operator!=() const;
            
    }
    //Constructors
    flow(std::string id, node origin, node dest, int flowSize);
    flow(node origin, node dest, int flowSize);
    flow(std::vector<packet> data);
    //function to obtain the origin of the flow
    node getOrigin();
    //function to obtain the destination of the flow
    node getDest();
    //function to obtain the id of the flow
    string getID();
    //function to obtain the size of the flow
    int getSize();
    //function to obtain the number of packets in the flow
    int numPacks();
    //function to obtain 
    private:
    node myOrigin;
    node myDest;
    string myID;
    int flowSize; //Total size of the flow. Unit: bit
    std::vector<packet> packetList; //List of the packets that comprise the flow
    void packup(); // when only the flow size is given (not the actual list of packets), divide the entire data into packets and store them as a vector "packetList"   
}
