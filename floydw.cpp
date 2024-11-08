#include<bits/stdc++.h>
#include "accel.hpp"
using namespace std;

int M0;

typedef int td;

struct Matrix{
    int n,m;
    vector<vector<td>> v;
    static const td M=1e9+7;

    Matrix(){
    }

    Matrix(vector<vector<td>> &v1){
        n=v1.size();
        m=n;
        v=v1;
    }
    Matrix(int n1){
        n=n1;
        m=n;
        v.resize(n,vector<td>(n,INT_MAX));
    }
    Matrix(int n1, char isIdentity){
        n=n1;
        m=n;
        v.resize(n,vector<td>(n,INT_MAX));
        for(int i=0;i<n;i++){
            v[i][i]=0;
        }
    }
    Matrix(int n1,int m1){
        n=n1;
        m=m1;
        v.resize(n,vector<td> (m,INT_MAX));
    }

};

Matrix f(Matrix a, Matrix b){
    int M=M0;
    Matrix ans(a.n,b.m);
    if(a.m!=b.n){
        return ans;
    }
    for(int i=0;i<a.n;i++){
        for(int j=0;j<b.m;j++){
            for(int k=0;k<a.m;k++){
                if(a.v[i][k]!=INT_MAX && b.v[k][j]!=INT_MAX){
                ans.v[i][j]=min(ans.v[i][j],(a.v[i][k]+b.v[k][j]));
                }
            }
        }
    }
    return ans;
}


vector<vector<int>> floydw(vector<vector<int>> &adjMatrix, int M){
    M0=M;
    int deg=adjMatrix.size();
    Matrix ans(adjMatrix);
    vector<Matrix> id={Matrix(deg,'*')};
    vector<Matrix (*) (Matrix,Matrix)> fn={&f};
    OperatorClass<Matrix> op(fn,id);
    op.id=id[0];
    Accel<OperatorClass<Matrix>> a(op);
    ans=a.calcerate(ans,deg);
    return ans.v;
}

int main(){
    
    return 0;
}