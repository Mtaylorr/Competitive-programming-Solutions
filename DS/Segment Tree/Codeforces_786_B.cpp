//https://codeforces.com/contest/786/problem/B

#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e5 + 5;
const int MOD = 1e9 + 7 ;

int n,q,s;

ll dist[4*N+1];
bool vis[N];
vector<int> query[4*N+1];
int t[N], l[N], r[N],w[N],v[N];
set<pair<ll,int> > dq;
bool visN[N];
ll distD[N];

void init(int id=0, int ns=0,int ne=n-1){
    if(ns==ne){
        dist[id]=1e17;
        distD[ns]=1e17;
        return ;
    }
    int ln = 2*id+1;
    int rn =ln+1;
    int md = ns+(ne-ns)/2;
    init(ln, ns, md);
    init(rn, md+1,ne);
    dist[id]=max(dist[ln], dist[rn]);
}

void updDist(int qs, int qe, ll v, int id=0, int ns=0, int ne=n-1){
    if(qs>ne || qe<ns)
        return ;
    if(v>dist[id])
        return ;
    if(ns==ne){
        dist[id]=v;
        distD[ns]=v;
        dq.insert({v,ns});
        return ;
    }
    int ln = 2*id+1;
    int rn =ln+1;
    int md = ns+(ne-ns)/2;
    updDist(qs, qe, v, ln, ns, md);
    updDist(qs, qe, v, rn , md+1, ne);
    dist[id]=max(dist[ln], dist[rn]);
}


void addQuery(int qs, int qe, int v, int id=0, int ns=0, int ne=n-1){
    if(qs>ne || qe<ns)
        return ;
    if(qs<=ns && qe>=ne){
        query[id].pb(v);
        return ;
    }
    int ln = 2*id+1;
    int rn =ln+1;
    int md = ns+(ne-ns)/2;
    addQuery(qs, qe, v, ln, ns,md);
    addQuery(qs, qe, v, rn, md+1, ne);
}

void apply(int i, int u){
    if(t[i]==1){
        ll x = distD[u];
        updDist(r[i],r[i],x+w[i]);
    }else if(t[i]==2){
        ll x = distD[u];
        updDist(l[i],r[i],x+w[i]);
    }else{
        ll x = distD[u];
        updDist(v[i],v[i],x+w[i]);
    }
}

void applyQuery(int p, int id=0, int ns=0, int ne=n-1){
    if(ns>p || ne<p)
        return ;
    for(auto u:query[id]){
        if(vis[u])
            continue;
        apply(u,p);
        vis[u]=1;
    }
    query[id].clear();

    if(ns==ne)
        return ;
    int ln = 2*id+1;
    int rn =ln+1;
    int md = ns+(ne-ns)/2;
    applyQuery(p, ln, ns,md);
    applyQuery(p, rn, md+1, ne);
}
bool cmp(int a, int b){
    return w[a]<w[b];
}

int main(){
    freopen("input.txt", "r",stdin);
    scanf("%d%d%d",&n,&q,&s);
    s--;
    init();
    for(int i=0;i<q;i++){
        scanf("%d",&t[i]);
        if(t[i]==1){
            scanf("%d%d%d",&l[i],&r[i],&w[i]);
            r[i]--,l[i]--;
            addQuery(l[i],l[i],i);
        }else if(t[i]==3){
            scanf("%d%d%d%d",&v[i],&l[i],&r[i],&w[i]);
            l[i]--,r[i]--,v[i]--;
            addQuery(l[i],r[i],i);
        }else{
            scanf("%d%d%d%d",&v[i],&l[i],&r[i],&w[i]);
            l[i]--,r[i]--,v[i]--;
            addQuery(v[i],v[i],i);
        }
    }
    for(int i=0;i<=4*n;i++){
        sort(query[i].begin(),query[i].end(),cmp);
    }
    updDist(s,s,0);
    pair<ll,int> r;
    while(dq.size()){
        r=*dq.begin();
        dq.erase(dq.begin());
        int u=  r.se;
        ll d = r.fi;
        if(visN[u])
            continue;
        visN[u]=1;
        applyQuery(u);
    }
    for(int i=0;i<n;i++){
        if(distD[i]<1e17)
            printf("%lld ", distD[i]);
        else
            printf("-1 ");
    }
    return 0;
}
