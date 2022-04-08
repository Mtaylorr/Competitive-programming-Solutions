#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e5 + 5, E = 2*(5e5)+5;
const int MOD = 1e9 + 7 ;

#define neig(u,e,v) for(int e=head[u],v;(~e)&&(v=to[e],1);e=nxt[e])

int nxt[E],head[N],to[E], w[E],edgcnt=0;

int n,m;
int x,y,z;
bool vis[N];
int dist[3][N];
map<int,vector<int> > d1;
int tree[3*N];
bool isUseless[N];
set<int> distinct;
int cn=1;
map<int,int> code;

void upd(int x, int v){
    for(;x<=cn;x+=(x)&(-x)){
        tree[x]=min(tree[x],v);
    }
}

int get(int x){
    int rs=1e9;
    for(;x;x-=(x)&(-x)){
        rs=min(rs, tree[x]);
    }
    return rs;
}

void inittree(){
    for(int i=0;i<=cn;i++){
        tree[i]=1e9;
    }
}



void addEdge(int u, int v, int we){
    nxt[edgcnt]=head[u];
    to[edgcnt]=v;
    w[edgcnt]=we;
    head[u]=edgcnt++;
}

void addBiEdge(int u, int v, int w){
    addEdge(u,v,w);
    addEdge(v,u,w);
}


void dijk(int src){
    for(int i=0;i<n;i++){
        dist[src][i]=1e9;
        vis[i]=0;
    }
    dist[src][src]=0;
    set<pair<int,int> > dq ;
    dq.insert({0,src});
    pair<int,int> p;
    while(!dq.empty()){
        p=*dq.begin();
        dq.erase(dq.begin());
        int u = p.se;
        int d = p.fi;
        if(vis[u])
            continue;
        vis[u]=1;
        neig(u,e,v){
            if(vis[v])
                continue;
            if(dist[src][v]>d+w[e]){
                dist[src][v]=d+w[e];
                dq.insert({d+w[e],v});
            }
        }

    }
}
int main()
{
    freopen("input.txt", "r",stdin);
    memset(head, -1, sizeof(head));
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++){
        scanf("%d%d%d",&x,&y,&z);
        addBiEdge(x,y,z);
    }
    for(int i=0;i<3;i++){
        dijk(i);
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<3;j++)
            distinct.insert(dist[j][i]);
    }
    for(auto u:distinct){
        code[u]=cn++;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<3;j++)
            dist[j][i]=code[dist[j][i]];
    }
    for(int j=0;j<3;j++){
        d1.clear();
        for(int i=0;i<n;i++){
            d1[dist[j][i]].pb(i);
        }
        inittree();
        for(auto &p:d1){
            for(auto &u:p.se){
                int x = get(dist[(j+1)%3][u]);

                if(x<=dist[(j+2)%3][u]){
                    isUseless[u]=1;
                }
            }

            for(auto &u:p.se){
                upd(dist[(j+1)%3][u],dist[(j+2)%3][u]);
            }
        }
    }
    int rs=n;
    for(int i=0;i<n;i++){
        rs-=isUseless[i];
    }
    cout << rs;

    return 0;

}
