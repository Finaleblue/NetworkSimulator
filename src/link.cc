#include "link.h"
#include <vector>

Link(const std::string id, int datarate, int buffer_size, int delay
      const Node& end1, const Node& end2){
  id_=id;
  datarate_=datarate;
  buffer_size_=buffer_size;
  delay_=delay + global::PACKET_SIZE / datarate;
  if (global::PACKET_SIZE % datarate !=0) {++delay;}
  end1_ = end1;
  end2_ = end2;
  buffer_ = Packet[buffer_size];
}

bool isAvailable(){
  return buffer_size_ == num_packs_in_buffer_;
}

void ReceivePacket(Packet &p, double t, Node& to){
  if (transmitting) {
    buffer_[num_packs_in_buffer_] = p;
    ++num_packs_in_buffer_;
  }
  else{
    SendPacket(p, t + delay, to);
    transmitting = true;
  }
}

void SendPacket(Packet &p, double t, Node& to){
  to.ReceivePacket(p,t);
}

void DoneTransmitting(){
  transmitting = false;
}
