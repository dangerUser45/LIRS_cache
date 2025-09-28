#include <cassert>
#include <iostream>

#include "../include/lirs.hpp"

void slow_get_page();
//--------------------------------------------------------------
int main() {
  using DataT = int;
  using KeyT  = int;
  
  int cache_size = 0, num_elems = 0;
  std::cin >> cache_size;
  std::cin >> num_elems;
  cache_t<DataT, KeyT> cache(cache_size);

  stack_t<DataT, KeyT> stack_s(10);
  stack_s.push_front(1, 666);

  #ifdef DEBUG
  stack_s.print();
  #endif

  // int hits = 0;
  // for (int i = 0; i < num_elems; ++i) {
  //   DataT key = 0;
  //   std::cin >> key;
  //   hits += cache.lookup_update(key, slow_get_page);
  // }
  // std::cout << hits << std::endl;
}
//--------------------------------------------------------------
