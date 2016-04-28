#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <map>
#include <queue>
#include <iostream>
#include <fstream>
#include "network.h"
#include "event.h"
//forward declaration
class Flow;
class Link;
class Node;

class EventManager{
  public:
    EventManager();
    void log(std::string);
    void Setup();
    void Run();
    bool isDone() const;
    double global_time() const;
    void push(Event);
    Network& Net();

  private:
    std::map<std::string, Flow> flows_;
    std::map<std::string, Link> links_;
    std::map<std::string, Node> devices_;
    std::string output_filename_="";
    std::ofstream out_file_;
    std::priority_queue<Event> queue_;
    Network net;
    double global_time_ = 0;
    int finished_ = 0;
    bool done_=false;
  };
#endif
