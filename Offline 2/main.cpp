#include <bits/stdc++.h>
using namespace std;

int n;

class Node{
    vector<vector<int> > board;
    Node *parent;
    int priority=0;

public:
    Node(){
        parent=NULL;
        priority=0;
    }
    Node(vector<int>v){
        parent=NULL;
        vector<int>x(n);
        for(int i=0;i<n;i++){
            x.clear();

            for(int j=0;j<n;j++){
                x.push_back(v[i*n+j]);
            }
            board.push_back(x);

        }
        priority=0;
    }
    Node(const Node &node){
        this->board=node.board;
        this->parent=new Node();
        priority=node.priority;
        *parent=*node.parent;

    }

    Node operator =(const Node& node) {
        this->board=node.board;
        this->parent=new Node();
        priority=node.priority;
        *parent=*node.parent;
    }
    void setpriority(int value){
        priority= value+h();
    }
    int getpriority(){
        return priority;
    }
    int h(){

    }
    bool operator <(const Node& node) {
        if(priority<=node.priority) return true;
        else return false;
    }


    friend ostream& operator<<(ostream& os, const Node& node);

    ~Node(){
        delete  parent;
        parent=NULL;
    }
};
ostream& operator<<(ostream& os, const Node& node){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(node.board[i][j]==-1){
                cout<<"  ";
                continue;
            }
            cout<<node.board[i][j]<<" ";
        }
        cout<<endl;
    }
}


int stringtoint(string s){
    int  num=0;
    int sz=s.size();
    int pw=1;
    for(int i=1;i<sz;i++){
        pw*=10;
    }
    for(int i=0;i<sz;i++){
        num+=(s[i]-'0')*pw;
        pw/=10;
    }
    return num;

}

int inversioncount(vector<int>v){
    int co=0;
    for(int i=0;i<v.size();i++){
        if(v[i]==-1) continue;
        for(int j=i+1;j<v.size();j++){
            if(v[j]==-1) continue;
            if(v[i]>v[j]) co++;
        }
    }
    return co;
}
Node GoalGenerator(){

    vector<int>v;
    for(int i=1;i<n*n;i++){
        v.push_back(i);
    }
    v.push_back(-1);
    Node Goal(v);
    return Goal;
}
int main() {
    cout<<"Enter board size : ";
    cin>>n;
    cin.ignore();
    string s[n];
    vector<int>v;
    int rem=-1;
    for(int i=0;i<n;i++){
        getline(cin,s[i]);
        istringstream iss(s[i]);
        string x;
        while ( getline( iss, x, ' ' ) ) {
            if(x.size()==0) {
                rem=i;
                v.push_back(-1);
                continue;
            }
            int y=stringtoint(x);
            v.push_back(y);
        }
    }
   /*for(int i=0;i<v.size();i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;
*/
    int  inversion=inversioncount(v);
  //  cout<<inversion<<endl;

    if(n%2==1){
        if(inversion%2==1){
            cout<<"No solution for this board"<<endl;
            return 0;
        }
        Node start(v);
        Node Goal=GoalGenerator();
        cout<<Goal;

    }else{
        if((rem+inversion)%2==0){
            cout<<"No solution for this board"<<endl;
            return 0;
        }

    }


}
