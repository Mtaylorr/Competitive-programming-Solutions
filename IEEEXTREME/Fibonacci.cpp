//https://csacademy.com/ieeextreme-practice/task/09f92a575cc006d4a6a7f525f370ec30/
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;


const int N = 1e3+5;

vector<pair<int,int> > v;
set<pair<int,int> > ss;
int t,n,c;
int m;
int main(){
    //freopen("input.txt", "r", stdin);
    int u0=1;
    int u1=2;
    do{
        ss.insert({u0,u1});
        v.pb({u0,u1});
        int tmp = u1;
        u1 = u1+u0;
        u0 = tmp;
        u1%=10;
        u0%=10;
    }while(ss.count({u0,u1})==0);
    int sz = v.size();
    scanf("%d",&t);
    while(t--){
        scanf("%d",&m);
        m--;
        m%=sz;
        printf("%d\n",v[m].first);

    }
    return 0;
}
