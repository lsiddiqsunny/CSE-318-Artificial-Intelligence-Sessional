#include <bits/stdc++.h>
using namespace std;


class State{

    int missionaries; //number of missionaries
    int cannibals; //number of cannibals
    int  current_side; //the side of the boat, 0 for left side and 1 for right  side
    int n;
    int m;
    int k;

public:

    State(int x,int y,int z,int a,int b,int c){

        missionaries=x;
        cannibals=y;
        current_side=z;
        n=a;
        m=b;
        k=c;

    }





    int getMissionaries(){
        return  missionaries;
    }
    int getCannibals(){
        return  cannibals;
    }
    int getCurrentSide(){
        return  current_side;
    }

    bool ValidState(State s){

        if(s.getCannibals()>m||s.getMissionaries()>n||s.getCannibals()<0||s.getMissionaries()<0) return false;
        if(s.getMissionaries()<s.getCannibals() && s.getMissionaries()!=0) return false;
        return !((n - s.getMissionaries()) < (m - s.getCannibals()) && (n - s.getMissionaries()) != 0);


    }
    vector<State> getChildren(){
        vector<State>children;
        int missionaries_on_other_side=n-this->missionaries;
        int cannibals_on_other_side=m-this->cannibals;
        int new_side=1-current_side;
        for(int i=0;i<=min(k,n);i++){
            for(int j=0;j<=max(0,(k-i));j++){
                if(i==0 and j==0) continue;
                State s(missionaries_on_other_side+i,cannibals_on_other_side+j,new_side,n,m,k);
                if(ValidState(s)){
                    children.push_back(s);
                }
            }
        }

        return children;




    }


    bool operator ==(const State& state) {
        return !(missionaries != state.missionaries || cannibals != state.cannibals || current_side != state.current_side);
    }

    State operator =(const State& state) {
        missionaries=state.missionaries;
        cannibals=state.cannibals;
        current_side=state.current_side;
        State newstate(state.missionaries,state.cannibals,state.current_side,state.n,state.m,state.k);
        return newstate;
    }


    bool operator <(const State& state) {
        if(missionaries<=state.missionaries) return true;
        else if(cannibals<=state.cannibals) return true;
        else if(state.current_side == current_side) return true;
        else return  false;
    }
    friend ostream& operator<<(ostream& os, const State& state);


};


ostream& operator<<(ostream& os, const State& state)
{
    if(state.current_side==0){
        for(int i=0;i<state.missionaries;i++){
            os<<"M";
        }
        for(int i=0;i<state.cannibals;i++){
            os<<"C";
        }
        os<<" B------- ";
        for(int i=0;i<state.n-state.missionaries;i++){
            os<<"M";
        }
        for(int i=0;i<state.m-state.cannibals;i++){
            os<<"C";
        }

    }
    else {
        for(int i=0;i<state.n-state.missionaries;i++){
            os<<"M";
        }
        for(int i=0;i<state.m-state.cannibals;i++){
            os<<"C";
        }
        os<<" -------B ";
        for(int i=0;i<state.missionaries;i++){
            os<<"M";
        }
        for(int i=0;i<state.cannibals;i++){
            os<<"C";
        }
    }
    return os;
}



class Solution{
    queue<State>q;
    vector<pair<State,State> > parent;
    vector<State>vis;
    stack<State>path;
    int missonaries;
    int cannibals;
    int passenger;

public:

    Solution(int m,int c,int k){
        missonaries=m;
        cannibals=c;
        passenger=k;
    }

    void Setting(){
        while(!q.empty()) q.pop();
        parent.clear();
        vis.clear();
        while(!path.empty()) path.pop();

    }

    bool checkvisited(State s){
        for (auto vi : vis) {
            if(vi ==s){
                return true;
            }
        }
        return false;

    }
    State getParent(State s){
        for (auto i : parent) {
            if(i.first==s){
                return i.second;
            }
        }


    }
    void solutionwithbfs(){


        cout<<"Solution with bfs :"<<endl;
        clock_t begin = clock();
        State Initial(missonaries,cannibals,0,missonaries,cannibals,passenger);
        State Final(missonaries,cannibals,1,missonaries,cannibals,passenger);

        Setting();
        bfs(Initial,Final);
        if(checkvisited(Final))
            printasolution(Final);
        else cout<<"No solution"<<endl;

        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        cout<<"Number of explored nodes : "<<explorednode()<<endl;
        cout<<"Time needed for solution with bfs : "<<elapsed_secs<<endl<<endl;



    }

    void bfs(State start,State goal){


       Setting();
        parent.push_back(make_pair(start,start));

        vis.push_back(start);
        q.push(start);
        while(!q.empty()){
            State u=q.front();

            q.pop();
            if(u==goal){
                goal=u;
                break;
            }
            vector<State> children=u.getChildren();
            for (auto i : children) {
                if(!checkvisited(i)){
                    vis.push_back(i);
                    q.push(i);
                    parent.push_back(make_pair(i,u));

                }
            }
            if(vis.size()>=1000000) break;

        }





    }
void printasolution(State goal){


    State cur=goal;
    State par=getParent(cur);
    // cout<<cur<<endl<<par.getCannibals()<<endl;
    while(true){
        path.push(cur);
        if(cur==par) break;
        cur=par;
        par=getParent(par);


    }

    while(!path.empty()){
        cout<<path.top()<<endl;
        path.pop();
    }
}

    int explorednode(){
        return vis.size();
    }
    void solutionwithdfs(){

        State Initial(missonaries,cannibals,0,missonaries,cannibals,passenger);
        State Final(missonaries,cannibals,1,missonaries,cannibals,passenger);

        cout<<"Solution with dfs :"<<endl;
        clock_t begin = clock();

        Setting();
        dfs(Initial,Initial,Final);
        if(checkvisited(Final))
            printasolution(Final);
        else cout<<"No solution"<<endl;


        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        cout<<"Number of explored nodes : "<<explorednode()<<endl;
        cout<<"Time needed for solution with dfs : "<<elapsed_secs<<endl;


    }


    void dfs(State start,State par,State goal){

        vis.push_back(start);
        if(vis.size()>=1000000) return;
        parent.push_back(make_pair(start,par));
        if(start==goal) return;
        vector<State>children=start.getChildren();
        for (const auto i : children) {
            if(!checkvisited(i)){
                dfs(i,start,goal);
            }
        }


    }
};


int main() {
    int m,c,k;
    cin>>m>>c>>k;

    State s(m,c,0,m,c,k);
    vector<State>ch=s.getChildren();


    Solution solution(m,c,k);

    solution.solutionwithbfs();
    solution.solutionwithdfs();


    return 0;
}