//100%
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

#define neig(u,v,e) for(int e=head[u],v;(e!=-1) && (v=to[e],1); e=nxt[e])

const int N = 2e5 +5 ;

int t;
int head[N], nxt[N], to[N], cst[N], col[N];
int n,m,k;
int u,v,d;
char c;
int edgcnt;
int chngcolor;

void init(){
    edgcnt=0;
    memset(head, -1, n*sizeof(head[0]));
}

void addEdge(int a , int b, int d , int c){
    nxt[edgcnt]=head[a];
    head[a]=edgcnt;
    to[edgcnt]=b;
    cst[edgcnt]=d;
    col[edgcnt]=c;
    edgcnt++;
}

void addBiEdge(int a , int b, int d , int c){
    addEdge(a,b,d,c);
    addEdge(b,a,d,c);
}

ll dist[N][5];
bool vis[N][5];
void dijk(){
    for(int i=0;i<n;i++){
        for(int j=0;j<5;j++){
            dist[i][j]=1e18;
            vis[i][j]=0;
        }
    }
    dist[0][0]=0;
    set<pair<ll,pair<int,int> > > pq;
    pq.insert({0,{0,0}});
    pair<ll,pair<int,int> > p ;
    while(!pq.empty()){
        p=*pq.begin();
        pq.erase(pq.begin());
        int u = p.second.first;
        int co = p.second.second;
        ll d = p.first;
        if(vis[u][co])
            return ;
        vis[u][co]=1;
        neig(u,v,e){
            ll newdist = chngcolor*(col[e]!=co) + cst[e]+dist[u][co];
            if(dist[v][col[e]]>newdist){
                dist[v][col[e]]=newdist;
                pq.insert({dist[v][col[e]], {v, col[e]}});
            }
        }
    }
}

bool ok(int c){
    chngcolor=c;
    dijk();
    ll dis = 1e18;
    for(int i=0;i<5;i++){
        dis=min(dis, dist[n-1][i]);
    }
    return dis<=k;
}



int main(){
    //freopen("input.txt", "r", stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%d%d%d",&n,&m,&k);
        init();
        for(int i=0;i<m;i++){
            cin >> u >> v >> d >> c;
            u--;v--;
            addBiEdge(u,v,d,c-'a');
        }
        ll l= -10;
        ll r= 1e10;
        while(l<r-1){
            ll md = (l+r)/2;
            if(ok(md)){
                l=md;
            }else{
                r=md;
            }
        }
        int ans=l;
        if(ok(r))
            ans=r;
        if(ans<=0){
            puts("impossible");
        }
        else if(ans>1e9){
            puts("relaxing");
        }else{
            cout << ans << endl;
        }
    }
    return 0;
}
