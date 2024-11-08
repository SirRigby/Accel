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
        v.resize(n,vector<td>(n,0));
    }
    Matrix(int n1, char isIdentity){
        n=n1;
        m=n;
        v.resize(n,vector<td>(n,0));
        for(int i=0;i<n;i++){
            v[i][i]=1;
        }
    }
    Matrix(int n1,int m1){
        n=n1;
        m=m1;
        v.resize(n,vector<td> (m,0));
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
                ans.v[i][j]=(ans.v[i][j]+(a.v[i][k]*1LL*b.v[k][j])%M)%M;
            }
        }
    }
    return ans;
}


td graph(vector<vector<int>> &adjMatrix,int from , int to,long long n, int M){
    M0=M;
    int deg=adjMatrix.size();
    Matrix ans(adjMatrix);
    vector<Matrix> id={Matrix(deg,'*')};
    vector<Matrix (*) (Matrix,Matrix)> fn={&f};
    OperatorClass<Matrix> op(fn,id);
    op.id=id[0];
    Accel<OperatorClass<Matrix>> a(op);
    ans=a.calcerate(ans,n);
    return ans.v[from][to];
}

int main(){
    
    return 0;
}