#include <iostream>
#include "lru.h"
int main() {
    LRUCache cache(3);
    cache.put(1,1);
    cache.put(2,2);
    cache.put(3,3);
    cache.put(4,4);
    cout<<cache.get(4)<<endl;
    cout<<cache.get(3)<<endl;
    cout<<cache.get(2)<<endl;
    cout<<cache.get(1)<<endl;

    cache.put(5,5);
    cout<<cache.get(1)<<endl;
    cout<<cache.get(2)<<endl;
    cout<<cache.get(3)<<endl;
    cout<<cache.get(4)<<endl;
    cout<<cache.get(5)<<endl;

    //std::cout << "Hello, World!" << std::endl;
    return 0;
}