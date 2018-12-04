#pragma warning(disable:4786)
#pragma warning(disable:4503)
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <cctype>
#include <stdio.h>
using namespace std;

void Show(vector<string>::const_iterator begin,vector<string>::const_iterator end)
{
    while(begin!= end)
    {
        cout<<*begin++<<" ";
    }
}
string inputStr()
{
    string str;
    cin>>str;
    return str;
}

string toEnglish(string &str)
{

    if(ispunct(str[0]))
    {
        str[0]=' ';
        //for(int i=0; i<str.size()-2;i++)
        //{
        //    tmp[i]= str[i+1];
        //}
        //return *p;
    }
    else if(ispunct(str[str.size()-1]))
    {
        str[str.size()-1]=' ';
        //for(int i=0;i<str.size()-2;i++)
        //{
        //    tmp[i]=str[i];
        //}
        //return *p;
    }
    return str;
}
int main() {
    ifstream infile("shakespeare.txt",ios::in);
    if(!infile)
    {
        cerr<<"open file error!"<<endl;
        exit(1);
    }
    string str;
    unsigned int line = 0;
    string strFind = inputStr();
    map<unsigned int, vector<string>> element;
    bool enter = false;

    while(getline(infile,str))
    {
        enter = false;
        string tmp;
        line++;
        istringstream stream(str);
        string word;
        bool flag = 0;
        vector<string> sentence;
        while(stream >> word)
        {
            if(strFind!=word)
            {
                tmp = word;
            }
            if(strFind == word)
            {
                enter = true;
            }
            if(true == enter&&flag == 0)
            {
                tmp = toEnglish(tmp);
                sentence.push_back(tmp);
                sentence.push_back(strFind);
                flag = 1;
                continue;
            }
            if(flag == 1)
            {
                word = toEnglish(word);
                sentence.push_back(word);
                break;
            }
            if(word == "Shakespeare"&&line>42)
            {
                line = 0;
                continue;
            }
        }
        if(true == enter)
        {
            element.insert(make_pair(line,sentence));
        }
    }
    cout<<"occurrences:"<<element.size()<<endl;
    for(map<unsigned int, vector<string>>::const_iterator iter = element.begin();iter!=element.end();iter++)
    {
        cout<<"place:"<<iter->first<<" ";
        Show((iter->second).begin(),(iter->second).end());
        cout<<endl;
    }
    cout<<endl;

    return 0;
}