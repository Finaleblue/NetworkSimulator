#include "link.h"
#include "node.h"
#include "global.h"

Link::Link(const std::string id, const Node& end1, const Node& end2, 
           double datarate, double buffer_size, double delay):
  id_(id),
  datarate_(datarate),
  buffer_size_(buffer_size),
  end1_(end1), end2_(end2),
  delay_(delay)
{}

bool Link::isAvailable() const{
  return buffer_size_ == num_packs_in_buffer_;
}

void Link::ReceivePacket(const Packet p, double t){
  if (transmitting_) {
    buffer_.push(p);
    ++num_packs_in_buffer_;
  }
  else{
    SendPacket(p, t + delay_);
    transmitting_ = true;
  }
}

void Link::SendPacket(const Packet p, double t){
  //to.eeceivePacket(p,t);
}

void Link::DoneTransmitting(){
  transmitting_ = false;
}

double Link::GetCost() const{
  return occupancy_ / datarate_;
}

std::string Link::id() const{
  return id_;
}
