#include <iostream>
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
    KeyT key;
    DataT data;
    bool is_lir;
    bool is_resident;
  };
  std::list<StackEntry> list_;
  using listIt_t = typename std::list<StackEntry>::iterator;
  using hashTableIt_t = typename std::unordered_map<KeyT, listIt_t>;
  hashTableIt_t hash_table_;

public:
  stack_t(size_t size) : size_(size) {
    /* TODO: добавить ht.max_load_factor() и ht.reserve(size stack S)
             для отмены рехэширования */ 
  }
  ~stack_t() = default;
  const size_t size_coef = 3;

  struct ElemContext {
    listIt_t list_it;
    hashTableIt_t hash_table_it;
  };

  //TODO доделать методы для stack S
  listIt_t get_hash_table_it(KeyT key) {
    auto it = hash_table_.find(key);
    if(it != hash_table_.end())
      return it;
  }

  listIt_t get_list_it (KeyT key) {

  }

  void push_front(KeyT key, DataT data) {
    list_.emplace_front(StackEntry{key, data, false, true});
    hash_table_.emplace(key, list_.begin());
  }

  //FIXME (move_to_front_list) не уверен что алгоритм правильно работает
  void move_to_front_list(listIt_t it) {
    list_.splice(list_.begin(), list_, it); 
  }

  bool is_contain(KeyT key) {
    if(hash_table_.find(key)->second == list_.end())
      return false;
    else
      return true;
  }

  void pruning() {
    auto last_lir_it = list_.rbegin();
    bool no_lirs = true;
    for(auto it = list_.rbegin(); it != list_.rend(); ++it) { 
      if(it->is_lir) {
        last_lir_it = it;
        no_lirs = false;
        break;
      }
      hash_table_.erase(it->key);
    } 

    if(no_lirs)  
      std::cerr << "Error: stack pruning is happened, "
                    "but stack S haven't LIR elements" << std::endl;
    else
      list_.erase(last_lir_it, list_.end());
  }

  #ifdef DEBUG
  const char* print_bool(bool value) {
    if(value) return "true";
    else return "false";
  } 
  void print() {
    int i = 0;
    for(auto it = list_.begin(); it != list_.end(); ++it, ++i) {
      std::cout << "StackEntry[" << i << "]:\n\t"
          << "DataT data  = " << it->data << "\n\t"
          << "bool is_lir = " << print_bool(it->is_lir) << "\n\t"
          << "bool is_resident = " << print_bool(it->is_resident) << std::endl;
    }
  }
  #endif
};
//--------------------------------------------------------------
template <typename DataT, typename KeyT = int> class queue_t {

  /* В алгоритме LIRS очередь Q используется так: в конец данные
    добавляются, а из начала - удаляются, но для удобства сделаем
    наоборот: в начало кладутся данные, из конца - удаляются.
    Это отклонение от алгоритма ни на что не влияет. */

private:
  size_t size_;
  std::list<DataT> list_;
  using listIt_t = typename std::list<DataT>::iterator;
  using hashTableIt_t = typename std::unordered_map<KeyT, listIt_t>::iterator;

  std::unordered_map<KeyT, listIt_t> hash_table_;

public:
  queue_t(size_t size): size_(size) {
    /* TODO: добавить ht.max_load_factor() и ht.reserve(size stack S)
             для отмены рехэширования */ 
  }
  ~queue_t() = default;
  
  struct ElemContext {
    listIt_t list_it;
    hashTableIt_t hash_table_it;
  };
  
  //TODO доделать методы для queue Q
  void push_back(DataT data, KeyT key) {
    list_.emplace_front(data);
    hash_table_.emplace(key, data);
  }

  void pop(KeyT key, listIt_t list_it) {
    list_.erase(list_it);
    hash_table_.erase(key);
  }
};
//--------------------------------------------------------------
template <typename DataT, typename KeyT = int> class cache_t {
private:
  size_t size_;
  struct CacheEntry {
    DataT data;
    bool is_lir;
  };
  std::list<CacheEntry> list_;
  using listIt_t = typename std::list<CacheEntry>::iterator;
  using hashTableIt_t = typename std::unordered_map<KeyT, listIt_t>::iterator;

  std::unordered_map<KeyT, listIt_t> hash_table_;

  struct ElemContext {
    listIt_t list_it;
    hashTableIt_t hash_table_it;
  };

  stack_t<DataT, KeyT> stack_s;
  queue_t<DataT, KeyT> queue_q;

  struct CacheContext {
    typename stack_t<DataT, KeyT>::ElemContext stack_cntx;
    typename queue_t<DataT, KeyT>::ElemContext queue_cntx;
    typename cache_t<DataT, KeyT>::ElemContext cache_cntx;
    
    CacheContext(KeyT key, stack_t<DataT, KeyT>& stack_s) {
    /* TODO: добавить ht.max_load_factor() и ht.reserve(size stack S)
             для отмены рехэширования */ 

      stack_cntx.hash_table_it = stack_s.get_hash_table_it(key);
      // stack_cntx.list_it = 

      // queue_cntx.list_it = 
      // queue_cntx.hash_table_it = 

      // cache_cntx.list_it = 
      // cache_cntx.hash_table_it = 
    }
  };
   
  //TODO доделать методы для cache
  bool is_resident(KeyT key) {
    if(hash_table_.find(key) == hash_table_.end())
      return false; //not found
    else
      return true;
  }

  inline bool is_lir(KeyT key) {
    return hash_table_.find(key)->second->is_lir;
  }

  inline bool is_in_bottom(listIt_t it) {
    if((++it) == list_.end())
      return true;
    else
      return false;
  }

public:
  cache_t(size_t size) : size_(size),
    stack_s(size * INCR_COEF_STACK),
    queue_q(size / DECR_COEF_QUEUE) {}
  ~cache_t() = default;

  template <typename FuncPtrT>
  bool lookup_update(KeyT key, FuncPtrT slow_get_page) {
    if(is_resident(key)) {
      if(is_lir(key)) { // LIR resident
        listIt_t list_it = hash_table_.find(key)->second;
        if(is_in_bottom(list_it))
          stack_s.pruning();
        stack_s.move_to_front(key);
      } 
      else { //HIR resident
        if(stack_s.is_contain(key)) {
          stack_s.move_to_front(key);
          //queue_q.remove(key) - добавить метод
          //queue_q.push_back(key); - добавить метод
          stack_s.pruning();
        }
        else { 

        }
      }
    }
    else { //Non resident

    }
  }
};
//--------------------------------------------------------------
