#include <iostream>
#include <vector>
#include <string>

using namespace std;
int main() {
    vector<int> cake;
    char height;
    string h;
    while(cin>>height)
    {
        if(height!=','){h+=height;}
        else {
            cake.push_back(stoi(h));
            h.clear();
        }
    }
    cake.push_back(stoi(h));
    vector<int> cakes;
    for(int i=0;i<cake.size();i++)
    {
        int curHeight=cake[i],output=cake[i];
        for(int j=i+1;j<cake.size();j++)
        {
            if(cake[j]<curHeight){
                output+=curHeight*(j-i-1);
                break;
            }
            else if(j==cake.size()-1){
                output+=curHeight*(j-i);
            }
        }
        for(int k=i-1;k>=0;k--)
        {
            if(cake[k]<curHeight){
                output+=curHeight*(i-k-1);
                break;
            }
            else if(k==0){
                output+=curHeight*(i-k);
            }
        }
        cakes.push_back(output);
    }
    int max=cakes[0];
    for(int i=0;i<cakes.size();i++)
    {
        if(cakes[i]>max){max=cakes[i];}
    }
    cout << max;
    return 0;
}