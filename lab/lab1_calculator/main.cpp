/*
   std_lib_facilities.h
*/

/*
	simple "Programming: Principles and Practice using C++ (second edition)" course header to
	be used for the first few weeks.
	It provides the most common standard headers (in the global namespace)
	and minimal exception/error support.

	Students: please don't try to understand the details of headers just yet.
	All will be explained. This header is primarily used so that you don't have
	to understand every concept all at once.

	By Chapter 10, you don't need this file and after Chapter 21, you'll understand it

	Revised April 25, 2010: simple_error() added

	Revised November 25 2013: remove support for pre-C++11 compilers, use C++11: <chrono>
	Revised November 28 2013: add a few container algorithms
	Revised June 8 2014: added #ifndef to workaround Microsoft C++11 weakness
*/

#ifndef H112
#define H112 251113L


#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<cmath>
#include<cstdlib>
#include<string>
#include<list>
#include <forward_list>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include <array>
#include <regex>
#include<random>
#include<stdexcept>

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------

typedef long Unicode;

//------------------------------------------------------------------------------

using namespace std;

template<class T> string to_string(const T& t)
{
    ostringstream os;
    os << t;
    return os.str();
}

struct Range_error : out_of_range {	// enhanced vector range error reporting
    int index;
    Range_error(int i) :out_of_range("Range error: "+to_string(i)), index(i) { }
};


// trivially range-checked vector (no iterator checking):
template< class T> struct Vector : public std::vector<T> {
    using size_type = typename std::vector<T>::size_type;

#ifdef _MSC_VER
    // microsoft doesn't yet support C++11 inheriting constructors
	Vector() { }
	explicit Vector(size_type n) :std::vector<T>(n) {}
	Vector(size_type n, const T& v) :std::vector<T>(n,v) {}
	template <class I>
	Vector(I first, I last) : std::vector<T>(first, last) {}
	Vector(initializer_list<T> list) : std::vector<T>(list) {}
#else
    using std::vector<T>::vector;	// inheriting constructor
#endif

    T& operator[](unsigned int i) // rather than return at(i);
    {
        if (i<0||this->size()<=i) throw Range_error(i);
        return std::vector<T>::operator[](i);
    }
    const T& operator[](unsigned int i) const
    {
        if (i<0||this->size()<=i) throw Range_error(i);
        return std::vector<T>::operator[](i);
    }
};

// disgusting macro hack to get a range checked vector:
#define vector Vector

// trivially range-checked string (no iterator checking):
struct String : std::string {
    using size_type = std::string::size_type;
//	using string::string;

    char& operator[](unsigned int i) // rather than return at(i);
    {
        if (i<0||size()<=i) throw Range_error(i);
        return std::string::operator[](i);
    }

    const char& operator[](unsigned int i) const
    {
        if (i<0||size()<=i) throw Range_error(i);
        return std::string::operator[](i);
    }
};


namespace std {

    template<> struct hash<String>
    {
        size_t operator()(const String& s) const
        {
            return hash<std::string>()(s);
        }
    };

} // of namespace std


struct Exit : runtime_error {
    Exit(): runtime_error("Exit") {}
};

// error() simply disguises throws:
inline void error(const string& s)
{
    fstream output("output.txt",ios::app);
    output << "error" << endl;
    output.close();
    throw runtime_error(s);
}

inline void error(const string& s, const string& s2)
{
    error(s+s2);
}

inline void error(const string& s, int i)
{
    ostringstream os;
    os << s <<": " << i;
    error(os.str());
}


template<class T> char* as_bytes(T& i)	// needed for binary I/O
{
    void* addr = &i;	// get the address of the first byte
    // of memory used to store the object
    return static_cast<char*>(addr); // treat that memory as bytes
}


inline void keep_window_open()
{
    cin.clear();
    cout << "Please enter a character to exit\n";
    char ch;
    cin >> ch;
    return;
}

inline void keep_window_open(string s)
{
    if (s=="") return;
    cin.clear();
    cin.ignore(120,'\n');
    for (;;) {
        cout << "Please enter " << s << " to exit\n";
        string ss;
        while (cin >> ss && ss!=s)
            cout << "Please enter " << s << " to exit\n";
        return;
    }
}



// error function to be used (only) until error() is introduced in Chapter 5:
inline void simple_error(string s)	// write ``error: s and exit program
{
    cerr << "error: " << s << '\n';
    keep_window_open();		// for some Windows environments
    exit(1);
}

// make std::min() and std::max() accessible on systems with antisocial macros:
#undef min
#undef max


// run-time checked narrowing cast (type conversion). See ???.
template<class R, class A> R narrow_cast(const A& a)
{
    R r = R(a);
    if (A(r)!=a) error(string("info loss"));
    return r;
}

// random number generators. See 24.7.



inline int randint(int min, int max) { static default_random_engine ran; return uniform_int_distribution<>{min, max}(ran); }

inline int randint(int max) { return randint(0, max); }

//inline double sqrt(int x) { return sqrt(double(x)); }	// to match C++0x

// container algorithms. See 21.9.

template<typename C>
using Value_type = typename C::value_type;

template<typename C>
using Iterator = typename C::iterator;

template<typename C>
// requires Container<C>()
void sort(C& c)
{
    std::sort(c.begin(), c.end());
}

template<typename C, typename Pred>
// requires Container<C>() && Binary_Predicate<Value_type<C>>()
void sort(C& c, Pred p)
{
    std::sort(c.begin(), c.end(), p);
}

template<typename C, typename Val>
// requires Container<C>() && Equality_comparable<C,Val>()
Iterator<C> find(C& c, Val v)
{
    return std::find(c.begin(), c.end(), v);
}

template<typename C, typename Pred>
// requires Container<C>() && Predicate<Pred,Value_type<C>>()
Iterator<C> find_if(C& c, Pred p)
{
    return std::find_if(c.begin(), c.end(), p);
}

#endif //H112


/*
 * 简单的计算器程序
 *
 * 本程序实现了一个简单的表达式计算器。
 * 从文件流input读入，输出到文件流output
 * 其中文本写在/Users/liujia/CLionProjects/517021911048/input.txt里，输出写在output.txt里
 * 输入文法如下：
 * Expression:
 *    Term
 *    Expression+Term
 *    Expression-Term
 * Term:
 *    Primary
 *    Term*Primary
 *    Term/Primary
 *    Term%Primary
 * Primary:
 *    Number
 *    (Expression)
 *    -Primary
 *    +Primary
 * Number:
 *    floating-point-literal
 *
 * 通过名为ts的单词流从input输入
 */

double expression();
double term();
double primary();
void clean_up_mess();
const char number = '8';
const char quit = 'q';
const char print = ';';
const char ans = 's';
const char name = 'a';
const char let = 'L';
const string declkey = "ANS";
double tmp=0;
ifstream input("/Users/liujia/CLionProjects/程序设计与数据结构习题/lab1_calculator/input.txt",ios::in);

/*
 * 单词类
 * 包括 类型、值、名字以及三个构造函数
 */
class Token{
public:
    char kind;
    double value;
    string name;
    Token(char ch):kind(ch),value(0){}
    Token(char ch,double val):kind(ch),value(val){}
    Token(char ch,string n):kind(ch),name(n){}
};
/*
 * 单词流类
 * 有获取、放回和忽略三个成员函数和一个构造函数，包括一个单词和一个标志
 * get获取文件流input里的一个单词
 * putback是将获取的token放回文件流input
 * ignore是忽略某一个字符
 */
class TokenStream{
public:
    Token get();
    void putback(Token t);
    void ignore(char c);
    TokenStream();
private:
    bool full;
    Token buffer;
};
TokenStream::TokenStream():full(false),buffer(0)
{

}
void TokenStream::ignore(char c)
{
    if(full && c == buffer.kind){
        full = false;
        return;
    }
    full = false;
    char ch = 0;
    while (input>>ch)
        if(ch==c) return;
}
void TokenStream::putback(Token t)
{
    if(full) error("putback() into a full buffer");
    buffer = t;
    full = true;
}
Token TokenStream::get()
{
    if(full){
        full = false;
        return buffer;
    }
    if(!input){cout << "error!";}
    char ch;
    input >> ch;
    if(ch !='\n') {
        switch (ch) {
            case quit:
            case print:
            case '(':
            case ')':
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
            case '!':
                return Token(ch);
            case '.':
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9': {
                input.putback(ch);
                double val;
                input >> val;
                return Token(number, val);
            }
            case '\0':
                error("next line");
            default:
                if (isalpha(ch)) {
                    string s;
                    s += ch;
                    while (input.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
                    input.putback(ch);
                    if (s == declkey) return Token(let);
                    return Token(name, s);
                }
                error("Bad token");//Bad token
                clean_up_mess();
        }
    }
}
TokenStream ts;

class Variable{
public:
    string name;
    double value;
    Variable(string n,double v):name{n},value{v}{}
};
vector<Variable> varTable;
/*
 * 文法部分
 */
double expression()
{
    double left = term();
    Token t = ts.get();

    while(true){
        switch(t.kind){
            case '+':
                left += term();
                t = ts.get();
                break;
            case '-':
                left -= term();
                t = ts.get();
                break;
            default:
                ts.putback(t);
                return left;
        }
    }
}

double term()
{
    double left = primary();
    Token t = ts.get();

    while(true){
        switch(t.kind){
            case '*':
                left *= primary();
                t = ts.get();
                break;
            case '/':
            {
                double d = primary();
                if(d==0) error("divided by zero");//divided by zero
                left /= d;
                t = ts.get();
                break;
            }
            case '%':
            {
                int i1 = narrow_cast<int>(left);
                int i2 = narrow_cast<int>(primary());
                if(i2==0) error("%:divided by zero");//%:divided by zero
                left = i1%i2;
                t = ts.get();
                break;
            }
            default:
                ts.putback(t);
                return left;
        }
    }
}
double primary()
{
    Token t = ts.get();
    switch(t.kind){
        case '(':
        {
            double d = expression();
            t = ts.get();
            if(t.kind!=')') {
                ts.putback(t);
                error("')' expected");
            }
            else if(t.kind==')'){
                Token tt = ts.get();
                while(tt.kind=='!'){
                    if(d!=int(d)||d<0){error("positive expected");tt = ts.get();break;}
                    else if(d==0){ d=1;tt = ts.get();}
                    else if(d==int(d)){
                        for(int i=abs(int(d))-1;i>1;i--){
                            d*=i;
                        }
                        tt = ts.get();
                    }
                }
                ts.putback(tt);
            }
            return d;
        }
        case '-':
            return - primary();
        case '+':
            return primary();
        case ans:{
            Token tt = ts.get();
            while (tt.kind == '!') {
                if (tmp < 0 || tmp != int(tmp)) {
                    error("negitive!");
                    tt = ts.get();
                    break;
                }
                else if (tmp == 0) {
                    tmp = 1;
                    tt = ts.get();
                }
                else if (tmp == int(tmp)) {
                    for (int i = abs(int(tmp)) - 1; i > 1; i--) {
                        tmp *= i;
                    }
                    tt = ts.get();
                }
            }
            ts.putback(tt);
            return tmp;
        }
        case let: {
            ts.putback(Token(ans, tmp));
            return primary();
        }
        default:
            error("primary expected");//primary expected
        case number: {
            Token tt = ts.get();
            while (tt.kind == '!') {
                if (t.value != int(t.value)) {
                    error("whole expected");
                    tt = ts.get();
                    break;
                }
                else if (t.value == 0) {
                    t.value = 1;
                    tt = ts.get();
                }
                else if (t.value == int(t.value)) {
                    for (int i = abs(int(t.value)) - 1; i > 1; i--) {
                        t.value *= i;
                    }
                    tt = ts.get();
                }
            }
            ts.putback(tt);
            return t.value;
        }

    }
}
/*
 * 细节处理部分
 */
bool isDeclared(string var)
{
    for(const Variable&v : varTable){
        if(v.name == var) return true;
    }
    return false;
}
double defineName(string var,double val)
{
    if(isDeclared(var)) error(var,"declared twice");
    varTable.push_back(Variable(var,val));
    return val;
}

void clean_up_mess()
{
    ts.ignore(print);
}
void calculate()
{
    ofstream output("output.txt",ios::trunc);
    output.close();
    if(!input){cout << "error!";}
    while (input.peek()!=EOF) {
        try {
            ofstream output("output.txt",ios::app);
            tmp = expression();
            Token t = ts.get();
            if(t.kind==print) {
                output << tmp << '\n';
            }
            else {
                while (t.kind!=print){t = ts.get();}
                output << "error" <<'\n';
            }
            output.close();
        }
        catch (exception &e) {
            if(e.what()!="next line") {
                cerr << e.what() << endl;
                clean_up_mess();
            }
        }
    }
    input.close();
}

int main() {
    try {
        defineName("pi",3.1415926535);
        defineName("e",2.7182818284);
        calculate();
        //keep_window_open();
        return 0;
    }
    catch(exception& e){
        cerr << e.what() << endl;
        keep_window_open("~~");
        return 1;
    }
    catch (...){
        cerr << "Oops: unknown exception!\n";
        keep_window_open("~~");
        return 2;
    }
}
