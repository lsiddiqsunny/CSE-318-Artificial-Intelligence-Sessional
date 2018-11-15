#include <bits/stdc++.h>
using namespace std;
int n;

class State{

    int missionaries; //number of missionaries
    int cannibals; //number of cannibals
    int  current_side; //the side of the boat, 0 for left side and 1 for right  side
public:

    State(int x,int y,int z){

        missionaries=x;
        cannibals=y;
        current_side=z;

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

        if(s.getCannibals()>n||s.getMissionaries()>n||s.getCannibals()<0||s.getMissionaries()<0) return false;
        if(s.getMissionaries()<s.getCannibals() && s.getMissionaries()!=0) return false;
        return !((n - s.getMissionaries()) < (n - s.getCannibals()) && (n - s.getMissionaries()) != 0);


    }
    vector<State> getChildren(){
        vector<State>children;
        int missionaries_on_other_side=n-this->missionaries;
        int cannibals_on_other_side=n-this->cannibals;
        int new_side=1-current_side;

        State case1(missionaries_on_other_side+2,cannibals_on_other_side,new_side);
        if(ValidState(case1)){
            children.push_back(case1);
        }
        State case2(missionaries_on_other_side,cannibals_on_other_side+2,new_side);
        if(ValidState(case2)){
            children.push_back(case2);
        }
        State case3(missionaries_on_other_side+1,cannibals_on_other_side,new_side);
        if(ValidState(case3)){
            children.push_back(case3);
        }
        State case4(missionaries_on_other_side,cannibals_on_other_side+1,new_side);
        if(ValidState(case4)){
            children.push_back(case4);
        }
        State case5(missionaries_on_other_side+1,cannibals_on_other_side+1,new_side);
        if(ValidState(case5)){
            children.push_back(case5);
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
        State newstate(state.missionaries,state.cannibals,state.current_side);
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
        for(int i=0;i<n-state.missionaries;i++){
            os<<"M";
        }
        for(int i=0;i<n-state.cannibals;i++){
            os<<"C";
        }

    }
    else {
        for(int i=0;i<n-state.missionaries;i++){
            os<<"M";
        }
        for(int i=0;i<n-state.cannibals;i++){
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
public:


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

    void solutionwithbfs(State start,State goal){


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



    void solutionwithdfs(State start,State par,State goal){

        vis.push_back(start);
        parent.push_back(make_pair(start,par));
        if(start==goal) return;
        vector<State>children=start.getChildren();
        for (const auto i : children) {
            if(!checkvisited(i)){
                solutionwithdfs(i,start,goal);
            }
        }


    }
};


int main() {
    cin>>n;
    State Initial(n,n,0);
    State Final(n,n,1);

    Solution solution;


    cout<<"Solution with bfs :"<<endl;
    clock_t begin = clock();

    solution.Setting();
    solution.solutionwithbfs(Initial,Final);
    if(solution.checkvisited(Final))
    solution.printasolution(Final);
    else cout<<"No solution"<<endl;

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout<<"Time needed for solution with bfs : "<<elapsed_secs<<endl<<endl;

    cout<<"Solution with dfs :"<<endl;
    begin = clock();

    solution.Setting();
    solution.solutionwithdfs(Initial,Initial,Final);
    if(solution.checkvisited(Final))
        solution.printasolution(Final);
    else cout<<"No solution"<<endl;


    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout<<"Time needed for solution with dfs : "<<elapsed_secs<<endl;

    return 0;
}