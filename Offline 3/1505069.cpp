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

double table[mx][mx];
int par[mx];

vector<pair<double, pair<int,int> > > edge;

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




void NearestNeighbor(bool print)
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
    if(print)
    {
        cout<<"Solution by nearest neighbor heuristic:"<<endl;
        PrintSolution();
    }


}

void compute_table()
{
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            if(i==j)
            {
                table[i][j]=INT_MAX;
                continue;

            }
            table[i][j]=point[i].dist(point[j]);
        }
    }
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            //  cout<<table[i][j]<<" ";
        }
        //cout<<endl;
    }

}
void compute_edge(int start)
{
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            if(i==j || i==start || j==start)
            {
                continue;
            }
            double cost=table[i][start]+table[j][start]-table[i][j];
            edge.push_back(make_pair(cost,make_pair(i,j)));

        }
    }
    sort(edge.rbegin(),edge.rend());
    for(int i=0; i<edge.size(); i++)
    {
        //cout<<edge[i].first<<" "<<edge[i].second.first<<" "<<edge[i].second.second<<endl;
    }

}
int compute_next(int now)
{
//cout<<now<<endl;
    for(int i=0; i<edge.size(); i++)
    {
        //cout<<now<<" "<<edge[i].second.first<<" "<<edge[i].second.second<<endl;


        if(edge[i].second.first==now and !visited[edge[i].second.second])
        {
            return edge[i].second.second;

        }
        else if(edge[i].second.second==now and !visited[edge[i].second.first])
            return edge[i].second.first;

    }

}

void Saving(int print=1)
{
    compute_table();
    Clear();


    int start=rand()%n+1;
    visited[start]=1;
    par[start]=-1;
    compute_edge(start);
    int nodes=3;
    int x=edge[0].second.first;
    int y=edge[0].second.second;
    par[x]=y;
    par[y]=start;
    visited[x]=1;
    visited[y]=1;
    int last=x;
    while(nodes<n)
    {
        // cout<<x<<" "<<y<<endl;
        int x1=compute_next(x);
        visited[x1]=1;
        par[x1]=x;
        last=x1;
        int y1=compute_next(y);
        par[y]=y1;
        par[y1]=start;
        visited[y1]=1;
        nodes++;
        if(nodes==n)
        {

            break;
        }
        nodes++;
        x=x1;
        y=y1;



    }
    int p=last;
    while(p!=-1)
    {
        if(p!=0)
            tour.push_back(point[p]);
        p=par[p];
    }
    tour.push_back(tour[0]);

    if(print)
    {
        cout<<"Solution by saving heuristic:"<<endl;
        PrintSolution();
    }
}


void TwoOpt()
{
    Clear();

    NearestNeighbor(1);
    while(true)
    {
        double cost=getTourCost();
        bool isChanged=false;

        for(int i=0; i<tour.size()-1; i++)
        {
            for(int j=i+2; j<tour.size()-1; j++)
            {
                ///reverse from i+1 to k-1;
                reverse(tour.begin()+i+1,tour.begin()+j-1);
                double nowcost=getTourCost();
                if(nowcost<cost)
                {
                    isChanged=true;
                    break;
                }
                ///reverse again to fix the change
                reverse(tour.begin()+i+1,tour.begin()+j-1);
            }
            if(isChanged)
                break;
        }
        if(!isChanged)
            break;
    }
    cout<<"Improved solution by 2-opt heuristic:"<<endl;
    PrintSolution();
}



void solution()
{
    NearestNeighbor(1);
    Saving();
    TwoOpt();



}

int main()
{
    freopen("burma14.tsp","r",stdin);
    freopen("outputburma.txt", "w", stdout);
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
