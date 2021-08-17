//https://codeforces.com/problemset/problem/506/D
#include <bits/stdc++.h>

using namespace std;

const int N = int(1e5) + 5;

#define pb push_back
#define fi first
#define se second

const int B=450;
int n,m,q;
int a,b,c;
int deg[N];
int ans[N];
bool done[N];
vector<pair<int,int> > edg[N];
vector<vector<int> > comp;
vector<int> incomp[N], tmp[N];
vector<int> bg;
int bigid[N];
bool islarge[N];

int dp[B][N];

int id[N];

struct UF{
    vector<int> id;
    void init(int  n){
        id.resize(n);
        for(int i=0;i<n;i++){
            id[i]=i;
        }
    }

    int getid(int u){
        return (id[u]==u?u:id[u]=getid(id[u]));
    }

    bool samset(int u, int v){
        return getid(u)==getid(v);
    }

    void unite(int u,int v){
        u=getid(u);
        v=getid(v);
        id[u]=v;
    }
};


UF uf;




int main()
{
    ios::sync_with_stdio(0);
    freopen("input.txt", "r", stdin);
    cin >> n >> m;
    for(int i=0;i<m;i++){
        cin >> a >> b >> c;
        edg[c].pb({--a,--b});
    }
    uf.init(n);
    for(int i=1;i<=m;i++){
        for(auto u:edg[i]){
            a = u.fi;
            b = u.se;
            uf.unite(a,b);
        }
        for(auto u:edg[i]){
            a = u.fi;
            b = u.se;
            if(!done[a]){
                tmp[uf.getid(a)].pb(a);
                done[a]=1;
            }
            if(!done[b]){
                tmp[uf.getid(b)].pb(b);
                done[b]=1;
            }
        }
        for(auto u:edg[i]){
            a = u.fi;
            b = u.se;
            if(tmp[a].size()){
                comp.pb(tmp[a]);
                tmp[a].clear();
            }
            if(tmp[b].size()){
                comp.pb(tmp[b]);
                tmp[b].clear();
            }
            done[a]=done[b]=0;
            uf.id[a]=a;
            uf.id[b]=b;
        }
    }
    for(int i=0;i<comp.size();i++){
        for(auto u:comp[i]){
            incomp[u].pb(i);
        }
    }
    for(int i=0;i<n;i++){
        if(incomp[i].size()>=B){
            bigid[i]=bg.size();
            bg.push_back(i);
        }else{
            bigid[i]=-1;
        }
    }
    for(int u:bg){
        for(int c:incomp[u]){
            for(int v: comp[c]){
                dp[u][v]++;
            }
        }
    }
    cin >> q;
    while(q--){
        cin >> a >> b;
        --a;
        --b;
        if(bigid[a]==-1){
            swap(a,b);
        }
        if(bigid[a]!=-1){
            cout << dp[a][b] << endl;
        }else{
            int res=0;
            int i=0,j=0;
            while(i<incomp[a].size() && j<incomp[b].size()){
                if(incomp[a][i]==incomp[b][j]){
                    res++;
                    i++;
                    j++;
                }else if(incomp[a][i]<incomp[b][j]){
                    i++;
                }else{
                    j++;
                }
            }
            cout << res << endl;
        }
    }


    return 0;

}
