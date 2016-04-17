#include <iostream>
#include "event_manager.h"

EventManager(const std::string filename, const Network &net){
  output_filename_ = filename;
  flows_ = net.GetFlows();
  links_ = net.GetLinks();
  devices_ = net.GetDevices();
  queue_();
}

void log(const std::string msg){
  out_file_.open(output_filename_ + ".log");
  out_file_ << msg <<endl;
  out_file_.close();
}

void run(){
  for (std::vector<Flow>::iterator itr = flows_.begin(); 
        itr != flows_.end(); ++itr){
      queue_.push(FlowStartEvent(*itr, itr->GetStartTime());
  }

}
