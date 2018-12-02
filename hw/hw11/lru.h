#include <map>
#include <algorithm>
#include <list>
using namespace std;
struct Node
{
    int key;
    int value;
};
class LRUCache
{
private:
    int size;
    list<Node> cacheList;
    map<int,list<Node>::iterator> mp;
  public:
    LRUCache(int capacity)
    {
        size=capacity;
        // TODO: your code here
    }

    int get(int key)
    {
        auto it = mp.find(key);
        if(it==mp.end()){//key do not exist
            return -1;
        }
        else {//key already exist
            auto listIt=mp[key];
            Node newNode;
            newNode.key=key;
            newNode.value=listIt->value;//store its information into a new node
            cacheList.erase(listIt);//delete origin node
            cacheList.push_front(newNode);//move the new node with its information to the front of the list
            mp[key] = cacheList.begin();//change its position
        }
        return cacheList.begin()->value;
        // TODO: your code here
    }

    void put(int key, int value)
    {
        auto it = mp.find(key);
        if(it==mp.end()){//key do not exist
            if(cacheList.size()==size){//if cache is full
                mp.erase(cacheList.back().key);//delete the least recently used key
                cacheList.pop_back();//delete the least recently used key
            }
            Node newNode;
            newNode.key = key;
            newNode.value = value;//create a new node
            cacheList.push_front(newNode);//put it to the front
            mp[key] = cacheList.begin();//record its position
        }
        else {//key already exists
            auto listIt=mp[key];
            cacheList.erase(listIt);//delete it from list
            Node newNode;
            newNode.key = key;
            newNode.value = value;//create a new node to store its new information
            cacheList.push_front(newNode);//put it to the front
            mp[key] = cacheList.begin();//record its position
        }
        // TODO: your code here
    }
};
