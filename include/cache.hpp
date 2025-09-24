#include <list>
#include <stddef.h>
#include <unordered_map>

#ifndef INCR_COEF_STACK
  #define INCR_COEF_STACK 3
#endif

#ifndef DECR_COEF_QUEUE
  #define DECR_COEF_QUEUE 2
#endif

//--------------------------------------------------------------
template <typename DataT, typename KeyT = int> class stack_t {
private:
  size_t size_;
  struct StackEntry {
    DataT data;
    bool is_lir, is_resident;
  };
  std::list<StackEntry> list_;
  using MyIt = typename std::list<StackEntry>::iterator;
  std::unordered_map<KeyT, typename std::list<StackEntry>::iterator> hash_table_;

public:
  stack_t(size_t size) : size_(size) {}
  ~stack_t() = default;
  const size_t size_coef = 3;

  //TODO доделать методы для stack S
};
//--------------------------------------------------------------
template <typename DataT, typename KeyT = int> class queue_t {
private:
  size_t size_;
  std::list<DataT> list_;
  std::unordered_map<KeyT, typename std::list<DataT>::iterator> hash_table_;

public:
  queue_t(size_t size): size_(size) {}
  ~queue_t() = default;
  
  //TODO доделать методы для queue Q
};
//--------------------------------------------------------------
template <typename DataT, typename KeyT = int> class cache_t {
private:
  size_t size_;
  std::list<DataT> list_;
  using ListIt = typename std::list<DataT>::iterator;
  std::unordered_map<KeyT, ListIt> hash_table_;

  stack_t<DataT, KeyT> stack_s;
  queue_t<DataT, KeyT> queue_q;
   
public:
  cache_t(size_t size) : size_(size),
    stack_s(size * INCR_COEF_STACK),
    queue_q(size / DECR_COEF_QUEUE) {
    // size_cache_ = size;
    // stack_s(size * stack_s.size_coef);
    // queue_q(size / queue_q.size_coef); 
  }
  ~cache_t() = default;
  
  //TODO доделать методы для cache 

  template <typename FuncPtrT>
  bool lookup_update(KeyT key, FuncPtrT slow_get_page) {
    return true;
  }
};
//--------------------------------------------------------------
