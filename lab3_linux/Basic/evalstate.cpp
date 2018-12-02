/*
 * File: evalstate.cpp
 * -------------------
 * This file implements the EvalState class, which defines a symbol
 * table for keeping track of the value of identifiers.  The public
 * methods are simple enough that they need no individual documentation.
 */

#include <string>
#include "evalstate.h"

#include "../StanfordCPPLib/map.h"
using namespace std;

/* Implementation of the EvalState class */

EvalState::EvalState() {
   /* Empty */
}

EvalState::~EvalState() {
   /* Empty */
}

void EvalState::setValue(string var, int value) {
   if(var=="REM"||var=="LET"||var=="PRINT"||var=="INPUT"||var=="END"||var=="GOTO"||var=="IF"||var=="THEN"||
           var=="RUN"||var=="LIST"||var=="CLEAR"||var=="QUIT"||var=="HELP") error("SYNTAX ERROR");
   else
      symbolTable.put(var, value);
}

int EvalState::getValue(string var) {
   return symbolTable.get(var);
}

bool EvalState::isDefined(string var) {
   return symbolTable.containsKey(var);
}
int EvalState::getCurrentLine() {
   return currentLine;
}
void EvalState::setCurrentLine(int lineNumber) {
   currentLine=lineNumber;
}
void EvalState::clear() {
   symbolTable.clear();
   currentLine=-1;
}