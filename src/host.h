#include "node.h"

class Host: public Node{
  private:
    int bits_sent = 0;
    int bits_received = 0;
  public:
    Host(const std::string id);

}
