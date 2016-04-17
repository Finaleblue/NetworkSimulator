#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <queue>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include "flow.h"
#include "link.h"
#include "node.h"

class EventManager{
  private:
    std::vector<Flow> &flows_;
    std::vector<Link> &links_;
    std::vector<Node> &devices_;
    std::string output_filename_="";
    ofstream out_file_;
    static std::priority_queue<Event> queue_;
    double time_ = 0;
  public:
    EventManager(std::string, &Network);
    void log(std::string);
    void run();
};
#endif
