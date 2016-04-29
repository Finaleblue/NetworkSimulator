#include <vector>
#include <queue>
#include <string>
#include <iostream>

std::priority_queue<int> pq;

class A{
  public:

    const operator < (const A&){

    }
    void push();
    
};

void A::push(){
  for(int i=1; i<=10; i+=2) pq.push(i);
}
class B {
      public:
        //constructor
        void push();
        
     };

void B::push(){
for(int i=2; i<=10; i+=2) pq.push(i);
}

int main(){
  A a;
  B b;
  a.push();
  b.push();
  while(!pq.empty()) {std::cout<<pq.top()<<" "<<std::endl; pq.pop();}
}
