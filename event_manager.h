#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <queue>
#include <fstream>

class EventManager{
  private:
    std::vector<Flow*> flows_;
    std::vector<Link*> links_;
    std::vector<Node*> devices_;
    std::string output_filename_="";
    ofstream out_file_;
    std::priority_queue<Event*> queue_;
    double time_ = 0;
  public:
    void log(std::string);
    void RegisterNetwork(&Network);
    double time();
    void Add(double, &Event);
    void Run();
};
#endif
