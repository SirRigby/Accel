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

Matrix g(Matrix a, Matrix b){
    int M=M0;
    Matrix ans(a.n,a.m);
    for(int i=0;i<a.n;i++){
        for(int j=0;j<b.m;j++){
            ans.v[i][j]=(a.v[i][j]+b.v[i][j])%M;
        }
    }
    return ans;
}

td recur(vector<td> &coeff, vector<td> &bases, long long n, int M){
    int deg=coeff.size();
    if(n<deg){
        int y=0;
        for(int i=0;i<=n;i++){
            y=(y+bases[i])%M;
        }
        return y;
    }
    Matrix coeMat(deg);
    for(int i=0;i<deg;i++){
        coeMat.v[0][i]=coeff[deg-1-i];
    }
    for(int i=1;i<deg;i++){
        coeMat.v[i][i-1]=1;
    }
    Matrix baseMat(deg,1);
    for(int i=0;i<deg;i++){
        baseMat.v[i][0]=bases[deg-1-i];
    }
    n=(n-deg+1);
    int y=0;
    for(int i=0;i<deg;i++){
        y=(y+bases[i])%M;
    }
    M0=M;
    vector<Matrix> id={Matrix(deg,'*')};
    vector<Matrix (*) (Matrix,Matrix)> fn={&f,&g};
    OperatorClass<Matrix> op(fn,id);
    op.id=id[0];
    Accel<OperatorClass<Matrix>> a(op);
    coeMat=a.calcerate(coeMat,n);
    coeMat=f(coeMat,baseMat);
    return (coeMat.v[0][0]+y)%M;
}

int main(){
    vector<int> coeff={1,1,2},bases={1,2,3};
    for(int i=0;i<5;i++){
        cout<<recur(coeff,bases,i,100)<<endl;
    }
    return 0;
}