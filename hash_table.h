#ifndef HASH_TABLE
#define HASH_TABLE

/* META-INF
# Interface:
  void add_item(TK key, TV value); O(1)*
  TV get_value(TK key); O(1)*
  void set_new_value(TK key, TV new_value); O(1)*
  void clear(); O(1)
  void delete_item(TK key); O(1)*
  is_empty(); O(1)

  Space: O(n)
*/

#include <functional>
#include <string>

// Constant Definations
// const TOMP_STONE : place holder for deletd
#define TOMP_STONE "TOMP_STONE"

// Include Lib Protection
#ifndef STD
#define STD
using namespace std;
#endif

// Key Value Pair Node
template<typename TK, typename TV>
class kvp_node {
    // Private Fields
    // var key : key object
    // var value : value object associated with the given key
    // var state : indicates if it's tomp stone or unassigned
private:
    TK key;
    TV value;
    string state;
public:
    // Default Constructor
    kvp_node(TK _key, TV _value) {
        this->key = _key;
        this->value = _value;
        this->state = "";
    }
    // Class Getters
    TK get_key() { return this->key; }
    TV get_value() { return this->value; }
    string get_state() { return this->state; }
    // Class Setters
    void set_state(string new_state) { this->state = new_state; }
    void set_value(TV new_value) { this->value = new_value; }
};

// Hash Table Implementation
template<typename TK, typename TV>
class hash_table {
    // Private Fields
    // var size : current size of the hash table
    // var count : current objects count
    // var get_hash : Object That Computes The Hash of The Key Using The Universal Hashing Algorithm
    // var objs : array of Key Value Pair Nodes
    // const tolerance : max ratio can be used before the table get resized
private:
    int count;
    int size;
    hash<TK> get_hash;
    kvp_node<TK, TV>** objs;
    float const tolerance = .6f;

    // Helper Functions
    // Check if x is Prime
    bool is_prime(int x) {
        int divisor = 2;
        bool out = true;
        while (divisor < x) {
            if (x % divisor == 0) {
                out = false;
                break;
            }
            divisor++;
        }
        return out;
    }
    // Get The Next Prime After x
    int get_next_prime(int x) {
        while (!is_prime(++x))
            continue;
        return x;
    }
    // Initlize The Table
    void init() {
        for (int i = 0; i < this->size; i++)
            this->objs[i] = nullptr;
    }
    // Assign Item in The Hash Table According To Open Addressing Algorithm
    void assign(TK key, TV value) {
        int key_hash = this->get_hash(key) % this->size;
        if (this->objs[key_hash] == nullptr)
            this->objs[key_hash] = new kvp_node<TK, TV>(key, value);
        else {
            // Open Addressing Algorithm
            int trav_times = 1;
            int delta = key_hash % this->size;
            delta = (delta == 0) ? 1 : delta;
            int offset = trav_times * delta;
            int new_addr = (key_hash + offset) % this->size;
            while (this->objs[new_addr] != nullptr) {
                offset = (++trav_times) * delta;
            }
            this->objs[new_addr] = new kvp_node<TK, TV>(key, value);
        }
    }
    // General Resize Subroutine
    void mem_resize(int old_size) {
        kvp_node<TK, TV>** old_ptr = this->objs;
        kvp_node<TK, TV>** new_ptr = new kvp_node<TK, TV> * [this->size];
        this->objs = new_ptr;
        this->init();
        for (int i = 0; i < old_size; i++) {
            if (old_ptr[i] != nullptr && old_ptr[i]->get_state() != TOMP_STONE) {
                this->assign(old_ptr[i]->get_key(), old_ptr[i]->get_value());
                delete old_ptr[i];
            }
        }
        delete[] old_ptr;
    }
public:
    // Default Constructor
    hash_table() {
        this->size = 2;
        this->objs = new kvp_node<TK, TV> * [this->size];
        this->init();
    }
    // Add Mapping To The Hash Table
    void add_item(TK key, TV value) {
        if (++(this->count) > int(this->size * this->tolerance)) {
            int new_size = this->get_next_prime(this->size * 2);
            int old_size = this->size;
            this->size = new_size;
            mem_resize(old_size);
        }
        this->assign(key, value);
    }
    // Value Lookup
    TV get_value(TK key) {
        int key_hash = this->get_hash(key) % this->size;
        kvp_node<TK, TV>* node = this->objs[key_hash];
        int first_tomp_stone_index = -1;
        int trav_times = 1;
        int delta = key_hash % this->size;
        delta = (delta == 0) ? 1 : delta;
        int offset = trav_times * delta;
        int new_addr = (key_hash + offset) % this->size;
        while (true) {
            if (node == nullptr)
                throw "This Key is Not Exist";
            else if (node->get_state() == TOMP_STONE) {
                if (first_tomp_stone_index == -1)
                    first_tomp_stone_index = new_addr;
            }
            else if (node->get_key() == key) {
                // Optimiztion Hack
                if (first_tomp_stone_index != -1) {
                    this->objs[first_tomp_stone_index] = node;
                    this->objs[new_addr] = nullptr;
                }
                return node->get_value();
            }
            offset = (++trav_times) * delta;
            new_addr = (key_hash + offset) % this->size;
            node = this->objs[new_addr];
        }
    }
    // Sets New Value For Given Key
    void set_new_value(TK key, TV new_value) {
        int key_hash = this->get_hash(key) % this->size;
        kvp_node<TK, TV>* node = this->objs[key_hash];
        int first_tomp_stone_index = -1;
        int trav_times = 1;
        int delta = key_hash % this->size;
        delta = (delta == 0) ? 1 : delta;
        int offset = trav_times * delta;
        int new_addr = (key_hash + offset) % this->size;
        while (true) {
            if (node == nullptr)
                throw "This Key is Not Exist";
            else if (node->get_state() == TOMP_STONE) {
                if (first_tomp_stone_index == -1)
                    first_tomp_stone_index = new_addr;
            }
            else if (node->get_key() == key) {
                // Optimiztion Hack
                if (first_tomp_stone_index != -1) {
                    this->objs[first_tomp_stone_index] = node;
                    this->objs[new_addr] = nullptr;
                }
                node->set_value(new_value);
                break;
            }
            offset = (++trav_times) * delta;
            node = this->objs[new_addr];
        }
    }
    // Delete Item by Key
    void delete_item(TK key) {
        int key_hash = this->get_hash(key) % this->size;
        kvp_node<TK, TV>* node = this->objs[key_hash];
        int first_tomp_stone_index = -1;
        int trav_times = 1;
        int delta = key_hash % this->size;
        delta = (delta == 0) ? 1 : delta;
        int offset = trav_times * delta;
        int new_addr = (key_hash + offset) % this->size;
        while (true) {
            if (node == nullptr)
                throw "This Key is Not Exist";
            else if (node->get_state() == TOMP_STONE) {
                if (first_tomp_stone_index == -1)
                    first_tomp_stone_index = new_addr;
            }
            else if (node->get_key() == key) {
                node->set_state(TOMP_STONE);
                break;
            }
            offset = (++trav_times) * delta;
            kvp_node<TK, TV>* node = this->objs[new_addr];
        }
    }
    // Clear All Items
    void clear() {
        for (int i = 0; i < this->size; i++) {
            delete this->objs[i];
        }
        delete[] this->objs;
        this->size = 2;
        this->count = 0;
        this->objs = new kvp_node<TK, TV> * [this->size];
        this->init();
    }
    // Check if Empty
    bool is_empty() {
        return (this->count == 0);
    }
    // Destrutcor
    ~hash_table() {
        for (int i = 0; i < this->size; i++) {
            delete this->objs[i];
        }
        delete[] this->objs;
    }
};
#endif
