/*
 * File: RandomWriter.cpp
 * ----------------------
 * [TODO: fill in your name and student ID]
 * Name:刘佳
 * Student ID:517021911048
 * This file is the starter project for the random writer problem of Lab 2.
 * [TODO: extend the documentation]
 *
 * Program Log
 * 2018-10-20: almost meet the requirements listed, but I only tested lab2/RandomWriter/aLetter.txt
 * 2018-10-26: change seed source and simplify some blocks
 * 2018-10-28：rewrite find_most function,but when testing lab2/RandomWriter/ladygaga.txt it falls into magic loop.
 */

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <ctime>
#include <algorithm>
#include <random>
using namespace std;
#define MAX_CHAR_NUM 2000

// get filename
void read_file(ifstream &file_input);

// get order number
int read_order();

// build model
void model_read(ifstream &file_input, const int &order, map<string, vector<char>> &model);

// write
void random_write(const int &order, map<string, vector<char>> &model);

void read_file(ifstream &file_input)
{
    // TODO: your code here
    cout << "Please enter filename containing source text:";
    string file_name;
    cin >> file_name;
    file_input.open(file_name.c_str());
}

int read_order()
{
    // TODO: your code here
    cout << "Please choose order(1-10):";
    int order;
    cin >> order;
    return order;
}

void model_read(ifstream &file_input, const int &order, map<string, vector<char>> &model)
{
    // TODO: your code here
    string former,s;
    vector<char> latter;
    int length=0;
    if(!file_input.is_open()){
        cout << "file not open\n";
        return;
    }
    char ch;
    while(file_input.get(ch)){
        s+=ch;
        length++;
        if(length%order==0){
            former=s;
            file_input.get(ch);
            if(model.count(former)==0){
                latter.clear();
                latter.push_back(ch);
                model.insert(make_pair(former,latter));
            }
            else if(model.count(former)==1){
                auto it = model.find(former);
                (it->second).push_back(ch);
            }
            file_input.putback(ch);
            s = s.substr(1);
            length--;
        }
    }

}

void random_write(const int &order, map<string, vector<char>> &model)
{
    // TODO: your code here
    string seed;
    unsigned long sum=0;
    for(auto elem:model)
    {
        sum+=elem.second.size();
    }
    srand(time(0));
    unsigned long index=rand()%sum,scope=0;
    for(auto elem:model)
    {
        if(scope/index>0){
            seed=elem.first;
            break;
        }
        else if(scope/index==0)
        {
            scope+=elem.second.size();
        }
    }
    cout<<seed;
    int num=MAX_CHAR_NUM;
    for(auto it=model.find(seed);it!=model.end()&&num>0;it = model.find(seed)){
        vector<char> vec=it->second;
        if(!vec.empty()){
            int tmp=rand();
            cout << vec[tmp%vec.size()];
            seed=seed.substr(1);
            seed+=vec[tmp%vec.size()];
            num--;
            srand(tmp);
        }
        else break;
    }
}

int main()
{
    // TODO: your code here
    ifstream input;
    read_file(input);
    int order=read_order();
    map<string,vector<char>> model;
    model_read(input,order,model);
    random_write(order,model);
    return 0;
}
