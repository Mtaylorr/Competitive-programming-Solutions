#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5;
const int MOD = 10567201 ;

bool vis[N];
bool candidate[N];
bool reach[N];
int n,m,t,u,v;
vector<int> adj[N],radj[N],radj2[N];
vector<int> ord;
vector<int> tmp;
int id=0;
int cc[N];
int sz[N];
bool othReach[N];

void dfs(int u){
    vis[u]=1;
    for(auto v:adj[u]){
        if(!vis[v])
            dfs(v);
    }
    ord.pb(u);
}

void getCC(int u){
    vis[u]=1;
    for(auto v:radj[u]){
        if(!vis[v])
            getCC(v);
    }
    tmp.pb(u);
}


void dfs3(int u){
    if(vis[u])
        return ;
    vis[u]=1;
    for(auto v:radj2[u]){
       // cout << u << " " << v<< " " << cc[u]<<" "<<cc[v] << endl;
        if(u!=t  && v!=t && cc[v]!=cc[u]){

            if(reach[cc[u]] || othReach[cc[u]]){
                othReach[cc[v]]=1;
            }
        }
        dfs3(v);
    }
}


int main()
{
    freopen("input.txt", "r",stdin);
    scanf("%d%d%d",&n,&m,&t);
    for(int i=0;i<m;i++){
        scanf("%d%d",&u,&v);
        if(v==t){
            candidate[u]=1;
        }else{
            adj[u].pb(v);
            radj[v].pb(u);
        }
        radj2[v].pb(u);

    }
    for(int i=0;i<n;i++){
        if(!vis[i])
            dfs(i);
    }
    reverse(ord.begin(),ord.end());
    memset(vis, 0, sizeof(vis));
    for(auto i:ord){
        if(vis[i])
            continue;
        tmp.clear();
        getCC(i);
        for(auto u:tmp){
            cc[u]=id;
            //cout << u << " " << id << endl;
            if(candidate[u]){
                sz[id]++;
                reach[id]=1;
                //cout << id << endl;
            }
        }
        id++;
    }
    memset(vis, 0, sizeof(vis));
    dfs3(t);
    tmp.clear();
    set<int> possibleCC;
    for(int i=0;i<id;i++){
        if(sz[i]==1 && othReach[i]==0){
            possibleCC.insert(i);
        }
    }
    for(int i=0;i<n;i++){
        if(i==t)
            continue;
        if(candidate[i] && possibleCC.count(cc[i])){
            tmp.pb(i);
        }
    }
    sort(tmp.begin(),tmp.end());
    cout << tmp.size() << endl;
    for(auto u:tmp){
        cout << u << "\n";
    }
    return 0;
}
