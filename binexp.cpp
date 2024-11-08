#include<bits/stdc++.h>
#include "accel.hpp"
using namespace std;

int M0;


int f(int a, int b) {
    return (1LL * a * b) % M0;
}

int binexp(int x, int y, int M){
    vector<int> id={1};
    M0=M;
    vector<int (*) (int,int)> fn={&f};
    OperatorClass<int> op(fn,id);
    Accel<OperatorClass<int>> a(op);
    return a.calcerate(x,y);
}

int main(){
    cout<<binexp(3,3,100);
    return 0;
}