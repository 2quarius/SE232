/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "program.h"
#include "statement.h"
using namespace std;
Program::Program() {
   // Replace this stub with your own code
}

Program::~Program() {
   // Replace this stub with your own code
}

void Program::clear() {
    sourceLines.clear();
   // Replace this stub with your own code
}

void Program::addSourceLine(int lineNumber, string line) {
    if(sourceLines.count(lineNumber)==1){
        auto it = sourceLines.find(lineNumber);
        it->second.first = line;
        if(it->second.second) {
            delete it->second.second;
            it->second.second=NULL;
        }
    }
    else{
        Statement *p=NULL;
        sourceLines.insert(make_pair(lineNumber,make_pair(line,p)));
    }
    /*process 'line' to a pointer of Statement*/
   // Replace this stub with your own code
}

void Program::removeSourceLine(int lineNumber) {
    if(sourceLines.count(lineNumber)==1){
        auto it=sourceLines.find(lineNumber);
        if(it->second.second) delete it->second.second;
        sourceLines.erase(lineNumber);
    }
    else return;
   // Replace this stub with your own code
}

string Program::getSourceLine(int lineNumber) {
    if(sourceLines.count(lineNumber)==1){
        auto it=sourceLines.find(lineNumber);
        return it->second.first;
    }
    else
        return "";    // Replace this stub with your own code
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
    if(sourceLines.count(lineNumber)==1){
        auto it = sourceLines.find(lineNumber);
        if(it->second.second) delete it->second.second;
        it->second.second=stmt;
    }
    else error("no such line");
   // Replace this stub with your own code
}

Statement *Program::getParsedStatement(int lineNumber) {
    if(sourceLines.count(lineNumber)==1){
        auto it=sourceLines.find(lineNumber);
        return it->second.second;
    }
    else
        return NULL;
    // Replace this stub with your own code
}

int Program::getFirstLineNumber() {
    if(!sourceLines.empty()){
        auto it=sourceLines.begin();
        return it->first;
    }
    else
        return -1;
    // Replace this stub with your own code
}

int Program::getNextLineNumber(int lineNumber) {
    for(auto it=sourceLines.find(lineNumber);it!=sourceLines.end();it++)
    {
        if(it->first>lineNumber){ return it->first;}
    }
    return -1;     // Replace this stub with your own code
}
bool Program::isValid(int lineNumber) {
    if(sourceLines.count(lineNumber)) return true;
    else return false;
}