# DHBHPQ
Double Hashed Binary Heap Priority Queue is an Improved Version of Priority Queue using a modified hash table to keep track of the elements' indexes
# Data Structures Used In Implementation:
## Array List
### Interface:
  ##### void add_item(T new_item);
  ##### T get_item(int index);
  ##### void clear();
### Complexity and Space Analysis:
  ##### Time: O(1)
  ##### Space: O(n)
## Hash Table
### Interface:
  ##### void add_item(TK key, TV value);
  ##### TV get_value(TK key);
  ##### void clear();
  ##### void delete_item(TK key);
  ##### is_empty();
### Complexity and Space Analysis:
  ##### Time: O(1)*
  ##### Space: O(n)
