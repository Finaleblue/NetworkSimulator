#include <iostream>
#include <memory>
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
  std::cout<<"Setting up the network"<<std::endl;
  flows_ = net_.GetFlows();
  links_ = net_.GetLinks();
  routers_ = net_.GetRouters();
  hosts_ = net_.GetHosts();
  for( auto &itr: hosts_){
    nodes_.insert({itr.first, itr.second});
  }

  for(auto &itr : routers_){
    nodes_.insert({itr.first, itr.second});
  }

  for (auto &pair : flows_){
      pair.second.Pack();
      queue_.push(std::shared_ptr<Event>(new FlowStartEvent(pair.second, pair.second.GetStartTime())));
  }
  for (auto &r : routers_){
    r.second.Init();
    std::cout<<"Router Setup"<<std::endl;
  }
}


bool EventManager::isDone() const{
  return queue_.empty();
}

void EventManager::Run(){ 
  while (true){
    if (queue_.empty()){
      std::cout<<"Simulation Ended"<<std::endl;
      break;
    }
    if(time_ >= global::MAX_SIMULATION_TIME){
      std::cout<<"MAX SIM TIME REACHED"<<std::endl;
      break;
    }
    std::shared_ptr<Event> e = queue_.top();
    queue_.pop();
    time_ = e->GetScheduledTime(); //sync global time
    e->Start();  
  }
}

void EventManager::push(std::shared_ptr<Event> e){
  //std::cout<<"Event "<<e->debugmsg<<" added"<<std::endl;
  queue_.push(e); 
}

double EventManager::time(){
  return time_;
}

int EventManager::queue_size(){
  return queue_.size();
}

