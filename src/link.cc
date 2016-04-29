#include <iostream>
#include <memory>
#include "link.h"
#include "node.h"
#include "event.h"
#include "event_manager.h"

extern EventManager event_manager;

Link::Link(std::string id, Node& end1, Node& end2, 
           double datarate, double buffer_size, double delay):
  id_(id),
  datarate_(datarate),
  buffer_size_(buffer_size),
  end1_(end1), end2_(end2),
  delay_(delay),
  transmitting_(false)
{}

bool Link::isAvailable() const{
  return buffer_size_ == num_packs_in_buffer_;
}

bool Link::ReceivePacket(Node& send_to, Packet p, double t){
  //std::cout<<"link flag1"<<std::endl;
  if (transmitting_) {
    buffer_.push({p,send_to});
    ++num_packs_in_buffer_;
    return true;
  }
  else{
    transmitting_ = true;
    return SendPacket(send_to, p, t + delay_); //TODO: take datarate into account
  }
}

bool Link::SendPacket(Node& send_to, Packet p, double t){
  //std::cout<<"link flag2"<<std::endl;
  event_manager.push(std::shared_ptr<ReceivePacketEvent>(new ReceivePacketEvent(send_to, p, t)));
  return true;
}

double Link::GetCost() const{
  return occupancy_ / datarate_;
}

std::string Link::id() const{
  return id_;
}

Node& Link::GetConnectedNode(Node &n) const{
  if (n == end1_){return end2_;}
  else  {return end1_;}
}

void Link::flush(double t){
  transmitting_ = false;
  if (!buffer_.empty()){
    std::pair<Packet, Node&> p = buffer_.front();
    buffer_.pop();
    SendPacket(p.second, p.first, t);
  }
}
