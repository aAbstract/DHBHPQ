#include <iostream>
#include <string>

#include "./array_list.h"
#include "./hash_table.h"

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
  try {
    print(dict.get_value(4));
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
  return 0;
}
