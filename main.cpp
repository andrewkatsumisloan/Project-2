//
//  main.cpp
//  Project_2
//
//  Created by Andrew K. Sloan on 1/24/20.
//  Copyright © 2020 Andrew K. Sloan. All rights reserved.
//

#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

int main() {
    Map a;
    a.insert("Andrew", 21);
    a.insert("JB", 77);
    a.insert("BS", 78);
    a.insert("EW", 70);
    a.update("Andrew", 35);
    
    Map b = a;
    b.dump();
    
    KeyType k;
    ValueType v;

    a.get(2, k, v);
    
    cout << k << " " << v << endl;
    
}



