#include<bits/stdc++.h>
#include "accel.hpp"
using namespace std;

vector<int> f(vector<int> a,vector<int> b) {
    vector<int> c=a;
    for(int i=0;i<a.size();i++){
        c[i]=a[b[i]];
    }
    return c;
}

vector<int> perm(vector<int> &v, long long n){
    int sz=v.size();
    vector<int> w(sz);
    for(int i=0;i<sz;i++){
        w[i]=i;
    }
    vector<vector<int>> id={w};
    vector<vector<int> (*) (vector<int>,vector<int>)> fn={&f};
    OperatorClass<vector<int>> op(fn,id);
    op.id=w;
    Accel<OperatorClass<vector<int>>> a(op);
    return a.calcerate(v,n);
}

int main(){
    vector<int> p={5,3,2,1,0,4};
    for(int i=0;i<4;i++){
        for(auto j:perm(p,i)){
            cout<<j<<" ";
        }
        cout<<endl;
    }
    return 0;
}