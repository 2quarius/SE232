/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface specified in Chapter 17, which is an
 * excellent model for the Statement class hierarchy.
 */

#ifndef _statement_h
#define _statement_h

#include "evalstate.h"
#include "exp.h"
#include "program.h"
#include <vector>
class Program;
/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */
class Statement {

public:

/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

   Statement();

/*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

   virtual ~Statement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */

   virtual void execute(EvalState & state,Program &program) = 0;

};

/*
 * The remainder of this file must consists of subclass
 * definitions for the individual statement forms.  Each of
 * those subclasses must define a constructor that parses a
 * statement from a scanner and a method called execute,
 * which executes that statement.  If the private data for
 * a subclass includes data allocated on the heap (such as
 * an Expression object), the class implementation must also
 * specify its own destructor method to free that memory.
 */

/*
 * Class: LetStatement
 * -------------------
 * This subclass is used to represent a Statement beginned with "LET".
 */
class LetStatement:public Statement{

public:

/*
 * Constructor: LetStatement
 * Usage: Statement *stmt = new LetStatement((Compound *)exp);
 * -----------------------------------------------------------
 * This constructor initializes a new LET statement which is composed
 * of a compound expression pointer.
 */

    LetStatement(CompoundExp *exp);

/*
 * Prototypes for the virtual methods
 * ----------------------------------
 * These methods have the same prototypes as those in the Statement
 * base class and don't require additional documentation.
 */

    ~LetStatement();
    virtual void execute(EvalState & state,Program &program);

private:
    CompoundExp *exprssion;

};

/*
 * Class: PrintStatement
 * -------------------
 * This subclass is used to represent a Statement beginned with "PRINT".
 */

class PrintStatement:public Statement{

public:

/*
 * Constructor: PrintStatement
 * Usage: Statement *stmt = new PrintStatement(Expression *exp);
 * -------------------------------------------------------------
 * This constructor initializes a new PRINT statement which is composed
 * of an implicit expression pointer.
 */

    PrintStatement(Expression *exp);

/*
 * Prototypes for the virtual methods
 * ----------------------------------
 * These methods have the same prototypes as those in the Statement
 * base class and don't require additional documentation.
 */

    ~PrintStatement();
    virtual void execute(EvalState & state,Program &program);

private:
    Expression *expression;
};

/*
 * Class: InputStatement
 * -------------------
 * This subclass is used to represent a Statement beginned with "INPUT".
 */

class InputStatement:public Statement{

public:

/*
 * Constructor: InputStatement
 * Usage: Statement *stmt = new InputStatement(IdentifierExp *exp);
 * ----------------------------------------------------------------
 * This constructor initializes a new INPUT statement which is composed
 * of an identifier expression pointer.
 */

    InputStatement(IdentifierExp *exp);

/*
 * Prototypes for the virtual methods
 * ----------------------------------
 * These methods have the same prototypes as those in the Statement
 * base class and don't require additional documentation.
 */

    ~InputStatement();
    virtual void execute(EvalState & state,Program &program);

private:
    IdentifierExp *expression;
};

/*
 * Class: GotoStatement
 * -------------------
 * This subclass is used to represent a Statement beginned with "GOTO".
 */

class GotoStatement:public Statement{

public:

/*
 * Constructor: GotoStatement
 * Usage: Statement *stmt = new GotoStatement(Expression *exp);
 * ----------------------------------------------------------------
 * This constructor initializes a new INPUT statement which is composed
 * of an implicit expression pointer.
 */

    GotoStatement(Expression *exp);

/*
 * Prototypes for the virtual methods
 * ----------------------------------
 * These methods have the same prototypes as those in the Statement
 * base class and don't require additional documentation.
 */

    ~GotoStatement();
    virtual void execute(EvalState & state,Program &program);

private:
    Expression *whichLine;
};

/*
 * Class: IfStatement
 * -------------------
 * This subclass is used to represent a Statement beginned with "IF".
 */

class IfStatement:public Statement{

public:

/*
 * Constructor: IfStatement
 * Usage: Statement *stmt = new IfStatement(Expression *lexp,Expression *rexp,string operand,Expression *exp);
 * -----------------------------------------------------------------------------------------------------------
 * This constructor initializes a new INPUT statement which is composed
 * of a condition part including lexp(left expression), operand and
 * rexp(right expression) and a control part including an implicit
 * expression pointer.
 */

    IfStatement(Expression *lexp,Expression *rexp,string operand,Expression *exp);

/*
 * Prototypes for the virtual methods
 * ----------------------------------
 * These methods have the same prototypes as those in the Statement
 * base class and don't require additional documentation.
 */

    ~IfStatement();
    virtual void execute(EvalState & state,Program &program);

private:
    Expression *lexpression;
    Expression *rexpression;
    string op;
    Expression *gotoLine;
};

/*
 * Class: EndStatement
 * -------------------
 * This subclass is used to represent a Statement beginned with "END".
 */

class EndStatement:public Statement{

public:

/*
 * Constructor: EndStatement
 * Usage: Statement *stmt = new EndStatement();
 * --------------------------------------------
 * This constructor initializes a new END statement which is empty.
 */

    EndStatement();

/*
 * Prototypes for the virtual methods
 * ----------------------------------
 * These methods have the same prototypes as those in the Statement
 * base class and don't require additional documentation.
 */

    virtual void execute(EvalState &state,Program &program);
};
#endif
