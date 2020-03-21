#ifndef ARRAY_LIST
#define ARRAY_LIST

/* META-INF
# Interface:
  void add_item(T new_item);
  T get_item(int index);
  void clear();

# Complexity Analysis:
  Time: O(1)
  Space: O(n)
*/

// Java Like Static ArrayList Data Structure
template<typename T>
class array_list {
// Private Fields
// var objs : the local objects of the array
// var count : the count of current stored objects
// var size : current capacity
private:
  T* objs;
  int count;
  int size;
  void double_size() {
    this->size = this->size * 2;
    T* new_ptr = new T[this->size];
    for (int i = 0; i < this->count; i++) {
      new_ptr[i] = this->objs[i];
    }
    delete[] this->objs;
    this->objs = new_ptr;
  }
public:
  // Default Constructor
  array_list() {
    this->count = 0;
    this->size = 2;
    this->objs = new T[2];
  }
  // Adds Element to The Array
  void add_item(T new_item) {
    if (this->count >= this->size)
      this->double_size();
    this->objs[this->count++] = new_item;
  }
  // Get Item By Inedx From The Array
  T get_item(int index) {
    if (index >= 0 && index < this->count) {
      return this->objs[index];
    } else {
      throw "Index Was Out The Bounds of The Array";
    }
  }
  // Clears The Content
  void clear() {
    delete[] this->objs;
    this->count = 0;
    this->size = 2;
    this->objs = new T[2];
  }
  // Destrutcor
  ~array_list() {
    delete[] this->objs;
  }
};
#endif
