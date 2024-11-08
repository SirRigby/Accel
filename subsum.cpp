#include<iostream>
#include<bitset>
#include<map>
#include "accel.hpp"

using namespace std;

int w;

template<int len=1>
struct F{
    static pair<bitset<len+1>,int> f0(pair<bitset<len+1>,int> a,pair<bitset<len+1>,int> b){
        auto c=b;
        c.second+=a.second;
        c.first=c.first<<(w*(a.second));
        return c;
    }
    static pair<bitset<len+1>,int> f1(pair<bitset<len+1>,int> a,pair<bitset<len+1>,int> b){
        auto c=a;
        c.first|=b.first;
        return c;
    }
};

static const int MAXN=100000;
template<int len=1>
void f(int m,vector<int> &ap){
    if(len < m) {
        f<min(len<<1,MAXN)>(m,ap);
        return;
    } 
    typedef bitset<len+1> bit;
    map<int,int> mp;
    for(auto i:ap){
        mp[i]++;
    }

    vector<pair<bit,int>> idv={{bit(1),0}};
    vector<pair<bit,int>(*) (pair<bit,int>,pair<bit, int>)> fn = {&F<len>::f0,&F<len>::f1};
    OperatorClass<pair<bit, int>> op(fn, idv); 
    Accel<OperatorClass<pair<bit, int>>> a(op);
    pair<bit,int> app={bit(1),1};
    for(auto i:mp){
        w=i.first;
        (app.first)|=(app.first)<<w;
        app.first|=a.calcerate(app,i.second).first;
    }
    cout<<app.first<<endl;
}

int main(){
    vector<int> r={2,2,2,2,2};
    int z=0;
    for(auto i:r){
        z+=i;
    }
    f(z,r);
    return 0;
}