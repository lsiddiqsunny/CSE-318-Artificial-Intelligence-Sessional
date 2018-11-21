#include <bits/stdc++.h>
using namespace std;

int n;

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
        for(int j=i+1;j<v.size();j++){
            if(v[i]>v[j]) co++;
        }
    }
    return co;
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
                continue;
            }
            int y=stringtoint(x);
            v.push_back(y);
        }
    }
  /*  for(int i=0;i<v.size();i++){
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

    }else{
        if((rem+inversion)%2==0){
            cout<<"No solution for this board"<<endl;
            return 0;
        }

    }

}