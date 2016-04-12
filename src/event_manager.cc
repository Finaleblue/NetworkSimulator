#include <iostream>
#include <fstream>
#include "event_manager.h"

EventManager(std::string filename){
  output_filename_ = filename;
}

void log(std::string msg){
  out_file_.open(output_filename_ + ".log");
  out_file_ << msg <<endl;
  out_file_.close();
}

void RegisterNetwork(Network &net){
  std::vector<Flow*> flows = net.GetFlows();
  for(std::vector<Flow*>::iterator itr = flows.begin();
      itr!=flows.end(); ++itr){
    itr -> Register();
  }
}

double time(){
  return time_;
}

void Add(double t, Event &e){
  if (t<0) return;
  queue_.push(&e); //TODO:Think about if we need time inside event class
}

void Run(){
  bool done = false;
  while (!queue_.empty()){
    Event e* = queue_.pop();
    e -> execute();
    
    bool acting = true;
    while (acting){
      acting = false;
      for (std::vector<Flow*>::iterator itr = flows.begin();
          itr != flows.end(); ++itr){
        if (itr->act()) acting = true; 
        done = !(itr->act() || done);
      }
    }
    if (done) break;
  }
}
