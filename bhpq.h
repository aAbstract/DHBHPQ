#ifndef BHPQ
#define BHPQ

/* META-INF
# Interface:
  void add_item(int pror, T value); O(log(n))
  T poll(); O(log(n))
  T peek(); O(1)
  void change_pror(int old_pror, T value, int new_pror); O(log(n))
  void clear(); O(1)
  bool is_empty(); O(1)
  int get_size(); O(1)
  void remove_item(T value, int pror); O(log(n))
  void remove_item(T value); O(n)

  Space: O(n)
*/

#include <stdlib.h>
#include <functional>

#include "./array_list.h"
#include "./hash_table.h"

// Include Namespace Protection
#ifndef STD
#define STD
using namespace std;
#endif

// Priority Value Pair Node
template<typename T>
class pv_node {
    // Private Fields
    // var pror : key object
    // var value : value object associated with the given priority
private:
    int pror;
    T value;
public:
    // Default Constructor
    pv_node() { this->pror = -1; } // Used From Dynamic Allocation
    pv_node(int _pror, T _value) {
        this->pror = _pror;
        this->value = _value;
    }
    // Class Getters
    int get_pror() const { return this->pror; }
    T get_value() const { return this->value; }
    // Class Setters
    void set_pror(int new_pror) { this->pror = new_pror; }
    void set_value(T new_value) { this->value = new_value; }
    bool operator==(const pv_node<T>& target) {
        return ((this->get_pror() == target.get_pror()) &&
            (this->get_value() == target.get_value()));
    }
};

namespace std {
    template<typename T>
    struct hash<pv_node<T>> {
        size_t operator()(const pv_node<T>& node) const {
            hash<int> uni_hash1;
            hash<T> uni_hash2;
            return (uni_hash1(node.get_pror()) + uni_hash2(node.get_value()));
        }
    };
};

template<typename T>
class bhpq {
    // Private Fields
    // var objs_map : hash table that keeps track of each item by their index
    // var count : count of elements in the queue
private:
    hash_table<pv_node<T>, int> objs_map;
    array_list<pv_node<T>> objs;
    int count;

    // Helper Functions
    // Swap Two Nodes
    void swap(int i1, int i2) {
        pv_node<T> n1 = this->objs.get_item(i1);
        pv_node<T> n2 = this->objs.get_item(i2);
        this->objs.insert_item(i1, n2);
        this->objs.insert_item(i2, n1);
        // Swap Addressing in The Hash Table
        int itemp = this->objs_map.get_value(n1);
        this->objs_map.set_new_value(n1, this->objs_map.get_value(n2));
        this->objs_map.set_new_value(n2, itemp);
    }
    // Get Parent of Index x in The Heap
    int get_parent(int x) {
        if (x == 0)
            return -1;
        if (x == 2 || x == 1)
            return 0;
        return (x - abs(x % 2) - 2) / 2;
    }
    // Get Child of Index X in the Heap
    int get_child(char dir, int x) {
        if (dir == 'l')
            if ((2 * x + 1) < this->count)
                return (2 * x + 1);
            else
                return -1;
        else
            if ((2 * x + 2) < this->count)
                return (2 * x + 2);
            else
                return -1;
    }
    // Appay Heap Invariacne On index x;
    void invariacne(int x) {
        // Default Case
        if (x == 0 &&
            this->get_child('l', x) == -1 &&
            this->get_child('r', x) == -1
            )return;
        // Invariacne Holds
        pv_node<T> node = this->objs.get_item(x);
        pv_node<T> parent;
        pv_node<T> child_left;
        pv_node<T> child_right;
        if (this->get_parent(x) != -1)
            parent = this->objs.get_item(this->get_parent(x));
        if (this->get_child('l', x) != -1)
            child_left = this->objs.get_item(this->get_child('l', x));
        if (this->get_child('r', x) != -1)
            child_right = this->objs.get_item(this->get_child('r', x));
        if (parent.get_pror() != -1) {
            if (node.get_pror() <= parent.get_pror()) {
                if (child_left.get_pror() == -1)
                    return;
                if (child_right.get_pror() == -1 && node.get_pror() >= child_left.get_pror())
                    return;
                if (node.get_pror() >= child_left.get_pror() &&
                    node.get_pror() >= child_right.get_pror())
                    return;
            }
        }
        else {
            if (child_left.get_pror() == -1)
                return;
            if (child_right.get_pror() == -1 && node.get_pror() >= child_left.get_pror())
                return;
            if (node.get_pror() >= child_left.get_pror() &&
                node.get_pror() >= child_right.get_pror())
                return;
        }
        // Invariacne Doesn't Hold
        if (x != 0 && (node.get_pror() > parent.get_pror())) {
            do {
                this->swap(x, this->get_parent(x));
                x = this->get_parent(x);
                int pi = this->get_parent(x);
                if (pi == -1)
                    return;
                parent = this->objs.get_item(pi);
                node = this->objs.get_item(x);
            } while (node.get_pror() > parent.get_pror());
        }
        else if (child_left.get_pror() != -1 && (node.get_pror() < child_left.get_pror() ||
            child_right.get_pror() == child_left.get_pror()) && child_right.get_pror() < child_left.get_pror()) {
            do {
                this->swap(x, this->get_child('l', x));
                x = this->get_child('l', x);
                int ci = this->get_child('l', x);
                if (ci == -1)
                    return;
                child_left = this->objs.get_item(ci);
                node = this->objs.get_item(x);
            } while ((node.get_pror() < child_left.get_pror()) && (
                node.get_pror() < child_left.get_pror() ||
                child_right.get_pror() == child_left.get_pror()
                ));
        }
        else if (child_right.get_pror() != -1) {
            do {
                this->swap(x, this->get_child('r', x));
                x = this->get_child('r', x);
                int ci = this->get_child('r', x);
                if (ci == -1)
                    return;
                child_right = this->objs.get_item(ci);
                node = this->objs.get_item(x);
            } while (node.get_pror() < child_right.get_pror());
        }
    }
public:
    // Default Constructor
    bhpq() { this->count = 0; }
    // Return Wheather The Queue is Empty
    bool is_empty() {
        return (this->count == 0);
    }
    // Returns Queue Size
    int get_size() {
        return this->count;
    }
    void add_item(int pror, T value) {
        pv_node<T> node(pror, value);
        this->objs.add_item(node);
        this->objs_map.add_item(node, this->count);
        this->count++;
        try {
            this->invariacne(this->count - 1);
        }
        catch (char const* msg) {
            throw msg;
        }
    }
    // Poll Highest Node
    T poll() {
        pv_node<T> root_node = this->objs.get_item(0);
        this->swap(0, this->count - 1);
        this->objs.remove_last();
        try {
            this->objs_map.delete_item(root_node);
        }
        catch (char const* msg) {
            throw msg;
        }
        this->count--;
        this->invariacne(0);
        return root_node.get_value();
    }
    // Peek Highest Node
    T peek() {
        return this->objs.get_item(0).get_value();
    }
    // Change Item Priority
    void change_pror(int old_pror, T value, int new_pror) {
        pv_node<T> node(old_pror, value);
        try {
            int obj_index = this->objs_map.get_value(node);
            this->objs.get_item(obj_index).set_pror(new_pror);
            this->invariacne(obj_index);
        }
        catch (char const* msg) {
            throw msg;
        }
    }
    // Remove Item
    void remove_item(T value) {
        int tp;
        for (int i = 0; i < this->count; i++) {
            if (this->objs.get_item(i).get_value() == value) {
                tp = this->objs.get_item(i).get_pror();
                break;
            }
        }
        this->remove_item(value, tp);
    }
    // Remove Item
    void remove_item(T value, int pror) {
        if (this->count == 1) {
            this->clear();
            return;
        }
        pv_node<T> target(pror, value);
        int ti;
        try {
            ti = this->objs_map.get_value(target);
        }
        catch (char const* msg) {
            throw msg;
        }
        if (ti == (this->count - 1)) {
            this->objs.remove_last();
            this->count--;
        }
        else {
            this->swap(ti, this->count - 1);
            this->objs.remove_last();
            this->count--;
            this->invariacne(ti);
        }
    }
    // Clears The Memory
    void clear() {
        this->count = 0;
        this->objs.clear();
        this->objs_map.clear();
    }
    // Destrutcor
    ~bhpq() {
        this->objs.clear();
        this->objs_map.clear();
    }
};
#endif
