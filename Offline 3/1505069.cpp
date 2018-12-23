#include<bits/stdc++.h>
using namespace std;
#define mx 1005

struct Point
{
    double x;
    double y;
    int id;
    void print()
    {
        cout<<id<<": ("<<x<<","<<y<<")"<<endl;
    }
    double dist(Point P)
    {
        return sqrt((x-P.x)*(x-P.x)+(y-P.y)*(y-P.y));

    }
    bool operator==(const Point& P)
    {
        return (x==P.x)&&(y==P.y)&&(id==P.id);
    }


};

Point point[mx];
int visited[mx];
vector<Point>tour;

int n;

void Clear()
{
    memset(visited,0,sizeof(visited));
    tour.clear();
}
double getTourCost()
{
    double cost=0.0;
    for(int i=0; i<tour.size()-1; i++)
    {
        cost+=tour[i].dist(tour[i+1]);
    }
    return cost;

}
void PrintSolution()
{

    cout<<"Total tour cost :"<<getTourCost()<<endl;
    for(int i=0; i<tour.size(); i++)
    {
        tour[i].print();
    }
    cout<<endl;


}
int getNearestNeighbor(Point p)
{

    int pos;
    double cost=LLONG_MAX;
    for(int i=1; i<=n; i++)
    {
        if(visited[i]==0)
        {
            double nowcost=p.dist(point[i]);
            if(nowcost<=cost)
            {
                cost=nowcost;
                pos=point[i].id;
            }
        }
    }
    return pos;
}

int getNearestNeighborFromAll()
{

    int pos;
    double cost=LLONG_MAX;
    for(int i=1; i<=n; i++)
    {
        if(visited[i]==1)
        {
            int curpos=getNearestNeighbor(point[i]);
            if(point[i].dist(point[curpos])<=cost)
            {
                cost=point[i].dist(point[curpos]);
                pos=curpos;
            }
        }
    }
    return pos;
}


int getNearestArc(int r)
{
    double cost=LLONG_MAX;
    int pos=-1;

    for(int edge=0; edge<tour.size(); edge++)
    {
        int i=tour[edge].id;
        int j=tour[(edge+1)%(tour.size())].id;
        double nowcost=point[i].dist(point[r])+point[j].dist(point[r])-point[i].dist(point[j]);
        if(nowcost<=cost)
        {
            cost=nowcost;
            pos=i;
        }
    }
    return pos;
}
void NearestNeighbor()
{
    Clear();
    int start=rand()%n+1;
    tour.push_back(point[start]);
    visited[start]=1;
    while(tour.size()<n)
    {
        int pos=getNearestNeighbor(tour.back());
        visited[pos]=1;
        tour.push_back(point[pos]);
    }
    tour.push_back(point[start]);
    PrintSolution();


}
void NearestInsertion()
{
    Clear();
    int start=rand()%n+1;
    tour.push_back(point[start]);
    visited[start]=1;
    int Next=getNearestNeighbor(point[start]);
    tour.push_back(point[Next]);
    visited[Next]=1;
    ///start sub tour with two nodes
    while(tour.size()<n)
    {

        int pos=getNearestNeighborFromAll();
        ///given sub-tour,find the nearest node from all nodes in the sub-tour
        // cout<<pos<<endl;
        visited[pos]=1;

        int id=getNearestArc(pos);
        ///find the position of the new node
        tour.push_back(point[pos]);
        for(int i=tour.size()-2; i>=0; i--)
        {
            ///positioning the new node
            if(tour[i]==point[id])
                break;
            swap(tour[i],tour[i+1]);

        }
    }
    tour.push_back(tour[0]);
      PrintSolution();


}
void solution()
{
    NearestNeighbor();
    NearestInsertion();


}

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt", "w", stdout);
    srand (time(NULL));

    cin>>n;
    for(int i=1; i<=n; i++)
    {
        cin>>point[i].x>>point[i].y;
        point[i].id=i;
    }
    cout.precision(5);
    solution();

}
