/*
 * tips: store operations in vector and use for loop (caution: you have forgotten it for once!)
 */
#include <iostream>
#include <string>
#include <random>
#include <stack>
#include <map>
#include <queue>

#define DENSITY 5

#define RED "\033[41m"
#define GREEN "\033[42m"
#define YELLOW "\033[43m"
#define BLUE "\033[44m"
#define PURPLE "\033[45m"
#define AZURE "\033[46m"
#define WHITE "\033[47m"

using namespace std;
void print(vector<vector<int>> maze);
class Point
{
  public:
    int X;
    int Y;

    Point()
    {
    }

    Point(int x, int y)
    {
        X = x;
        Y = y;
    }

    Point &operator=(const Point &point)
    {
        if (this == &point)
        {
            return *this;
        }

        X = point.X;
        Y = point.Y;

        return *this;
    }

    bool operator==(const Point &point) const
    {
        if (X == point.X && Y == point.Y)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator!=(const Point &point) const
    {
        return (X != point.X || Y != point.Y);
    }
};
bool solve(vector<vector<int>> &maze, Point start, Point end)
{
    vector<vector<Point>> info;//one position([i][j]) store its pre point
    //initial info, which means every point has no pre point
    for(int i=0;i<maze.size();i++)
    {
        vector<Point> tmpV;
        for(int j=0;j<maze[0].size();j++)
        {
            tmpV.push_back(Point(-1,-1));
        }
        info.push_back(tmpV);
    }
    queue<vector<Point> > solution;//every vector stores two points
    info[start.Y][start.X] = Point(-2,-2);//let start-point's pre be another default value
    vector<Point> tmp;//just for immediate use, to make solution not empty
    tmp.push_back(start);
    solution.push(tmp);
    //store operations on point 'next' into vector
    vector<vector<int>> operation;
    for(int i=-1;i<2;i++)
    {
        for(int j=-1;j<2;j++)
        {
            vector<int> pos;
            if(i==0&&j==0) continue;
            pos.push_back(i);
            pos.push_back(j);
            operation.push_back(pos);
        }
    }
    while(!solution.empty())
    {
        vector<Point> pointsTmp;
        pointsTmp.push_back(solution.front()[solution.front().size()-1]);
        if(solution.back()[0]==end)
        {
            return true;
        }
        for(int i=0;i<operation.size();i++)
        {
            Point next = pointsTmp[0];
            next.X+=operation[i][0];
            next.Y+=operation[i][1];
            if(next.X>0&&next.X<maze.size()&&next.Y>0&&next.Y<maze[0].size()&&maze[next.Y][next.X]==1)
            {
                if(info[next.Y][next.X]==Point(-1,-1))
                {
                    pointsTmp.push_back(next);
                    solution.push(pointsTmp);
                    maze[next.Y][next.X]=2;
                    pointsTmp.clear();
                    pointsTmp.push_back(solution.front()[solution.front().size()-1]);
                    info[next.Y][next.X] = pointsTmp[0];//record last point
                }
            }
        }
        solution.pop();
    }
    //return false;
}

vector<vector<int>> generate(int width, int height)
{
    mt19937 rng;
    rng.seed(random_device()());

    default_random_engine fixed;
    uniform_int_distribution<int> distribution(0, 9);

    vector<vector<int>> maze(height, vector<int>(width));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            maze[i][j] = distribution(rng) < DENSITY ? 1 : 0;
        }
    }

    return maze;
}

void print(vector<vector<int>> maze)
{
    for (int i = 0; i < maze.size(); i++)
    {
        for (int j = 0; j < maze[0].size(); j++)
        {
            switch (maze[i][j])
            {
            case 0:
                // wall
                cout << YELLOW << "  "
                     << "\033[0m";
                break;
            case 1:
                // road
                cout << GREEN << "  "
                     << "\033[0m";
                break;
            case 2:
                // route
                cout << RED << "  "
                     << "\033[0m";
                break;
            case 3:
                // wrong
                cout << WHITE << "  "
                     << "\033[0m";
                break;
            case 5:
                // start and end
                cout << PURPLE << "  "
                     << "\033[0m";
                break;
            }
        }

        cout << endl;
    }
}

int main()
{
    int width;
    int height;
    Point start(0,0), end(height/2,width/2);

    cout << "Please input the width:";
    cin >> width;
    cout << "Please input the height:";
    cin >> height;

    mt19937 rng;
    rng.seed(random_device()());

    uniform_int_distribution<int> distribution(0, 9);

    vector<vector<int>> maze = generate(width, height);

    //print(maze);
    while(maze[start.Y][start.X]==0)
    {
        cout << "Please input the start point:";
        cin >> start.X >> start.Y;

    }
    while(maze[end.Y][end.X]==0)
    {
        cout << "Please input the end point:";
        cin >> end.X >> end.Y;
    }


    time_t begin,ending;
    begin = clock();

    if (!solve(maze, start, end))
        cout << "No answer." << endl;
    ending = clock();
    cout << "Time consumption:"<< double(ending-begin)/CLOCKS_PER_SEC;
    //print(maze);

    return 0;
}