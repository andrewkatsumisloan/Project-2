//
//  Map.h
//  Project_2
//
//  Created by Andrew K. Sloan on 1/24/20.
//  Copyright © 2020 Andrew K. Sloan. All rights reserved.
//

#ifndef Map_h
#define Map_h

#include <iostream>
#include <string>

// Creating a Map object that contains a KeyValuePair and a 
using namespace std;

using KeyType = string;
using ValueType = double;


class Map
{
  public:

    Map();
    Map(const Map& other);
    Map& operator = (const Map& other);
    ~Map();
    
    bool empty() const;
    int size() const;
    bool insert(const KeyType& key, const ValueType& value);
    bool update(const KeyType& key, const ValueType& value);
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    bool erase(const KeyType& key);
    bool contains(const KeyType& key) const;
    bool get(const KeyType& key, ValueType& value) const;
    bool get(int i, KeyType& key, ValueType& value) const;
    void swap(Map& other);
    void dump();


private:
    
typedef struct
{
    KeyType key;
    ValueType val;
    
}KeyValuePair;
    
class Node
{
    public:
        Node();
        KeyValuePair data;
        Node* next;
        Node* prev;
};
    
Node* m_head;
};


bool combine(const Map& m1, const Map& m2, Map& result);
void reassign(const Map& m, Map& result);

#endif /* Map_hpp */



