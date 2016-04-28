#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <map>
#include <queue>
#include <iostream>
#include <fstream>
//forward declaration
class Event;
class Flow;
class Link;
class Node;
class Network;

class EventManager{
  public:
    EventManager();
    EventManager(Network);
    void log(std::string);
    void Setup();
    void Run();
    bool isDone() const;
    double global_time() const;
    void push(Event);

  private:
    std::map<std::string, Flow> flows_;
    std::map<std::string, Link> links_;
    std::map<std::string, Node> devices_;
    std::string output_filename_="";
    std::ofstream out_file_;
    std::priority_queue<Event> queue_;
    double global_time_ = 0;
    int finished_ = 0;
    bool done_=false;
  };
#endif
