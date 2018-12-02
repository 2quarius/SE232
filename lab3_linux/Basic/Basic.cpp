/*
 * File: Basic.cpp
 * ---------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 * [TODO: extend and correct the documentation]
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"

#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
using namespace std;

/* Function prototypes */

void processLine(string line, Program & program, EvalState & state);

/* Main program */

int main() {
   EvalState state;
   Program program;
   while (true) {
      try {
         processLine(getLine(), program, state);

      }
      catch (ErrorException & ex) {
         if(ex.getMessage()!="") {
            cout << ex.getMessage() << endl;
         }
      }
   }
   return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */
/* Pseudo-code
 * ProcessLine:
    get next token from scanner
    if token type is NUMBER: (is a statement line)
        if there is more tokens after token: (is defining a statement)
            add source line to program
            parse statement (you need to create a function to help you to parse statement)
            set parsed statement into program
            end
        else: (a empty line)
            delete source line from program according to the line number
        end
    if token equals LIST:
        do list action
        end
    if token equals RUN:
        reset Evalstate's current line to the beginning of the program
        get current line number
        while current line number is valid:
            get statement from program according to line number
            if statement exists:
                execute statement
            get current line number
        end
    ...

    if token neither a NUMBER nor a keyword: (it is a statement should be execute immediately)
        if token equals invalid keywords: (some keywords can't exist in immediate execute statement)
            raise error
        else:
            put token back into scanner
            parse and execute the statement

 */
bool isNumber(const string &token)
{
   for(int i=0;i<token.size();i++)
   {
      char c=token[i];
      if(isdigit(c)) continue;
      else return false;
   }
   return true;
}
void processLine(string line, Program & program, EvalState & state) {
   TokenScanner scanner;
   scanner.ignoreWhitespace();
   scanner.scanNumbers();
   scanner.setInput(line);
   string token=scanner.nextToken();
   if(isNumber(token)){
      if(scanner.hasMoreTokens()){
         program.addSourceLine(stoi(token),line);
         Statement *stmt = parseStm(scanner,state);
         program.setParsedStatement(stoi(token),stmt);
      }
      else {
         program.removeSourceLine(stoi(token));
      }
   }
   else if(token=="LIST"){
      int first=program.getFirstLineNumber();
      if(first!=-1) {
          cout << program.getSourceLine(first)<<'\n';
          int next=program.getNextLineNumber(first);
          while(next!=-1)
          {
              cout <<program.getSourceLine(next)<<'\n';
              next = program.getNextLineNumber(next);
          }
      }
   }
   else if(token=="RUN"){
      state.setCurrentLine(program.getFirstLineNumber());
      int lineNumber=state.getCurrentLine();
      while(lineNumber!=-1){
         Statement *stmt=program.getParsedStatement(lineNumber);
         if(stmt!=NULL) {
            stmt->execute(state,program);
            lineNumber=state.getCurrentLine();
         }//change currentLine of state during execute
         else{
            int next = program.getNextLineNumber(lineNumber);
            state.setCurrentLine(next);
            lineNumber=state.getCurrentLine();
         }
      }
   }
   else if(token=="CLEAR"){ program.clear(); state.clear();}//clear both information in program and state
   else if(token=="QUIT"){ exit(0); }
   else if(token=="HELP"){cout << "no help hahaha..."<<'\n';}
   else{//immediately execute parts
      if(token=="REM"||token=="END"||token=="IF"||token=="GOTO"){//invalid command
         error("SYNTAX ERROR");
      }
      else {
         scanner.saveToken(token);
         Statement *stmt = parseStm(scanner,state);
         stmt->execute(state,program);
         delete stmt;
      }
   }

}
