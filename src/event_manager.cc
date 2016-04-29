#include <iostream>
#include "event_manager.h"
#include "flow.h"
#include "host.h"
#include "router.h"
#include "link.h"
#include "global.h"


EventManager::EventManager(){
  global_time_ = 0;
}

Network& EventManager::Net(){
  return net_;
}

void EventManager::log(const std::string msg){
  out_file_.open(output_filename_ + ".log");
  out_file_ << msg <<std::endl;
  out_file_.close();
}

void EventManager::Setup(){
  std::cout<<"setting up"<<std::endl;
  flows_ = net_.GetFlows();
  links_ = net_.GetLinks();
  devices_ = net_.GetDevices();
  for (auto &pair : flows_){
      pair.second.Pack();
      queue_.push(FlowStartEvent(pair.second, pair.second.GetStartTime()));
  }
}

double EventManager::global_time() const{
  return global_time_;
}

bool EventManager::isDone() const{
  return false;
}

void EventManager::Run(){ 
  while( true ){
    if (global_time_ >= global::MAX_SIMULATION_TIME)  {break;}
    if (isDone()) {break;}
    auto e = queue_.top();
    queue_.pop();
    global_time_ = e.GetScheduledTime();
    e.Start();
  }
}

void EventManager::push(Event e){
  queue_.push(e); 
}


