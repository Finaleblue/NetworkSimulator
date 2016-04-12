/*
 * CommNets
 * Author Eui Han
 */
#ifndef DATAPACKET_H_
#define DATAPACKET_H_

class DataPacket : public Packet{
  private: 
    bool timeout_;
    int num_times_sent;
  public:
    DataPacket(std::string id, node* origin, node* dest, flow* fl, bool timeout);
};
#endif
