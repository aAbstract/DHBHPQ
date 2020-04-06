#include <iostream>
#include <string>

#include "./array_list.h"
#include "./hash_table.h"
#include "./bhpq.h"

#ifndef STD
#define STD
using namespace std;
#endif

#define print(x) cout << x << endl;

int main() {
     // Array List Test
     array_list<int> list;
     for (int i = 0; i < 10; i++) {
       list.add_item(i);
     }
     for (int i = 0; i < 10; i++) {
       try {
         print(list.get_item(i));
       } catch (char const* msg) {
         print(msg);
       }
     }
    
     // Hash Table Test
     hash_table<int, string> dict;
     dict.add_item(1, "ESLAM");
     dict.add_item(2, "AHMED");
     dict.add_item(3, "EHAB");
     dict.add_item(4, "ADEL");
     dict.add_item(5, "BELAL");
     dict.add_item(6, "OSAMA");
     dict.add_item(7, "BAZA");
     dict.add_item(8, "ANYONE");
     try {
       print(dict.get_value(3));
     } catch (char const* msg) {
       print(msg);
     }
     try {
       dict.delete_item(2);
       print("Deletion Done!")
     } catch (char const* msg) {
       print(msg);
     }
     try {
       print(dict.get_value(2));
     } catch (char const* msg) {
       print(msg);
     }
     print("===============================");
     try {
       print(dict.get_value(1));
       dict.delete_item(1);
       print("Deletion Done!")
       print(dict.get_value(1));
     } catch (char const* msg) {
       print(msg);
     }
    bhpq<string> pror_q;
    try {
        pror_q.add_item(5, "ESLAM");
        pror_q.add_item(4, "ADEL");
        pror_q.add_item(3, "EHAB");
        pror_q.add_item(2, "HASSAN");
        pror_q.add_item(1, "OSAMA");
        print("Poll #1");
        print(pror_q.poll());
        print("Poll #2");
        print(pror_q.poll());
        print("Poll #3");
        print(pror_q.poll());
        print("ADD #1");
        pror_q.add_item(10, "BELAL");
        print("Poll #4");
        print(pror_q.poll());
        print("ADD #2");
        pror_q.add_item(6, "BAZA");
        print("ADD #3");
        pror_q.add_item(7, "RAMY");
        print("Poll #5");
        pror_q.remove_item("RAMY", 7);
        pror_q.remove_item("HASSAN");
        print(pror_q.poll());
        print("Poll #6");
        print(pror_q.poll());
        print(pror_q.poll()); // Should Give ERROR Because The PQ is empty
    }
    catch (char const* msg) {
        print(msg);
    }
    return 0;
}
