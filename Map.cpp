//
//  Map.cpp
//  Project_2
//
//  Created by Andrew K. Sloan on 1/24/20.
//  Copyright © 2020 Andrew K. Sloan. All rights reserved.
//

#include "Map.h"
#include <iostream>

using namespace std;


Map::Map()
{
    m_head = nullptr;
}

// Constructor for node
Map::Node::Node()
{
    // Assign the next and previous to nullptr
    this->next = nullptr;
    this->prev = nullptr;
}

// Copy constructor
Map::Map(const Map& other)
{
    // Copy constructor to initialize values using other Map
    m_head = nullptr;
    KeyType key;
    ValueType val;
    
    int osz = other.size();
    for (int i = 0; i < osz; i++)
    {
        other.get(i, key, val);
        this->insert(key, val);
    }
}

// Assignment operator
Map& Map::operator = (const Map& other)
{
    // Where this refers to the map that is calling the function
    int sz = this->size();
    KeyType key;
    ValueType val;
    
    // This deletes everything in Map b
    // This refers to b, assuming our statement reads Map b = a;
    for (int i = 0; i < sz; i++)
    {
        this->get(0, key, val);
        this->erase(key);
    }

    int osz = other.size();
    for (int i = 0; i < osz; i++)
    {
        other.get(i, key, val);
        this->insert(key, val);
    }
    // Map b = a, b is this
    // Map b(a);
    return *this;
}

// Destructor
Map::~Map()
{
    KeyType k;
    ValueType v;
    int size = this->size();
    // Must erase all keys and values in list
    for (int i = 0; i < size; i++)
    {
        this->get(0, k, v);
        this->erase(k);
    }
}

bool Map::empty() const
{
    // Return true if m_head is nullptr
    return(m_head==nullptr);
}

int Map::size() const
{
    // Assign Node type pointer to m_head
    Node* n = m_head;
    // If empty, return zero
    if (m_head == nullptr)
    {
        return 0;
    }

    int count = 0;
    // While valid, iterate over the Linked List, increment the counter
    while (n != nullptr)
    {
        n = n->next;
        count++;
    }
    return count;
}

// You are inserting a key and value if the key does not exist
// If they key exists, return false
bool Map::insert(const KeyType& key, const ValueType& value)
{
    if (this->empty())
    {
        m_head = new Node;
        // new __ always returns a pointer
        // If decide to make it circular, must add another pointer
        
        m_head->data.key = key;
        m_head->data.val = value;
        
    }
    else
    {
        Node* n = m_head;
        Node* prev = m_head;
        while (n != nullptr)
        {
            if (n->data.key == key)
            {
                return false;
            }
            prev = n;
            n = n->next;
        }
        n = new Node;
        n->data.key = key;
        n->data.val = value;
        n->prev = prev;
        prev->next = n;
    }
    return true;
}

bool Map::update(const KeyType& key, const ValueType& value)
{
    // If key is equal to a key currently in the map, then make that key no
    // longer map to the value it currently maps to, but instead map to
    // the value of the second parameter; return true in this case.
    // Otherwise, make no change to the map and return false.
    Node* n = m_head;
    while (n != nullptr)
    {
        // Update values of node if key is equal to key param
        if (n->data.key == key)
        {
            n->data.val = value;
            return true;
        }
        n = n->next;
    }
    return false;
}

bool Map::insertOrUpdate(const KeyType &key, const ValueType &value)
{
    // If the map you are applying the function to contains the key parameter that you passed in, then return the map with the new parameter.
    // Otherwise, return the map with the inserted key and value parameter.
    if (this-> contains(key))
    {
        return this->update(key, value);
    }
    else
    {
        return this->insert(key, value);
    }
    return false;
}

bool Map::erase(const KeyType& key)
{
    Node* n = m_head;
    while (n != nullptr)
    {
        
        if (n->data.key == key)
        {
            Node* next = n->next;
            Node* prev = n->prev;
//          This checks to see if the data member prev (which stores the pointer to the preceding node) is nullptr, i.e if it is the first term in the linked list.  If it is not, it sets the previous node's next to the current node's next.
            if (prev != nullptr)
            {
                prev->next = next;
            }

//          This checks to see that the node is not the last node in the list, and assigns to it the current nodes previous.
            
            if (next != nullptr)
            {
                next->prev = prev;
            }

            if (n == m_head)
            {
                m_head = next;
            }
            delete n;
            return true;
        }
        n = n->next;
        
    }
    return false;
}

bool Map::contains(const KeyType& key) const
{
    // Return true if key is equal to a key currently in the map, otherwise false
    Node* n = m_head;
    while (n != nullptr)
    {
        if (n->data.key == key)
        {
            return true;
        }
        n = n->next;
    }
    return false;
}

bool Map::get(const KeyType &key, ValueType &value) const
{
    Node* n = m_head;
    while (n != nullptr)
    {
        // If the key is equal to the key parameter, set the value parameter equal to n's value
        if (n->data.key == key)
        {
            value = n->data.val;
            return true;
        }
        n = n->next;
    }
    return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
    if (i < 0)
    {
        return false;
    }
    // Define a node n set to m_head
    Node* n = m_head;
    int count = 0;
    while (n != nullptr)
    {
        // At the ith position, assign the value of n's key and value to that of the key and value parameter
        if (count == i)
        {
            key = n->data.key;
            value = n->data.val;
            return true;
        }
        count ++;
        n = n->next;
    }
    return false;
}


void Map::swap(Map& other)
{
    // Declare a temporary map
    Map tempMap;
    // Set this temporary map equal to the Map that you passed in
    tempMap = other;
    // Set the parameter, other map, to original map (the map that you is calling the swap function
    other = *this;
    // Set the map that is calling swap equal to the temporary map (the temporary map holds the parameter map 'other'
    *this = tempMap;
}


bool combine(const Map& m1, const Map& m2, Map& result)
{
    // The combine function takes the references to two maps, and a "result" Map
    // If a key appears in exactly one of m1 or m2, then result must contain a pair consisting of that key and its corresponding value.
    // If a key appears in both m1 and m2, with the same corresponding value in both, then result must contain exactly one pair with that key and value.
    // You must not assume result is empty when it is passed into this function, it may not be.
    // Return false if there is a key that is in both m1 and m2, but has different corresponding values.  If there is no key like this, return true.  Even if you return false, result should still be constituted as defined above.
    
    int sz = result.size();
    KeyType key;
    ValueType val;
    for (int i = 0; i < sz; i++)
    {
        result.get(0, key, val);
        result.erase(key);
    }
    
    int m1sz = m1.size();
    int m2sz = m2.size();
    KeyType k1, k2;
    ValueType v1, v2;
    bool noconflict = true;
    for (int i = 0; i < m1sz; i++)
    {
        
        m1.get(i, k1, v1);
        if (m2.contains(k1))
        {
            m2.get(k1, v2);
            if (v1 != v2)
            {
                noconflict = false;
            }
            else
            {
                result.insert(k1, v1);
            }
        }
        else
        {
            result.insert(k1, v1);
        }
        
    }
    for (int i = 0; i < m2sz; i++)
    {
        m2.get(i, k2, v2);
        if (m1.contains(k2))
        {
            m1.get(k2, v1);
            if (v1 == v2)
            {
                result.insert(k2, v2);
            }
        }
        else
        {
            result.insert(k2, v2);
        }
      
  }
    return noconflict;
}

void reassign(const Map& m, Map& result)
{
    // The reassign function takes a reference to a Map
    // Because it is not a member function of Map, it can not access the private member variables.
    KeyType k, k1;
    ValueType v, v1, last;
    int sz = result.size();
    for (int i = 0; i < sz; i++)
    {
        result.get(0, k, v);
        result.erase(k);
    }
    
    if (m.size() == 1)
    {
        for (int i = 0; i < 1; i++)
        {
            result = m;
        }
    }
    for (int i = 0; i < m.size(); i++)
    {
        m.get(i, k, v);
        if (i == 0)
        {
            m.get(m.size()-1, k1, v1);
            result.insert(k, v1);
        }
        else
        {
            result.insert(k, last);
        }
        last = v;
        
    }
        
}


void Map::dump()
{
    Node* n = m_head;
    while (n != nullptr)
    {
        cout << n->data.val << endl;
        n = n->next;
    }
}

