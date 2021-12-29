//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=465
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5+5;
const int MOD = 998244353 ;


int n;
vector<int> adj[20];
vector<vector<int> > sols;
vector<int> cursol;
bool vis[N];

bool isprime(int x){
    if(!(x&1))
        return x==2;
    for(int i=3;i*i<=x;i+=2){
        if(x%i==0)
            return 0;
    }
    return 1;
}

void swim(int dpth, int x){
    if(dpth==n-1){
        if(isprime(x+1)){
            sols.pb(cursol);
        }
        return ;
    }
    vis[x]=1;
    for(auto v:adj[x]){
        if(v>n)
            break;
        if(vis[v])
            continue;
        cursol.pb(v);
        swim(dpth+1,v);
        cursol.pop_back();
    }
    vis[x]=0;
}


int main(){
    freopen("input.txt", "r",stdin);
    for(int i=1;i<=16;i++){
        for(int j=1;j<=16;j++){
            if(j==i)
                continue;
            if(isprime(i+j)){
                adj[i].pb(j);
            }
        }
    }
    int ii=0;
    while(~scanf("%d",&n)){
        sols.clear();
        cursol.clear();
        cursol.pb(1);
        swim(0,1);
        printf("Case %d:\n",++ii);
        for(int i=0;i<sols.size();i++){
            for(int j=0;j<n;j++){
                cout << sols[i][j] <<" \n"[j==n-1];
            }
        }
    }
    return 0;
}
