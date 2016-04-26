#include "link.h"
#include "node.h"
#include <vector>

Link::Link(const std::string id, const Node& end1, const Node& end2, 
           double datarate, double buffer_size, double delay):
  id_(id),
  datarate_(datarate),
  buffer_size_(buffer_size),
  delay_(delay + global::PACKET_SIZE / datarate){

  if (global::PACKET_SIZE % datarate !=0) {++delay;}
  end1_ = end1;
  end2_ = end2;
  buffer_ = Packet[buffer_size];
}

const bool Link::isAvailable() const{
  return buffer_size_ == num_packs_in_buffer_;
}

void Link::ReceivePacket(Packet &p, double t, Node& to){
  if (transmitting) {
    buffer_[num_packs_in_buffer_] = p;
    ++num_packs_in_buffer_;
  }
  else{
    SendPacket(p, t + delay, to);
    transmitting = true;
  }
}

void Link::SendPacket(Packet &p, double t, Node& to){
  to.ReceivePacket(p,t);
}

void Link::DoneTransmitting(){
  transmitting = false;
}

double GetCost(){
  return occupancy_ / datarate_;
}
