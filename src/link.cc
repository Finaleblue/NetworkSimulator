#include <memory>
#include "global.h"
#include "link.h"
#include "node.h"
#include "event.h"
#include "event_manager.h"

extern EventManager event_manager;
extern std::ostream* logger;
extern std::ostream *debugSS;
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

void Link::ReceivePacket(Node& send_to, Packet p, double t){
  //std::cout<<"link flag1"<<std::endl;
  if (transmitting_) {
    //std::cout<<"link flag1.1"<<std::endl;
    if (buffer_size_ >= occupancy_ + p.size()){
      //*debugSS<<"Link "<<id_<<" is busy. Pushed to the buffer"<<std::endl; 
      buffer_.push({p,send_to});
      ++num_packs_in_buffer_;
      occupancy_ += p.size();
    }
    else{
      *logger<<"Link "<<id_<<" buffer full. Discard Packet"<<std::endl;
    }
  }
  else{
    //std::cout<<"link flag2"<<std::endl;
    SendPacket(send_to, p, t + delay_ + p.size()/datarate_); 
  }
}

void Link::SendPacket(Node& send_to, Packet p, double t){
  //std::cout<<"link flag3"<<std::endl;
  transmitting_ = true;
  event_manager.push(std::shared_ptr<ReceivePacketEvent>(new ReceivePacketEvent(*this, send_to, p, t)));
}

double Link::GetCost() const{
  return (1+occupancy_) / datarate_;
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
    occupancy_ -= p.first.size();
    SendPacket(p.second, p.first, t+delay_);
  }
}
