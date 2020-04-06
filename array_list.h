#ifndef ARRAY_LIST
#define ARRAY_LIST

/* META-INF
# Interface:
  void add_item(T new_item); O(1)
  T get_item(int index); O(1)
  void clear(); O(1)
  void insert_item(int i, T v); O(1)
  void remove_last(); O(1) 
  void remove_item(int index); O(n)

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
    // Resize Allocated Memory
    void resize() {
        if ((this->count) < this->size)
            return;
        else if ((this->count) == this->size) {
            this->size = this->size * 2;
            T* new_ptr = new T[this->size];
            for (int i = 0; i < this->count; i++) {
                new_ptr[i] = this->objs[i];
            }
            delete[] this->objs;
            this->objs = new_ptr;
        }
        else {
            this->size = this->size / 2;
            T* new_ptr = new T[this->size];
            for (int i = 0; i < this->count; i++) {
                new_ptr[i] = this->objs[i];
            }
            delete[] this->objs;
            this->objs = new_ptr;
        }
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
        this->objs[this->count++] = new_item;
        this->resize();
    }
    // Get Item By Inedx From The Array
    T get_item(int index) {
        if (index >= 0 && index < this->count) {
            return this->objs[index];
        }
        else {
            throw "Index Was Out The Bounds of The Array";
        }
    }
    // Add Item In Index
    void insert_item(int i, T v) {
        if (i >= 0 && i < this->count)
            this->objs[i] = v;
        else
            throw "Index Was Out The Bounds of The Array";
    }
    // Remove Last Item in The Array
    void remove_last() {
        this->count--;
        this->resize();
    }
    // Remove First Item in The Array
    void remove_item(int index) {
        T* new_ptr = new T[this->size];
        for (int i = 0; i < this->count; i++) {
            if (index == i)
                continue;
            new_ptr[i] = this->objs[i];
        }
        this->objs = new_ptr;
        this->count--;
        this->resize();
    }
    // Get Counst of Items
    int get_count() {
        return this->count;
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
