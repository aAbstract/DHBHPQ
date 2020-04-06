# DHBHPQ
## Double Hashed Binary Heap Priority Queue is an Improved Version of Priority Queue using a modified hash table to keep track of the elements' indexes
# Interface:
  ##### void add_item(int pror, T value); O(log(n))
  ##### T poll(); O(log(n))
  ##### T peek(); O(1)
  ##### void change_pror(int old_pror, T value, int new_pror); O(log(n))
  ##### void clear(); O(1)
  ##### bool is_empty(); O(1)
  ##### int get_size(); O(1)
  ##### void remove_item(T value, int pror); O(log(n))
  ##### void remove_item(T value); O(n)
  ##### Space: O(n)
# Data Structures Used In Implementation:
## Array List
### Interface:
  ##### void add_item(T new_item); O(1)
  ##### T get_item(int index); O(1)
  ##### void clear(); O(1)
  ##### void insert_item(int i, T v); O(1)
  ##### void remove_last(); O(1) 
  ##### void remove_item(int index); O(n)
  ##### Space: O(n)
## Hash Table
### Interface:
  ##### void add_item(TK key, TV value); O(1)*
  ##### TV get_value(TK key); O(1)*
  ##### void clear(); O(1)
  ##### void delete_item(TK key); O(1)*
  ##### is_empty(); O(1)
  ##### Space: O(n)
