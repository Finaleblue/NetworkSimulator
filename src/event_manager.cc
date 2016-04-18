#include <iostream>
#include "event_manager.h"

EventManager(const std::string filename, const Network &net){
  output_filename_ = filename;
  flows_ = net.GetFlows();
  links_ = net.GetLinks();
  devices_ = net.GetDevices();
  queue_();
  global_time_ = 0;
}

void log(const std::string msg){
  out_file_.open(output_filename_ + ".log");
  out_file_ << msg <<endl;
  out_file_.close();
}

void SetUp(){
  for (std::vector<Flow>::iterator itr = flows_.begin(); 
        itr != flows_.end(); ++itr){
      itr->Pack();
      queue_.push(FlowStartEvent(*itr, itr->GetStartTime());
  }
}

int global_time(){
  retuurn global_time_;
}
bool isDone(){
  if (finished_ >= flows_.size()) {return true;}
}
void Run(){ 
  while( true ){
    if (global_time_ >= globla::MAX_SIMULATION_TIME)  {break;}
    if (isDone()) {break;}
    Event& e = queue_.top();
    queue_.pop();
    global_time_ = e.GetScheduledTime();
    e.Start();
  }
}

