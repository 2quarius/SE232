/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"
#include "parser.h"
#include "../StanfordCPPLib/tokenscanner.h"
#include "../StanfordCPPLib/simpio.h"

using namespace std;
/* Implementation of the Statement class */

Statement::Statement() {
   /* Empty */
}

Statement::~Statement() {
   /* Empty */
}

/*
 * Implementation notes: the LetStatement subclass
 * ------------------------------------------------
 * The LetStatement subclass declares a statement that stores the
 * expression following it. The implementation of execute must
 * look for information up in the evaluation state and generate
 * state's current line according to program
 */

LetStatement::LetStatement(CompoundExp *exp) {
    exprssion = exp;
}
LetStatement::~LetStatement() {
    delete exprssion;
}
void LetStatement::execute(EvalState & state,Program &program) {
    if (exprssion->getOp() == "=") {
        if (exprssion->getLHS()->getType() != IDENTIFIER) {
            error("SYNTAX ERROR");
        }
        int val = exprssion->getRHS()->eval(state);
        state.setValue(((IdentifierExp *) exprssion->getLHS())->getName(), val);
    }
    else error("SYNTAX ERROR");
    int next=program.getNextLineNumber(state.getCurrentLine());
    state.setCurrentLine(next);
}

/*
 * Implementation notes: the PrintStatement subclass
 * ------------------------------------------------
 * The PrintStatement subclass declares a statement that stores the
 * expression following it. The implementation of execute must
 * look for information up in the evaluation state and generate
 * state's current line according to program
 */

PrintStatement::PrintStatement(Expression *exp) {
    expression = exp;
}
PrintStatement::~PrintStatement() {
    delete expression;
}
void PrintStatement::execute(EvalState &state,Program &program) {
    cout << expression->eval(state) <<'\n';
    int next=program.getNextLineNumber(state.getCurrentLine());
    state.setCurrentLine(next);
}

/*
 * Implementation notes: the InputStatement subclass
 * ------------------------------------------------
 * The InputStatement subclass declares a statement that stores the
 * expression following it. The implementation of execute must
 * look for information up in the evaluation state and generate
 * state's current line according to program
 */

InputStatement::InputStatement(IdentifierExp *exp) {
    expression = exp;
}
InputStatement::~InputStatement() {
    delete expression;
}
void InputStatement::execute(EvalState &state,Program &program) {
    cout << " ? ";
    string input=getLine();
    bool isNotValid=true;
    while(isNotValid){
        int cnt=0;
        for(int i=0;i<input.size();i++){
            char c=input[i];
            if(isdigit(c)||input[0]=='-') cnt++;
            else break;
        }
        if(cnt==input.size()){isNotValid= false;}
        else {
            cout << "INVALID NUMBER"<<'\n'<<" ? ";
            input = getLine();
        }
    }
    state.setValue(expression->getName(),stoi(input));
    int next=program.getNextLineNumber(state.getCurrentLine());
    state.setCurrentLine(next);
}

/*
 * Implementation notes: the GotoStatement subclass
 * ------------------------------------------------
 * The GotoStatement subclass declares a statement that stores the
 * expression following it. The implementation of execute must
 * look for information up in the evaluation state and generate
 * state's current line according to the value of that expression
 */

GotoStatement::GotoStatement(Expression *exp) {
    whichLine=exp;
}
GotoStatement::~GotoStatement() {
    delete whichLine;
}
void GotoStatement::execute(EvalState &state,Program &program) {
    int val=whichLine->eval(state);
    if(!program.isValid(val)) error("LINE NUMBER ERROR");
    else
        state.setCurrentLine(val);
}

/*
 * Implementation notes: the IfStatement subclass
 * ------------------------------------------------
 * The IfStatement subclass declares a statement that stores the
 * two expressions following it. The implementation of execute must
 * look for information up in the evaluation state and generate
 * state's current line according to the value of last expression and
 * conditional statement
 */

IfStatement::IfStatement(Expression *lexp, Expression *rexp,string operand,Expression *exp) {
    lexpression=lexp;
    rexpression=rexp;
    op = operand;
    gotoLine = exp;
}
IfStatement::~IfStatement() {
    delete lexpression;
    delete rexpression;
    delete gotoLine;
}
void IfStatement::execute(EvalState &state, Program &program) {
        int left = lexpression->eval(state);
        int right = rexpression->eval(state);
        if (op == ">") {
            if (left > right) { state.setCurrentLine(gotoLine->eval(state)); }
            else {
                int next = program.getNextLineNumber(state.getCurrentLine());
                state.setCurrentLine(next);
            }
        }
        else if (op== "<") {
            if (left < right) { state.setCurrentLine(gotoLine->eval(state)); }
            else {
                int next = program.getNextLineNumber(state.getCurrentLine());
                state.setCurrentLine(next);
            }
        }
        else if (op== "=") {
            if (left == right) { state.setCurrentLine(gotoLine->eval(state)); }
            else {
                int next = program.getNextLineNumber(state.getCurrentLine());
                state.setCurrentLine(next);
            }
        }
        else error("SYNTAX ERROR");
}

/*
 * Implementation notes: the EndStatement subclass
 * ------------------------------------------------
 * The EndStatement subclass declares a statement that is empty.
 * The implementation of execute just throw an empty string error
 * to end the program. Though it has passed the trace, I think this
 * implementation should add state.clear(); and program.clear();
 */

EndStatement::EndStatement() {}
void EndStatement::execute(EvalState &state, Program &program) {
    error("");
}