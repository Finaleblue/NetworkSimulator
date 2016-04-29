#ifndef NETWORK_H_
#define NETWORK_H_

#include <map>
#include "host.h"
#include "router.h"
#include "link.h"
#include "flow.h"

class Network{
  public:
    void AddHost(std::string id);
    void AddRouter(std::string id);
    void AddLink(std::string id, std::string end1_id, std::string end2_id, double datarate, double delay, double buffer);
    void AddFlow(std::string id, double start_time, int size, std::string src_id, std::string dst_id, std::string);
    std::map<std::string, Flow> GetFlows() const;
    std::map<std::string, Link> GetLinks() const;
    std::map<std::string, Router> GetRouters() const;
    std::map<std::string, Host> GetHosts() const;
    Link& GetLink(std::string);
    Router& GetRouter(std::string);
    Host& GetHost(std::string);
    Node& GetNode(std::string);
  private:
    std::map<std::string, Flow> flows_;
    std::map<std::string, Link> links_;
    std::map<std::string, Router> routers_;
    std::map<std::string, Host> hosts_;
};

#endif
