/*
 * File: WordLadder.cpp
 * --------------------
 * [TODO: fill in your name and student ID]
 * Name:刘佳
 * Student ID:517021911048
 * This file is the starter project for the word ladder problem of Lab 2.
 * [TODO: extend the documentation]
 *
 * Program Log
 * 2018-10-19: almost meet basic requirements, do nothing to check user's input word
 * 2018-11-05: shrink time consumption
 */

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <queue>
#include <vector>
#include <map>
using namespace std;

//find the dest and init
void show_ans(vector<string> &ans);

//input and start function
void input_words(string &start, string &dest);

// read lexicon from file
void read_english(set<string> &english);

void show_ans(vector<string> &ans)
{
    cout << "Found ladder:";
    cout << ans[0];
    for (int i = 1; i < ans.size(); i++)
    {
        cout << "->" << ans[i];
    }
    cout << endl
         << endl;
}

void input_words(string &start, string &dest)
{
    cout << "Enter start word (enter ':q' to quit):";
    cin >> start;
    if (start == ":q")
    {
        exit(0);
    }
    cout << "Enter destination word:";
    cin >> dest;
}

void read_english(map<string,int> &english)
{
    while (true)
    {
        cout << "Please enter filename containing source text:";
        string file_name;
        cin >> file_name;
        ifstream file_input(file_name.c_str());
        if (file_input.is_open())
        {
            string temp_word;
            while (getline(file_input, temp_word))
            {
                english.insert(make_pair(temp_word,1));
            }
            break;
        }
        else cout << "error" << endl;
    }
}

int main()
{
    // TODO: your code
    //clock_t b,m,mb,e;
    //b = clock();
    map<string,int> english;//store valid english words
    read_english(english);
    //m = clock();
    //cout << double(m-b)/CLOCKS_PER_SEC <<endl;
    //mb = clock();
    string start, dest;
    input_words(start, dest);
    queue<vector<string>> ladderqueue;//store any possible ladder vector, after every loop ladder increase,
    vector<string> ladders;//which means after every loop, size of vector increase one,
    ladders.push_back(start);//moreover, after every loop, lower ladders are poped.
    ladderqueue.push(ladders);
    auto lexicon = english.find(start);
    lexicon->second=0;
    while (!ladderqueue.empty()) {
        vector<string> laddertmp = ladderqueue.front();
        if (laddertmp.back() == dest) {
            show_ans(laddertmp);
            return 0;
        }
        string temp=laddertmp.back();
        for(int i=0;i<temp.size();i++)//change every letter from 'a' to 'z' in order
        {
            for(char j='a';j<='z';j++)
            {
                temp[i] = j;
                if(english.count(temp)==1){
                    lexicon = english.find(temp);
                    if(lexicon->second==1){
                        laddertmp.push_back(lexicon->first);
                        ladderqueue.push(laddertmp);
                        laddertmp = ladderqueue.front();
                        lexicon->second=0;
                    }
                }
            }
            temp[i] = laddertmp.back()[i];//do not forget to reset it to origin for next set
        }
        ladderqueue.pop();
    }
    //e = clock();
    //cout << double(e - mb) / CLOCKS_PER_SEC << endl;

    cout << "No ladder\n" ;
    return 0;
}
