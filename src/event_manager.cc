#include <iostream>
#include "event_manager.h"
#include "flow.h"
#include "host.h"
#include "router.h"
#include "link.h"
#include "global.h"


EventManager::EventManager(){
  time_ = 0;
}

Network& EventManager::Net(){
  return net_;
}

//Logging does not work yet
void EventManager::log(const std::string msg){
  out_file_.open(output_filename_ + ".log");
  out_file_ << msg <<std::endl;
  out_file_.close();
}

void EventManager::Setup(){
  std::cout<<"setting up"<<std::endl;
  flows_ = net_.GetFlows();
  links_ = net_.GetLinks();
  routers_ = net_.GetRouters();
  hosts_ = net_.GetHosts();
  for (auto &pair : flows_){
      pair.second.Pack();
      std::cout<<"pushed flowstart"<<std::endl;
      queue_.push(std::shared_ptr<FlowStartEvent>(new FlowStartEvent(pair.second, pair.second.GetStartTime())));
  }
}


bool EventManager::isDone() const{
  return queue_.empty();
}

void EventManager::Run(){ 
  while(true){
    std::cout<<"queue size in run: " <<queue_.size()<<std::endl;
    if (time_ >= global::MAX_SIMULATION_TIME)  {return;}
    if (queue_.empty()){
      std::cout<<"simulation ended"<<std::endl;
     return;
    }
  
    std::shared_ptr<Event> e = queue_.top();
    queue_.pop();
    time_ = e->GetScheduledTime(); //sync global time
    std::cout<<"Current Time: "<<time_<<std::endl;
    bool done=false;
    done = e->Start();  
    while (!done){/*wait for threads to finish*/}
  }
}

void EventManager::push(std::shared_ptr<Event> e){
  std::cout<<"Event added"<<std::endl;
  queue_.push(e); 
}

double EventManager::time(){
  return time_;
}

int EventManager::queue_size(){
  return queue_.size();
}

