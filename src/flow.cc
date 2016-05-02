#include <memory>
#include "flow.h"
#include "packet.h"
#include "host.h"
#include "event.h"
#include "event_manager.h"

extern EventManager event_manager;
extern std::ostream *debugSS;
extern std::ostream *logger;
extern std::string outputFolder;

Flow::Flow(std::string id, double start_time, int size, Host& src, 
           Host& dst, std::string protocol):
  id_(id),
  start_time_(start_time),
  size_(size),
  src_(src),
  dst_(dst),
  protocol_(protocol)
{
  RTTSS_ = new std::ofstream(outputFolder+"/"+id+"_"+"AvgRTT.csv");
  CWNDSS_ = new std::ofstream(outputFolder+"/"+id+"_"+"CWND.csv");      
}



double Flow::GetStartTime() const{
  return start_time_;
}

void Flow::Pack(){
  int data = size_;
  *debugSS<<data<<"data"<<std::endl;
  int i=1;
  while (data > 0){
    packets_.push_back(Packet(id_, i, 'D', i ,src_, dst_));
    ++i;
    data -= global::DATA_PACKET_SIZE;
  }
  num_packs_ = packets_.size();
  *debugSS<<num_packs_<<" packets from "<<id_<<std::endl;
}

void Flow::Start(double t){
  if (protocol_ == "UDP"){
    *debugSS<<"UDP Protocol loaded for "<<id_<<std::endl;
    double wait_ = global::DATA_PACKET_SIZE / src_.GetLink().rate();
    if(src_.GetLink().isAvailable()){
      if (pack_to_send >= num_packs_)  {return;}
      else{
        event_manager.push(std::shared_ptr<SendPacketEvent>(new SendPacketEvent(src_, packets_[pack_to_send], t))); 
        ++pack_to_send;
      }
    }
    event_manager.push(std::shared_ptr<FlowStartEvent>(new FlowStartEvent(*this, t+wait_)));
  }

  else{
    if (src_.GetLink().isAvailable()){
      int count=0;
      //*debugSS<<"flow starts now"<<std::endl;
      while (count * global::DATA_PACKET_SIZE < CWND){
        if (pack_to_send >= num_packs_)  {return;}
        else{
          event_manager.push(std::shared_ptr<SendPacketEvent>(new SendPacketEvent(src_, packets_[pack_to_send], t))); 
          ++pack_to_send;
          ++count;
        }
      }
      double wait_ = count*global::DATA_PACKET_SIZE / src_.GetLink().rate();
      event_manager.push(std::shared_ptr<FlowStartEvent>(new FlowStartEvent(*this, t+wait_)));
    }
  }
}

void Flow::RTT_Update(double rtt){
  //estimate RTTE
  most_recent_rtt_=rtt;
  *logger<<"@time: "<<event_manager.time()<<" RTTE of "<<id_
  <<" changed from: "<<rtte_;
  rtte_ = std::max(1.0, (rtte_ * (acks_received_) + rtt) / (++acks_received_));
  *logger<<" to "<<rtte_<<std::endl;

  if(slow_start){
    if (CWND*2 >= SSTHRESH) {slow_start = false;}
      *logger<<"@time: "<<event_manager.time()
             <<", CWND changed from: "<<CWND;
      CWND*=2;
      *logger<<" to "<<CWND<<std::endl;
  }
  else{
    CWND += global::DATA_PACKET_SIZE;
  }
  *CWNDSS_ <<id_<<", "<<event_manager.time()<<", "<<CWND<<", CWND"<<std::endl;
  *RTTSS_ <<id_<<", "<<event_manager.time()<<", "<<rtte_<<", Average RTT"<<std::endl;
}

void Flow::Congestion(){
  if (protocol_ == "TAHOE"){
    *logger<<"@time: "<<event_manager.time()
          <<", SSTHRESH changed from: "<<SSTHRESH;
    SSTHRESH = std::max(global::INIT_CWND, CWND/2);
    *logger<<" to "<<SSTHRESH<<std::endl;

    *logger<<"@time: "<<event_manager.time()
          <<", CWND changed from: "<<CWND;
    CWND = global::DATA_PACKET_SIZE;
    *logger<<" to "<<CWND<<std::endl;
    slow_start=true;
  }
  else if(protocol_ == "RENO"){
    *logger<<"@time: "<<event_manager.time()
          <<", SSTHRESH changed from: "<<SSTHRESH;
    SSTHRESH = std::max(global::INIT_CWND, CWND/2);
    *logger<<" to "<<SSTHRESH<<std::endl;

    *logger<<"@time: "<<event_manager.time()
          <<", CWND changed from: "<<CWND;
    CWND = std::max(global::DATA_PACKET_SIZE, CWND/2);
    *logger<<" to "<<CWND<<std::endl;
    slow_start=true;
  }

  *CWNDSS_ <<id_<<", "<<event_manager.time()<<", "<<CWND<<", CWND"<<std::endl;
}

double Flow::TimeOutEst(){
  return std::max(((rtte_ * acks_received_ - most_recent_rtt_) + (most_recent_rtt_ * 1.5)) / acks_received_ ,1.0);

}

