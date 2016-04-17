#include "network.h"

void AddHost(const std::string id){
  devices_.push_back(Host(id));
}

void AddRouter(const std::string id){
  devices_.push_back(Router(id));
}

void AddLink(const std::string id, const std::string end1_id, const std::string end2_id,
            int datarate, int delay, int buffer){
  const Node& end1 = FindDevice(end1_id);
  const Node& end2 = FindDevice(end2_id);

  links_.push_back(Link(id, end1, end2, datarate, delay, buffer));
}

void AddFlow(const std::string id, double start_time, int size,
            const std::string src_id, const std::string dst_id, 
            const std::string protocol, const std::string alpha){
  const Node& src = FindDevice(src_id);
  const Node& dst = FindDevice(dst_id);
  flows_.push_back(Flow(id, start_time, size, src, dst, 
                  std::string protocol, std::string alpha));
}

std::vector<Flow> GetFlows(){
  return flows_;
}

std::vector<Link> GetLinks(){
  return links_;
}

std::vector<Node> GetDevices(){
  return devices_;
}

Node& FindDevice(std::string id){
  for(std::vector<Node>::iterator itr = devices_.begin();
      itr != devices_.end(); ++itr){
    if (itr->GetId() == id) {return *itr;}
  }
}
