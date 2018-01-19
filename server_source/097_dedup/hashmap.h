#include<iostream>
#include<stdlib.h>
//#include<map>
#include<list>
#include<functional>
#include<string>
#include<vector>
#include<utility>

// --- HashMap class ---

template<typename Key, typename Value, typename Hasher>
class HashMap{
private:
  Hasher hash;
  std::vector<std::list<std::pair<Key,Value> > > * table;
  size_t start_size;
  size_t num_items;
  
  // alternatively you could use STL std::map<K,V> 
  
public:
 HashMap():table(new std::vector<std::list<std::pair<Key,Value> > >(1048576)), start_size(1048576), num_items(0){}
  
  HashMap(size_t size):table(new std::vector<std::list<std::pair<Key,Value> > >(size)), start_size(size),
		       num_items(0){}

  HashMap(const Key& k, const Value& v):table(new std::vector<std::list<std::pair<Key,Value> > >(1024)),
					start_size(1024),num_items(0)
  {
    (*(this->table)).add(k,v);
  }

  ~HashMap(){
    delete this->table;
    // table uses STL maps, lists and pairs, should all be good
    // Hasher is also STL, std::hash<typename (what you wanna hash)> is used
  }

  /*
  HashMap(const HashMap& rhs):table(new std::vector<std::list<std::pair<Key,Value> > >(){
      for (std::vector<std::list<std::pair<Key,Value> > >::iterator it = (*rhs.table).begin();
	   it != (*rhs.table).end(); ++it){
	(*(this->table))[it] = 
  */
  // come back to that if I need to
  // may get away with not having it, since test just tests the program function

  void add(const Key& k, const Value& v){
    if ((*(this->table)).size() == 0){ // check if size is 0 so to not divide by 0
      //std::cout << "Starting with size of 0\n";
      this->reSize();
    }
    size_t index = hash(k);  // hash the key  
    index = index % this->start_size;//(*(this->table)).size();  // divide by hash table (vector) size to get right index
    (*(this->table))[index].push_front(std::pair<Key,Value>(k,v));
    num_items++;
    if (this->needsReSize()){
      this->reSize();
    }
  }

  bool isEmptyBucket(const Key& k){
    size_t index = hash(k);  // hash the key  
    index = index % (*(this->table)).size();  // divide by hash table (vector) size to get right index
    // got through list and check for key k in the pairs of the list
    for (typename std::list<std::pair<Key,Value> >::const_iterator it = (*(this->table))[index].cbegin();
	 it != (*(this->table))[index].cend(); ++it){  // iterator goes through pairs of linked list
      if (std::get<0>(*it) == k){
	return false;
      }
    }
    return true;
  }
  
  const Value& getKeysValue(const Key& k){
    size_t index = hash(k);  // hash the key  
    index = index % (*(this->table)).size();  // divide by hash table (vector) size to get right index
    // got through list and check for key k in the pairs of the list
    for (typename std::list<std::pair<Key,Value> >::const_iterator it = (*(this->table))[index].cbegin();
	 it != (*(this->table))[index].cend(); ++it){  // iterator goes through pairs of linked list
      if (std::get<0>(*it) == k){
	return std::get<1>(*it);
      }
    }
    throw std::exception();
  }
  
  // vector will automatically resize but only when full -- probably not good enough 
  bool needsReSize(){
    double load_factor = ((double) num_items) / ((double) (*(this->table)).size());
    if (load_factor > 0.75){
      return true;
    }
    else{
      return false;
    }
  }

  void reSize(){
    //std::cout << "Resizing...\n";
    // if the load factor is exceeded make new table twice as large as previous
    if (this->start_size == 0){ // check if starting from size 0
      this->start_size++;
    }
    std::vector<std::list<std::pair<Key,Value> > > * newTable =
      new std::vector<std::list<std::pair<Key,Value> > >((this->start_size) * 2); 
    // rather than doing that, could use temp and swap with copy constructor
    // num_items stays the same, but start_size is now updated
    this->start_size *= 2; // double size
    typename std::vector<std::list<std::pair<Key,Value> > >::iterator table_it;// = (*(this->table)).begin();
    typename std::list<std::pair<Key,Value> >::iterator list_it;// = (*table_it).begin();  // beginning of list
    for (table_it = (*(this->table)).begin(); table_it != (*(this->table)).end(); ++table_it){
      if (!(*table_it).empty()){  // if the list at current index is not empty
	for (list_it = (*table_it).begin(); list_it != (*table_it).end(); ++list_it){
	  // for each pair in each list in each index of table
	  size_t new_index = hash(std::get<0>(*list_it)); // hash the key of the current pair in list
	  new_index = new_index % start_size;
	  (*newTable)[new_index].push_front(std::pair<Key,Value>(std::get<0>(*list_it),std::get<1>(*list_it)));
	}
      }
    }
    // now you have a new, larger table; start_size is resized, num_items is the same --> swap table
    std::vector<std::list<std::pair<Key,Value> > > * temp = this->table;
    this->table = newTable;
    delete temp;
  }

      
  

  
};


