#include <iostream>
#include <stdexcept>

#include "branched-linked-list.hpp"
#include "node.hpp"

int main() {
  /* EXAMPLE INTERACTIONS WITH BLL */
  BLL* first = new BLL();
  first->PushBack('h');
  first->PushBack('i');

  std::cout << first->ToString() << std::endl;  // hi
  std::cout << first->Size() << std::endl;      // 2
  // std::cout << first->GetAt(2) << std::endl;    //exception testing
  // first->SetAt(1, 'e');
  // std::cout << first->ToString() << std::endl;

  BLL* copy = first;
  std::cout << copy->ToString() << std::endl;
  // /////////////////////////////////////

  // BLL* second = new BLL();
  // second->PushBack('i');
  // second->PushBack('!');
  // second->PushBack('@');

  // std::cout << second->ToString() << std::endl;  // i!@
  // std::cout << second->Size() << std::endl;      // 3

  // BLL* third = new BLL();
  // third->PushBack('l');
  // third->PushBack('a');
  // third->PushBack('r');
  // first->Join(0, third);  // h -> lar -> e , first: he, third: lar
  // std::cout << first->ToString() << std::endl;
  // std::cout << first->Size() << std::endl;
  // std::cout << first->GetAt(1) << std::endl;
  // first->SetAt(4, 'x');
  // std::cout << first->ToString() << std::endl;
  // std::cout << first->IsBLLAcyclic() << std::endl;

  BLL* four = new BLL();
  four->PushBack('E');
  first->Join(1, four);
  std::cout << four->ToString() << std::endl;
  four->Join(0, first);
  // std::cout << first->ToString() << std::endl;
  std::cout << first->IsBLLAcyclic() << std::endl;
  // BLL* four;
  // four = first;
  // std::cout << four->ToString() << std::endl;

  // /////////////////////////////////////

  // first->Join(1, second);

  // std::cout << first->ToString() << std::endl;  // hii!@
  // std::cout << first->Size() << std::endl;      // 5

  // std::cout << second->ToString() << std::endl;  // i!@
  // std::cout << second->Size() << std::endl;      // 3

  // /////////////////////////////////////

  // BLL* first_clone = new BLL();
  // first_clone = first;

  // std::cout << first_clone->ToString() << std::endl;  // hii!@
  // std::cout << first_clone->Size() << std::endl;      // 5

  return 0;
}
