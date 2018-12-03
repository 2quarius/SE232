#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <set>
//------------------------------------------------------------------------------
using namespace std;

//------------------------------------------------------------------------------
struct node
{
    int val;
    vector<node*> neighbors;
    node(int i):val(i){}
    node(){}
};
//------------------------------------------------------------------------------
class Solver
{
private:
    //member variables
    vector<vector<node>> katayose;
    node *start,*dest;
    set<int> targets;
    //member functions
    void parseNode(const vector<string> & puzz,int max_wid)
    {
        for(int i = 0; i<puzz.size();i+=max_wid)
        {
            vector<node> ryota;
            for(int j = 0; j<max_wid;j++)
            {
                if(puzz[i+j]=="."){
                    ryota.emplace_back(-1);
                }
                else if(puzz[i+j]=="*"){
                    ryota.emplace_back(-2);
                }
                else{
                    ryota.emplace_back(stoi(puzz[i+j].c_str()));
                    targets.insert(stoi(puzz[i+j].c_str()));
                }
            }
            katayose.push_back(ryota);
        }
        vector<pair<int,int>> direction;
        direction.emplace_back(-1,-1);
        direction.emplace_back(-1,0);
        direction.emplace_back(-1,1);
        direction.emplace_back(0,-1);
        direction.emplace_back(0,1);
        direction.emplace_back(1,-1);
        direction.emplace_back(1,0);
        direction.emplace_back(1,1);
        dest=new node(-2);
        start=new node(INT_MAX);
        for(int i = 0; i<katayose.size();i++)
        {
            for(int j = 0; j < katayose[i].size(); j++)
            {
                for(int k = 0; k<direction.size();k++)
                {
                    int x=i+direction[k].first,y=j+direction[k].second;
                    if(x>=0&&x<katayose.size()&&y>=0&&y<katayose[i].size()&&katayose[x][y].val!=-2){
                        katayose[i][j].neighbors.emplace_back(&katayose[x][y]);
                    }
                }
                if(katayose[i][j].val>dest->val){dest=&katayose[i][j];}
                if(katayose[i][j].val>0&&katayose[i][j].val<start->val){start=&katayose[i][j];}
            }
        }
    }
    bool find()
    {
        if(start->val==dest->val) { return true;}
        else {
            int next=start->val+1;
            if(targets.count(next)==1){
                for(int i = 0; i<start->neighbors.size();i++)
                {
                    if(start->neighbors[i]->val==next){
                        start=start->neighbors[i];
                        return find();
                    }
                }
                return false;
            }
            else {
                for(int i = 0;i<start->neighbors.size();i++)
                {
                    node *tmp=start;
                    if(start->neighbors[i]->val==-1){
                        start=start->neighbors[i];
                        start->val=next;
                        bool flag = find();
                        if(flag) { return true;}
                        else {
                            start=tmp;
                            start->neighbors[i]->val=-1;
                        }
                    }
                }
                return false;
            }
        }
    }
public:
    //constructors & deconstructors
    Solver()
    {
    }

    //member functions
    bool solve( vector<string>& puzz, int max_wid )
    {
        parseNode(puzz,max_wid);
        bool flag=find();
        if(flag) {
            for(int i = 0; i<katayose.size();i++)
            {
                for(int j = 0;j<katayose[i].size();j++)
                {
                    if(katayose[i][j].val>0){puzz[i*max_wid+j]=to_string(katayose[i][j].val);}
                }
            }
            return true;
        }
        return false;
    }
};

struct puzzle
{
    int width;
    vector<string> data;
};

void printPuzzle(puzzle p)
{
    int c = 0;
    for( vector<string>::iterator i = p.data.begin(); i != p.data.end(); i++ )
    {
        if( ( *i ) != "*" && ( *i ) != "." )
        {
            if( atoi( ( *i ).c_str() ) < 10 ) cout << "0";
            cout << ( *i ) << " ";
        }
        else
            cout << "   ";
        if( ++c >= p.width )
        {
            cout << endl; c = 0;
        }
    }
    cout << endl << endl;

}
//------------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
    struct puzzle puzzles[3];

    istringstream iss1( "32 . . . 37 * * * . 34 . . 38 * * * . 25 . . 12 . * * 29 . 20 . 40 . * * . 28 . 19 . 10 1 * * * 15 . . . . * * * * * . . . 3 * * * * * * . 4" );
    copy( istream_iterator<string>( iss1 ), istream_iterator<string>(), back_inserter<vector<string> >( puzzles[0].data ) );
    puzzles[0].width = 8;

    istringstream iss2(". 53 . 59 . 67 66 . . 52 . . 57 . . 68 72 . . . 56 . 64 * * * * 49 . . . * * 17 . * . 10 . * . 16 . . 22 . 46 . * . 2 . . 24 . 44 . . 4 1 . . 25 . . 7 6 . 34 . . 31 42 40 . . . . . 29 .");
    copy( istream_iterator<string>( iss2 ), istream_iterator<string>(), back_inserter<vector<string> >( puzzles[1].data ) );
    puzzles[1].width = 9;

    istringstream iss3("56 . . . . 62 . . 67 . 55 . 53 . . 65 . . 9 . 52 . . 48 . . 69 . 6 . * * * 47 . . 5 . . * * * 72 . 42 . . 13 * * * . . 41 . 3 . 18 . . 38 . . 2 . . 22 23 . . . 32 1 20 . . 25 . 35 . .");
    copy( istream_iterator<string>( iss3 ), istream_iterator<string>(), back_inserter<vector<string> >( puzzles[2].data ) );
    puzzles[2].width = 9;
    \
    int puzzleIndex = 0;

    if(argc > 1)
    {
        puzzleIndex = atoi(argv[1]);
    }

    cout<<"The original puzzle:"<<endl;

    printPuzzle(puzzles[puzzleIndex]);

    Solver s;
    bool bFound = s.solve( puzzles[puzzleIndex].data, puzzles[puzzleIndex].width );

    if(bFound)
    {
        cout<<"The answer: "<<endl;
        printPuzzle(puzzles[puzzleIndex]);
    }
    else
    {
        cout<<"No answer."<<endl;
    }

    return 1;
}
