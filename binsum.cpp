#include<bits/stdc++.h>
#include "accel.hpp"
using namespace std;

int M0;


int f(int a, int b) {
    return (1LL * a * b) % M0;
}
int g(int a, int b){
    int z=a+b;
    if(z>=M0){
        z-=M0;
    }
    return z;
}

int binsum(int x, int y, int M){
    vector<int> id={1,0};
    M0=M;
    vector<int (*) (int,int)> fn={&f,&g};
    OperatorClass<int> op(fn,id);
    Accel<OperatorClass<int>> a(op);
    return a.calcerate(x,y);
}

int main(){
    cout<<binsum(3,4,100);
    return 0;
}