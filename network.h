#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include "link.h"
#include "host.h"
//#include "router.h" TODO: no routres yet
#include "flow.h"

class Network{
  private:
    std::vector<node*> devices_;
    std::vector<link*> links_;
    std::vector<flows*> flows_;
  public:
    Network();
    void AddHost(const &Host);
    //void AddRouter(const &Router); TODO: no routers yet
    void AddLink(const &Link);
    void AddFlow(const &Flow);
    Flow* GetFlow();

};
#endif  

