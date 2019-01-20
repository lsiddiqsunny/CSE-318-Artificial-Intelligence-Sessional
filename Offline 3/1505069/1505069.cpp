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
    memset(par,0,sizeof(par));
    //memset(table,0,sizeof(table));
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

double getTourCost(vector<Point>v)
{
    double cost=0.0;
    for(int i=0; i<v.size()-1; i++)
    {
        cost+=v[i].dist(v[i+1]);
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



int RgetNearestNeighbor(Point p)
{

    int pos;
    double cost=LLONG_MAX;
    vector<pair<double,int> >costs;
    for(int i=1; i<=n; i++)
    {
        if(visited[i]==0)
        {
            double nowcost=p.dist(point[i]);
            costs.push_back({nowcost,i});
            if(nowcost<=cost)
            {
                cost=nowcost;
                pos=point[i].id;
            }
        }
    }
    sort(costs.begin(),costs.end());
    int x=rand()%(int)min((int)costs.size(),5);

    return costs[x].second;
}




void RNearestNeighbor(bool print)
{
    Clear();
    int start=rand()%n+1;
    tour.push_back(point[start]);
    visited[start]=1;
    while(tour.size()<n)
    {
        int pos=RgetNearestNeighbor(tour.back());
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
    return -1;

}

void Saving(int print=1)
{
    compute_table();

    Clear();
    for(int i=1; i<=n; i++)
    {
        par[i]=-1;
    }


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

        int x1=compute_next(x);
        visited[x1]=1;
        par[x1]=x;
        last=x1;

        nodes++;
//cout<<nodes<<endl;
        if(nodes==n)
        {

            break;
        }
        nodes++;
        int y1=compute_next(y); //cout<<y1<<endl;
        par[y]=y1;
        par[y1]=start;
        visited[y1]=1;
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







int Rcompute_next(int now)
{
//cout<<now<<endl;
    vector<int>pos;
    for(int i=0; i<edge.size(); i++)
    {
        //cout<<now<<" "<<edge[i].second.first<<" "<<edge[i].second.second<<endl;


        if(edge[i].second.first==now and !visited[edge[i].second.second])
        {
            pos.push_back(i);
            // return edge[i].second.second;
            if(pos.size()>=5)
            {
                break;
            }

        }
        else if(edge[i].second.second==now and !visited[edge[i].second.first])
            pos.push_back(i);
        if(pos.size()>=5)
        {
            break;
        }

    }

    if(pos.size()==0)
        return -1;
    int x=rand()%(int)min(5,(int)pos.size());
    if(edge[pos[x]].second.first==now)
    {
        return edge[pos[x]].second.second;
    }
    else
    {
        return edge[pos[x]].second.first;
    }

}

void RSaving(int print=1)
{
    compute_table();

    Clear();
    for(int i=1; i<=n; i++)
    {
        par[i]=-1;
    }


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

        int x1=compute_next(x);
        visited[x1]=1;
        par[x1]=x;
        last=x1;

        nodes++;
//cout<<nodes<<endl;
        if(nodes==n)
        {

            break;
        }
        nodes++;
        int y1=compute_next(y); //cout<<y1<<endl;
        par[y]=y1;
        par[y1]=start;
        visited[y1]=1;
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
void TwoOptbest(int print)
{
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
}


void TwoOptfirst(int print)
{
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
        break;
    }
}

bool cmp(vector<Point> a, vector<Point> b)
{
    return getTourCost(a)<getTourCost(b);
}


void solution(double optcost)
{

    vector<vector<Point> > toursfor2opt;
    vector<vector<Point> > tours;
    cout<<"Task 1:\n"<<endl;
    vector<double>cost;
    for(int i=0; i<10; i++)
    {
        NearestNeighbor(0);
        tours.push_back(tour);
        cost.push_back(getTourCost());
    }
    cout<<"\nNearest Neighbor Heuristic for pr76 : "<<endl;
    cout<<"Avg. case : "<<accumulate(cost.begin(),cost.end(),0)/10.0<<endl;
    cout<<"Best case : "<<*min_element(cost.begin(),cost.end())<<endl;
    cout<<"Worst case : "<<*max_element(cost.begin(),cost.end())<<endl;
    sort(tours.begin(),tours.end(),cmp);
    toursfor2opt.push_back(tours[0]);
    cost.clear();
    tours.clear();

    for(int i=0; i<10; i++)
    {
        Saving(0);
        tours.push_back(tour);
        cost.push_back(getTourCost());
    }
    cout<<"\nSaving Heuristic for pr76 : "<<endl;
    cout<<"Avg. case : "<<accumulate(cost.begin(),cost.end(),0)/10.0<<endl;
    cout<<"Best case : "<<*min_element(cost.begin(),cost.end())<<endl;
    cout<<"Worst case : "<<*max_element(cost.begin(),cost.end())<<endl;
    sort(tours.begin(),tours.end(),cmp);
    toursfor2opt.push_back(tours[0]);
    cost.clear();
    tours.clear();

    cout<<"\nTask 2:\n"<<endl;
    for(int i=0; i<10; i++)
    {
        RNearestNeighbor(0);
        tours.push_back(tour);
        cost.push_back(getTourCost());
    }
    cout<<"\nRandomized Nearest Neighbor Heuristic for pr76 : "<<endl;
    cout<<"Avg. case : "<<accumulate(cost.begin(),cost.end(),0)/10.0<<endl;
    cout<<"Best case : "<<*min_element(cost.begin(),cost.end())<<endl;
    cout<<"Worst case : "<<*max_element(cost.begin(),cost.end())<<endl;
    sort(tours.begin(),tours.end(),cmp);
    for(int i=0; i<3; i++)
        toursfor2opt.push_back(tours[i]);
    cost.clear();
    tours.clear();

    cost.clear();
    for(int i=0; i<10; i++)
    {
        Saving(0);
        tours.push_back(tour);
        cost.push_back(getTourCost());
    }
    cout<<"\nRandomized Saving Heuristic for pr76 : "<<endl;
    cout<<"Avg. case : "<<accumulate(cost.begin(),cost.end(),0)/10.0<<endl;
    cout<<"Best case : "<<*min_element(cost.begin(),cost.end())<<endl;
    cout<<"Worst case : "<<*max_element(cost.begin(),cost.end())<<endl;
    sort(tours.begin(),tours.end(),cmp);
    for(int i=0; i<3; i++)
        toursfor2opt.push_back(tours[i]);
    cost.clear();
    tours.clear();
    cout<<"\nTask 3:\n"<<endl;
    for(int i=0; i<toursfor2opt.size(); i++)
    {
        tour=toursfor2opt[i];
        TwoOptbest(0);
        cost.push_back(getTourCost());
    }

    cout<<"\nBest two opt for pr76 : "<<endl;
    cout<<"Avg. case : "<<accumulate(cost.begin(),cost.end(),0)/(double)cost.size()<<endl;
    cout<<"Best case : "<<*min_element(cost.begin(),cost.end())<<endl;
    cout<<"Worst case : "<<*max_element(cost.begin(),cost.end())<<endl;
    cout<<"Parentage : "<<(100.0*(accumulate(cost.begin(),cost.end(),0)/(double)cost.size())/optcost)<<endl;
    cost.clear();
    for(int i=0; i<toursfor2opt.size(); i++)
    {
        tour=toursfor2opt[i];
        TwoOptfirst(0);
        cost.push_back(getTourCost());
    }

    cout<<"\nFirst two opt for pr76 : "<<endl;
    cout<<"Avg. case : "<<accumulate(cost.begin(),cost.end(),0)/(double)cost.size()<<endl;
    cout<<"Best case : "<<*min_element(cost.begin(),cost.end())<<endl;
    cout<<"Worst case : "<<*max_element(cost.begin(),cost.end())<<endl;
    cout<<"Parentage : "<<(100.0*(accumulate(cost.begin(),cost.end(),0)/(double)cost.size())/optcost)<<endl;

    //Saving(0);
    // TwoOpt(0);



}

int main()
{
    vector<double> optcost;
    optcost.push_back(108159.0);
    optcost.push_back(7542.0);
    optcost.push_back(675.0);

    vector<pair<string,string> >v;
    v.push_back({"pr76.txt","outputpr76.txt"});
    v.push_back({"berlin52.tsp","outputberlin52.txt"});
    v.push_back({"st70.tsp","outputst70.txt"});
    for(int i=0; i<3; i++)
    {
        freopen(v[i].first.c_str(),"r",stdin);
        freopen(v[i].second.c_str(), "w", stdout);
        srand (time(NULL));

        cin>>n;
        int dummy;
        for(int i=1; i<=n; i++)
        {
            cin>>dummy>>point[i].x>>point[i].y;
            point[i].id=i;
        }
        // cout.precision(5);
        solution(optcost[i]);
    }


}
