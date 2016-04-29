#include <vector>
#include <string>
#include <iostream>
class A{
      public:
        virtual void do();
    };

class B : public A{
      public:
        //constructor
        void do(){
          std::cout<<"do A"<<std::end;
        }
     };

class C{
}
int main(){
  A a;
  B b(a);
  std::string id = "C1";
  printint(id[1]-'0');
}

void printint(std::string i){
  std::cout<<i<<std::endl;
}
