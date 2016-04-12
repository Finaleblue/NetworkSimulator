/**
 * CommNets
 * @author Eui Han
 */

#ifndef ACKPACKET_H_
#define ACKPACKET_H_

class AckPacket : public Packet{
  private:
    Packet next_expected_*;
  public:
    AckPacket(std::string id, node* origin, node* dest, flow* fl, Packet* next);
};

#endif
