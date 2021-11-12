//https://codeforces.com/contest/587/problem/D

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e6 + 5, E = 1e6+5;
const int MOD = 1e9 + 7 ;

#define neig(a, u,v,e) for(int e=a.head[u], v;(~e)&&(v=a.to[e],1);e=a.nxt[e])

struct Adj{
    int n,edgcnt, nxt[E], to[E], head[N];

    void addEdege(int a , int b){
        nxt[edgcnt]=head[a];
        head[a]=edgcnt;
        to[edgcnt++]=b;
    }

    void init(){
        edgcnt=0;
        memset(head, -1,n*sizeof(head[0]));
    }
}adj;

int vid, vis[N], nodes[N], ndcnt, low[N], dfst[N], curt, comps, comp[N];
int val[N];
void dfs(int u){
    vis[u]=vid;
    comp[u]=-1;
    nodes[ndcnt++]=u;
    low[u]=dfst[u]=curt++;
    neig(adj, u,v,e){
        if(vis[v]!=vid){
            dfs(v);
            low[u]=min(low[u], low[v]);
        }else{
            if(comp[v]==-1){
                low[u]=min(low[u],low[v]);
            }
        }
    }
    if(dfst[u]==low[u]){
        do{
            comp[nodes[--ndcnt]]=comps;
        }while(nodes[ndcnt]!=u);
        comps++;
    }
}

void tarjan(){
    comps=0;
    vid++;
    ndcnt=0;
    curt=0;
    for(int i=0;i<adj.n;i++){
        if(vis[i]!=vid)
            dfs(i);
    }
}

void getsol(int u, int par=-1){
    if(vis[u]==vid)
        return ;
    vis[u]=vid;
    neig(adj,u,v,e){
        getsol(v,u);
    }
    if(val[comp[u]]==-1 &&(par==-1 || comp[u]!=comp[par])){
        val[comp[u]]=1;
        val[comp[u^1]]=0;
    }
}



bool twoSat(){
    tarjan();
    vid++;
    memset(val, -1, comps*sizeof(val[0]));
    for(int i=0;i<adj.n;i+=2){
        getsol(i);
        getsol(i+1);
        if(comp[i]==comp[i+1])
            return 0;
    }
    return 1;
}

int var(int x){
    return x<<1;
}
int notvar(int x){
    return x^1;
}

void addor(int x,int y){
    adj.addEdege(notvar(x),y);
    adj.addEdege(notvar(y),x);
}

int n,m, a,b,c, t[N],cnt[N];
map<int,vector<int> > graph[N];
vector<int> rests[N];

void buildadj(){
    adj.n = 6*m;
    adj.init();
    int cur=m-1;
    for(int i=0;i<n;i++){
        for(auto & u:graph[i]){
            if(u.se.size()<2)
                continue;
            int x = u.se[0];
            int y = u.se[1];
            addor(var(x),var(y));
            //addor(notvar(var(x)), notvar(var(y)));
        }
        for(int j=0;j<rests[i].size();j++){
            cur++;
            int x = rests[i][j];
            int y = cur;
            addor(notvar(var(x)), var(y));
            if(j>0){
                addor(notvar(var(x)), notvar(var(y-1)));
                addor(notvar(var(y-1)), var(y));
            }
        }
    }
}

int prob[E];

void addconstraint(int u){
    for(int i=0;i<m;i++){
        if(t[i]>u || !prob[i]){
            addor(notvar(var(i)),notvar(var(i)));
        }
    }
}

bool ok(int u){
    buildadj();
    addconstraint(u);
    return twoSat();
}


int solve(){
    int l=0;
    int r = 1e9+5;
    while(l<r){
        int md = (l+r)/2;
        if(ok(md)){
            r=md;
        }else{
            l=md+1;
        }
    }
    ok(l);
    return l;
}


int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++){
        scanf("%d%d%d%d",&a,&b,&c, &t[i]);
        a--;b--;
        graph[a][c].pb(i);
        graph[b][c].pb(i);
        if(graph[a][c].size()>2){
            puts("No");
            return 0;
        }
        if(graph[a][c].size()==2){
            cnt[a]++;
            prob[i]=1;
            prob[graph[a][c][0]]=1;

        }
        if(graph[b][c].size()>2){
            puts("No");
            return 0;
        }
        if(graph[b][c].size()==2){
            cnt[b]++;
            prob[i]=1;
            prob[graph[b][c][0]]=1;

        }
    }
    for(int i=0;i<n;i++){
        if(cnt[i]>1){
            puts("No");
            return 0;
        }
    }
    for(int i=0;i<n;i++){
        for(auto &u:graph[i]){
                for(auto v:u.se)
                    rests[i].pb(v);
        }
    }
    int ans = solve();
    if(ans>1e9){
        cout << "No";
    }else{
        cout << "Yes\n";
        cout << ans << " ";
        int nb=0;
        for(int i=0;i<2*m;i+=2){
            if(val[comp[i]]==1 )
                nb++;
        }
        cout << nb << "\n";

        for(int i=0;i<2*m;i+=2){
            if(val[comp[i]]==1 )
                cout << i/2 +1 << " ";
        }
    }

    return 0;
}
