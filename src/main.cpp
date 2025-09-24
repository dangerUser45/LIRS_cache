#include <cassert>
#include <iostream>

#include "../include/cache.hpp"

void slow_get_page();
//--------------------------------------------------------------
int main() {
  using DataT = int;
  using KeyT = int;
  
  int cache_size = 0, num_elems = 0;
  std::cin >> cache_size;
  std::cin >> num_elems;
  cache_t<DataT, KeyT> cache(cache_size);

  int hits = 0;
  for (int i = 0; i < num_elems; ++i) {
    DataT key = 0;
    std::cin >> key;
    hits += cache.lookup_update(key, slow_get_page);
  }
  std::cout << hits << std::endl;
}
//--------------------------------------------------------------
