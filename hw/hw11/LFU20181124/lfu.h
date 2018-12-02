#include <list>
#include <unordered_map>
using namespace std;
class LFUCache {
private:
    struct FreNode{
        int fre;
        list<pair<int, int>> val;//maxsubfre to minsubfre, {key,value} key is used when cache fills map.erase(it->first)
    };
    int cap;
    int total;
    list<FreNode> freList;//minfre to maxfre, every FreNode stores {key,value} with the same frequency
    unordered_map<int, pair<list<pair<int, int>>::iterator, list<FreNode>::iterator>> mp;//key to {FreNode position,freList position}
public:
    LFUCache(int capacity) {
        cap = capacity;
        total = 0;
    }

    int get(int key) {
        if (cap == 0) return -1;
        if (mp.count(key) <= 0) return -1;
        auto ptr = mp[key].first;
        auto iter = mp[key].second;
        auto value = *ptr;
        iter->val.erase(ptr);//delete it from frequency list
        int originFre = iter->fre;
        auto iterLatter = iter;
        ++iterLatter;
        if (iterLatter == freList.end() || iterLatter->fre != originFre + 1){
            FreNode node;//create a new node
            node.fre = originFre + 1;
            freList.insert(iterLatter, node);//put it into proper position of freList
        }
        iterLatter = iter;
        ++iterLatter;
        iterLatter->val.push_front(value);
        mp[key].first = iterLatter->val.begin();
        mp[key].second = iterLatter;
        if (iter->val.empty()){//if no key matches this frequency, delete FreNode from freList
            freList.erase(iter);
        }
        return value.second;
    }

    void put(int key, int value) {
        if (cap == 0) return;
        if (mp.count(key)){
            auto ptr = mp[key].first;
            auto iter = mp[key].second;
            auto originValue = *ptr;
            iter->val.erase(ptr);//delete it from frequency list because its frequency increases
            int originFre = iter->fre;
            auto iterLatter = iter;
            ++iterLatter;
            if (iterLatter == freList.end() || iterLatter->fre != originFre + 1){//if the exact frequency does not exist
                FreNode node;//create a new node
                node.fre = originFre + 1;
                freList.insert(iterLatter, node);//put it into proper place
            }
            iterLatter = iter;
            ++iterLatter;
            auto newValue = originValue;
            newValue.second = value;
            iterLatter->val.push_front(newValue);//reset it to front
            mp[key].first = iterLatter->val.begin();
            mp[key].second = iterLatter;
            if (iter->val.empty()){
                freList.erase(iter);
            }
            return;
        }
        if (total == cap){//if cache is full
            auto iter = freList.begin();
            auto ptr = iter->val.end();
            --ptr;
            mp.erase(ptr->first);//delete least frequently used key
            iter->val.pop_back();//pop least frequently used key
            if (iter->val.empty()){
                freList.pop_front();
            }
            --total;
        }
        if (freList.empty() || freList.front().fre != 1){
            FreNode node;
            node.fre = 1;
            freList.push_front(node);
        }
        freList.front().val.push_front(make_pair(key, value));
        mp[key] = make_pair(freList.front().val.begin(), freList.begin());
        ++total;
    }


};

