#include <iostream>
#include <math.h>
#include <string.h>
#include <algorithm>
#include <fstream>
#define N 30
#define par pair<double,double>
#define Fabs(x) ((x)>0?(x):-(x))
using namespace std;
const double pi = acos(-1.0);
const double EPS = 1e-10;
const double INF = 1e100;
class Point{
public:
    double x,y;
    friend double distance(Point a,Point b)
    {
        return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
    }
};
class Circle
{
public:
    Point p;
    double r;
    friend bool operator<(Circle a,Circle b)
    {
        if(a.p.x-a.r<b.p.x-a.r){
            return a.p.x+a.r<b.p.x-a.r;
        }
        return a.p.x-a.r<b.p.x-a.r;
    }
    par f(double x)
    {
        if(r<fabs(p.x-x)) return par(0,0);
        double t=r*r-(p.x-x)*(p.x-x);
        t = sqrt(t);
        return par(p.y-t,p.y+t);
    }
};
Circle O[N];
bool ban[N];
par p[N];
int n=25;
double Cut(double x)
{
    double ret=0,last = -INF;
    int cnt=0;
    for(int i=1;i<=n;i++)
    {
        p[++cnt] = O[i].f(x);
        if(p[cnt]==par(0,0))
            cnt--;
    }
    sort(p+1,p+cnt+1);
    for(int i=1;i<=cnt;i++)
    {
        if(p[i].first>last){
            ret+=p[i].second-p[i].first,last=p[i].second;
        }
        else if(p[i].second>last){
            ret+=p[i].second-last,last=p[i].second;
        }
    }
    return ret;
}
double Simpson(double l,double r,double mid,double Cl,double Cr,double Cm)
{
    double tCl = Cut((l+mid)/2),tCr=Cut((mid+r)/2);
    double ans = (r-l)*(Cl+Cr+4*Cm)/6,lans=(mid-l)*(Cl+Cm+4*tCl)/6,rans=(r-mid)*(Cr+Cm+4*Cr)/6;
    if(Fabs(lans+rans-ans)<EPS)
        return ans;
    else
        return Simpson(l,mid,(l+mid)/2,Cl,Cm,tCl)+Simpson(mid,r,(mid+r)/2,Cm,Cr,tCr);
}
int main() {

    double l=INF,r=-INF;
    clock_t b,e;
    b = clock();
    ifstream input;
    input.open("circles.txt",ios::in);
    for(int i=1;i<=n;i++)
    {
        input >> O[i].p.x >> O[i].p.y >>O[i].r;
        l=min(l,O[i].p.x-O[i].r);
        r=max(r,O[i].p.x+O[i].r);
    }
    sort(O+1,O+n+1);
    for(int i=1;i<=n;i++)
    {
        if(ban[i]) continue;
        for(int j=i+1;j<=n;j++)
        {
            if(distance(O[i].p,O[j].p)+O[j].r<=O[i].r)
                ban[j]=true;
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(ban[i])
        {
            swap(ban[i],ban[n]);
            swap(O[i--],O[n--]);
        }
    }
    cout << Simpson(l,r,(l+r)/2,0,0,Cut((l+r)/2))<<'\n';
    e=clock();
    cout <<double(e-b)/CLOCKS_PER_SEC;

    return 0;
}