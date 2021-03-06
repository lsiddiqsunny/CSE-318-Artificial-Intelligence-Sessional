#include <bits/stdc++.h>
using namespace std;

int n;

int heuristic_cost(vector<int> board);
int choise;
class Node
{
    vector<int> board;
    Node *parent;


public:
    int priority;
    Node()
    {
        parent=NULL;
        priority=0;
    }
    Node(vector<int>v,Node* par)
    {
        parent=par;
        this->board=v;
        priority=0;
    }
    Node(vector<int>v)
    {
        parent=NULL;
        this->board=v;
        priority=0;
    }
    Node(const Node &node)
    {
        this->board=node.board;
        this->parent=new Node();
        priority=node.priority;
        if(node.parent!=NULL)
            *parent=*node.parent;

    }

    void setpriority(int value)
    {
        priority= value+h();
    }
    int getvalue()
    {
        return priority-h();
    }
    int getpriority()
    {
        return priority;
    }
    int h()
    {
        return heuristic_cost(board);

    }
    vector<int>get_board()
    {
        return board;
    }
    Node* getParent()
    {
        return parent;
    }
    bool operator==(const Node& node){
        for(int i=0;i<board.size();i++){
            if(board[i]!=node.board[i]) return  false;
        }
        return true;
    }




    friend ostream& operator<<(ostream& os, const Node& node);

    ~Node()
    {
        // delete  parent;
        parent=NULL;
    }
};

int heuristic_cost(vector<int> board)
{
    if(choise==1) {
        int now = 1;
        int co = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int pos = i * n + j;
                if (board[pos] == -1)
                    continue;
                if (board[pos] != now) {
                    co++;
                }
                now++;
            }
        }
        return co;
    }
    else if(choise==2){
        int co=0;
        int now ;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int pos = i * n + j;
                if (board[pos] == -1)
                    continue;

                now=board[pos];
                int orgx,orgy=(now%n);
                if(now%n==0){
                    orgx=now/n;
                }
                else orgx=(now/n)+1;
                if(orgy==0) orgy=n;
                int nowx=i+1;
                int nowy=j+1;
               // cout<<now<<" "<<nowx<<" "<<nowy<<" "<<orgx<<" "<<orgy<<endl;
                co+=abs(nowx-orgx)+abs(nowy-orgy);

            }
        }
        return co;

    }
    else{
        int co=0;
        int now ;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int pos = i * n + j;
                if (board[pos] == -1)
                    continue;

                now=board[pos];
                int orgx,orgy=(now%n);
                if(now%n==0){
                    orgx=now/n;
                }
                else orgx=(now/n)+1;
                if(orgy==0) orgy=n;
                int nowx=i+1;
                int nowy=j+1;
                // cout<<now<<" "<<nowx<<" "<<nowy<<" "<<orgx<<" "<<orgy<<endl;
                co+=abs(nowx-orgx)+abs(nowy-orgy);

            }
        }
        int linear_conflict=0;

        for(int i=0;i<n;i++){
            vector<int>v;
            map<int,int>pos;
            for(int j=0;j<n;j++){
                int pos1 = i * n + j;
                if (board[pos1] == -1)
                    continue;
                pos[board[pos1]]=j;
            }
            for(int j=n*i+1;j<n*i+1+n;j++){
                v.push_back(j);
            }
            for(int k=0;k<v.size();k++){
                if(pos.find(v[k])!=pos.end()){
                    for(int l=k+1;l<v.size();l++){

                        if(pos.find(v[l])!=pos.end()){
                            int pos1=pos[v[l]];
                            if(pos1<pos[v[k]]) linear_conflict++;
                          //  cout<<v[k]<<" "<<v[l]<<endl;
                        }
                    }
                }
            }
           // cout<<endl;

        }
        for(int i=0;i<n;i++){
            vector<int>v;
            map<int,int>pos;


            for(int j=0;j<n;j++){
                int pos1 = j * n + i;
                if (board[pos1] == -1)
                    continue;
                pos[board[pos1]]=j;
            }
            int s=i+1;
            for(int k=s;k<n*n;k=k+n){
                v.push_back(k);
            }
            for(int k=0;k<v.size();k++){
                if(pos.find(v[k])!=pos.end()){
                    for(int l=k+1;l<v.size();l++){

                        if(pos.find(v[l])!=pos.end()){
                            int pos1=pos[v[l]];
                            if(pos1<pos[v[k]]) linear_conflict++;
                             // cout<<v[k]<<" "<<v[l]<<endl;
                        }
                    }
                }
            }
        }



        return co+2*linear_conflict;
    }

}

struct Comp
{
    bool operator()(const Node& a, const Node& b)
    {
        return a.priority>b.priority;
    }
};

pair<int,int> getpos(vector<int>v)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            int pos=n*i+j;
            if(v[pos]==-1)
            {
                return make_pair(i,j);
            }
        }
    }
}

int dx[4]= {0,0,1,-1};
int dy[4]= {1,-1,0,0};

bool isvalid(int x,int y)
{
    if(x<0 ||x>=n ||y<0 ||y>=n)
        return false;
    return true;

}

vector<Node> getchildren(Node node)
{
    vector<int>v=node.get_board();
    pair<int,int>pos=getpos(v);
    vector<Node> children;

    vector<int>x;
    int nowx=pos.first,nowy=pos.second;
    Node *par=new Node(node);
    //cout<<*par;
    for(int i=0; i<4; i++)
    {
        x.clear();
        x=v;
        if(isvalid(nowx+dx[i],nowy+dy[i]))
        {
            swap(x[(pos.first*n+pos.second)],x[(nowx+dx[i])*n+(nowy+dy[i])]);

            Node child(x,par);

            child.setpriority(node.getvalue()+1);

            children.push_back(child);
        }

    }
    //cout<<*(children[0].getParent());
    /*for(int i=0;i<children.size();i++){
        cout<<children[i];
    }*/

    return children;



}
vector<Node>closedlist;
bool inclosedlist(Node x){
    for(int i=0;i<closedlist.size();i++){
        if(closedlist[i]==x) return true;
    }
    return  false;

}

void printsolution(Node x){
    if(x.getParent()==NULL){

        return ;
    }
    printsolution(*(x.getParent()));
    cout<<x;

}
void solve(Node start,Node goal)
{

    //map<Node,int,Comp>mp;
    closedlist.clear();
    int expanded_node=0;
    priority_queue<Node,vector<Node>,Comp >q;
    start.setpriority(0);
    q.push(start);
    while(!q.empty())
    {
        Node x=q.top();
        //  cout<<x;cout<<x.getpriority()<<endl;

        q.pop();
        if(x==goal) {goal=x;break;}
        //mp[x]=1;
        closedlist.push_back(x);
        vector<Node>children=getchildren(x);
        for(int i=0;i<children.size();i++){
            Node y=children[i];
            if(!inclosedlist(y)){
                expanded_node++;
                q.push(y);
                // cout<<*y.getParent();
            }
        }


    }
    //cout<<goal.getpriority()<<endl;
    // printsolution(goal);
    stack<Node>path;
    path.push(goal);
    while(goal.getParent()){
        goal=*goal.getParent();
        //cout<<goal;
        path.push(goal);
        // cout<<path.top();

    }
    // cout<<path.size()<<endl;
    int path_size=path.size();
    while(!path.empty()){
        Node x=path.top();
        path.pop();
        cout<<x<<endl;
    }
    if(choise==1){
        cout<<"Solution using Hamming distance : "<<endl;
    }
    else if(choise==2){
        cout<<"Solution using Manhattan distance: "<<endl;
    }
    else{
        cout<<"Solution using Linear Conflict: "<<endl;

    }
     cout<<"Steps for the solutions : "<<path_size<<endl;
    cout<<"Explored Node : "<<closedlist.size()<<endl;
    cout<<"Expanded Node : "<<expanded_node<<endl;



}

ostream& operator<<(ostream& os, const Node& node)
{
    if(node.board.size()==(n*n)) {
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {

                int pos=n*i+j;
                if(node.board[pos]==-1)
                {
                    os<<"  ";
                }
                else
                    os<<node.board[pos]<<" ";
            }
            os<<endl;
        }
    }
    return os;

}


int stringtoint(string s)
{
    int  num=0;
    int sz=s.size();
    int pw=1;
    for(int i=1; i<sz; i++)
    {
        pw*=10;
    }
    for(int i=0; i<sz; i++)
    {
        num+=(s[i]-'0')*pw;
        pw/=10;
    }
    return num;

}

int inversioncount(vector<int>v)
{
    int co=0;
    for(int i=0; i<v.size(); i++)
    {
        if(v[i]==-1)
            continue;
        for(int j=i+1; j<v.size(); j++)
        {
            if(v[j]==-1)
                continue;
            if(v[i]>v[j])
                co++;
        }
    }
    return co;
}
Node GoalGenerator()
{

    vector<int>v;
    for(int i=1; i<n*n; i++)
    {
        v.push_back(i);
    }
    v.push_back(-1);
    Node Goal(v);
    return Goal;
}
int main()
{
    cout<<"Enter board size : ";
    cin>>n;
    cin.ignore();
    string s[n];
    vector<int>v;
    int rem=-1;
    int zero=0;
    for(int i=0; i<n; i++)
    {
        getline(cin,s[i]);
        istringstream iss(s[i]);
        string x;
        while ( getline( iss, x, ' ' ) )
        {
            if(x.size()==0 && zero==0)
            {
                rem=i;
                v.push_back(-1);
                zero++;
                continue;
            }
            if(x.size()==0 && zero!=0)
            {
                continue;
            }
            int y=stringtoint(x);
            v.push_back(y);
        }
    }
    /* for(int i=0;i<v.size();i++){
          cout<<v[i]<<" ";
      }
      cout<<endl;
    */
    int  inversion=inversioncount(v);
    //cout<<inversion<<endl;

    if(n%2==1)
    {
        if(inversion%2==1)
        {
            cout<<"No solution for this board"<<endl;
            return 0;
        }
        Node start(v);
        Node goal=GoalGenerator();
        getchildren(start);
//        cout<<start;
//        cout<<goal;
        choise=3;
        solve(start,goal);
        choise=2;
        solve(start,goal);
        choise=1;
        solve(start,goal);


    }
    else
    {
        if((rem+inversion)%2==0)
        {
            cout<<"No solution for this board"<<endl;
            return 0;
        }
        Node start(v);
        Node goal=GoalGenerator();
        choise=3;
        solve(start,goal);
        choise=2;
        solve(start,goal);
        choise=1;
        solve(start,goal);
    }


}
