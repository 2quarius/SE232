#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;
void solve(const vector<int> &buckets,stack<int> &bucketPos, int &capacity , int i)
{
    int right = buckets[i+1];
    int mid =buckets[bucketPos.top()];
    do{
        bucketPos.pop();
    }
    while (!bucketPos.empty()&&buckets[bucketPos.top()]<=mid);
    if(!bucketPos.empty()) {
        int left = buckets[bucketPos.top()];
        if (left > right) {
            capacity = capacity + (i + 1 - bucketPos.top() - 1) * (right-mid);
            bucketPos.push(i + 1);
        }
        else if(left==right){
            capacity = capacity + (i + 1 - bucketPos.top() - 1) * (left-mid);
            bucketPos.pop();
            bucketPos.push(i + 1);
        }
        else {
            capacity = capacity + (i + 1 - bucketPos.top() - 1) * (left-mid);
            solve(buckets,bucketPos,capacity,i);//recursion
        }
    }
    else bucketPos.push(i+1);
}
int main() {
    vector<int> buckets;
    char height;
    string h;
    while(cin>>height)
    {
        if(height!=','){h+=height;}
        else {
            buckets.push_back(stoi(h));
            h.clear();
        }
    }
    buckets.push_back(stoi(h));
    stack<int> bucketPos;//store each bucket's position in vector 'buckets', so we can access bucket's height by buckets[i]
    int i=0,capacity=0;
    bucketPos.push(i);
    while((i+1)<buckets.size()){
        if(buckets[i+1]<=buckets[i]) {bucketPos.push(i+1);}
        else {
            //encounter a upstair edge
            solve(buckets,bucketPos,capacity,i);
        }
        i++;
    }
    cout << capacity;
    return 0;
}