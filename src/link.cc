#include "link.h"
#include "node.h"
#include "global.h"
#include "event_manager.h"

Link::Link(std::string id, Node& end1, Node& end2, 
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

void Link::ReceivePacket(Node& send_to, Packet p, double t){
  if (transmitting_) {
    buffer_.push(p);
    ++num_packs_in_buffer_;
  }
  else{
    SendPacket(send_to, p, t + delay_); //TODO: take datarate into account
    transmitting_ = true;
  }
}

void Link::SendPacket(Node& send_to, Packet p, double t){
  event_manager.push(ReceivePacketEvent(send_to, p, t));
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
