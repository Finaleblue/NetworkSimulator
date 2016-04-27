#include "link.h"
#include "node.h"
#include "global.h"
#include <vector>

Link::Link(const std::string id, const Node& end1, const Node& end2, double datarate, double buffer_size, double delay):
  id_(id),
  datarate_(datarate),
  buffer_size_(buffer_size),
  end1_(end1), end2_(end2),
  delay_(delay + Global::PACKET_SIZE / datarate){

  if (global::PACKET_SIZE % datarate !=0) {++delay;}
  buffer_ = Packet[buffer_size];
}

const bool Link::isAvailable() const{
  return buffer_size_ == num_packs_in_buffer_;
}

void Link::ReceivePacket(const Node& n, Packet p, double t){
  if (transmitting) {
    buffer_[num_packs_in_buffer_] = p;
    ++num_packs_in_buffer_;
  }
  else{
    SendPacket(p, t + delay, to);
    transmitting = true;
  }
}

void Link::SendPacket(Packet p, double t){
  //to.ReceivePacket(p,t);
}

void Link::DoneTransmitting(){
  transmitting = false;
}

double Link::GetCost(){
  return occupancy_ / datarate_;
}
