//https://www.spoj.com/problems/GOT/
#include <bits/stdc++.h>
 
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl ;
typedef pair<ll,ll> pl;
 
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(),(v).rend()
#define max(a,b) (a>b ? a : b)
#define min(a,b) (a<b ? a : b)
#define FAST ios::sync_with_stdio(0), cin.tie(0),cout.tie(0)
 
const int MOD = (int)7+(int)1e9 ;
const int N = 1000005;
const double PI =4*atan(1);
const double eps = 1e-10;
const long long oo = 1e10;
const int K = 26;
 
 
int qe[N],qs[N],qi[N],qv[N],val[N],qlca[N];
int n,m;
int ans[N];
int l,r;
int st[N],et[N];
vector<int> a;
int occ[N],freq[N];
 
void change(int cur){
    occ[cur]^=1;
    
    if(occ[cur]){
        freq[val[cur]]++;
    }else{
        freq[val[cur]]--;
    }
    //cout << cur << " " << val[cur] << " " << freq[val[cur]] << endl;
}
 
void update(int cur){
    while(r<qe[cur])
        change(a[++r]);
    while(l>=qs[cur])
        change(a[--l]);
    while(r>qe[cur])
        change(a[r--]);
    while(l<qs[cur])
        change(a[l++]);
}
 
void mo()
{
    int bs = sqrt(2*n);
    sort(qi,qi+m,[bs](int a, int b){return mp(qs[a]/bs,qe[a])<mp(qs[b]/bs,qe[b]);});
    l=0;
    r=-1;
    for(int i=0;i<m;i++){
        int cur = qi[i];
        freq[val[qlca[cur]]]++;
        update(cur);
    	//cout << freq[qv[cur]] << endl;
        ans[cur]=(freq[qv[cur]]>0);
        freq[val[qlca[cur]]]--;
    }
}
vector<vector<int> > adj;
vector<int> depth, node2ind,ind2node;
 
 
void init()
{
    for(int i=0;i<=n;i++){
        occ[i]=freq[i]=0;
    }
    adj.clear();
    adj.resize(n+1);
    depth.resize(n+1);
    node2ind.resize(n+1);
    ind2node.clear();
}
void dfs(int u,int dpth=0,int p=0)
{
    node2ind[u]=ind2node.size();
    ind2node.push_back(u);
    depth[u]=dpth;
    st[u]=a.size();
    a.pb(u);
    for(int v:adj[u])
    {
        if(v==p)
            continue;
        dfs(v,dpth+1,u);
        ind2node.push_back(u);
    }
    et[u]=(a.size());
    a.pb(u);
}
int lgs[int(2e5)+5];
int spt[int(2e5)+5][20];
void buildSpt()
{
    lgs[0]=-1;
    for(int i=0;i<ind2node.size();i++)
    {
        spt[i][0]=i;
        lgs[i+1]=lgs[i]+!(i&(i+1));
    }
    for(int j=1;(1<<j)<=ind2node.size();j++)
    {
        for(int i=0;i+(1<<j)<=ind2node.size();i++)
        {
            int a=spt[i][j-1];
            int b=spt[i+(1<<(j-1))][j-1];
            spt[i][j]=(depth[ind2node[a]]<depth[ind2node[b]])?a:b;
        }
    }
}
 
int SPTRMQ(int a,int b)
{
    int sz=b-a+1;
    int lg=lgs[sz];
    a=spt[a][lg];
    b=spt[b-(1<<lg)+1][lg];
    return (depth[ind2node[a]]<depth[ind2node[b]])?a:b;
}
int SPTLCA(int u,int v)
{
    int a=node2ind[u];
    int b=node2ind[v];
    if(a>b)
        swap(a,b);
    return ind2node[SPTRMQ(a,b)];
}
int u,v,w;
int main(){
    while(cin>> n){
        init();
        scanf("%d",&m);
        for(int i=1;i<=n;i++){
            scanf("%d",val+i);
        }
        for(int i=0;i<n-1;i++){
            scanf("%d %d",&u,&v);
            adj[u].pb(v);
            adj[v].pb(u);
        }
        dfs(1);
        buildSpt();
        for(int i=0;i<m;i++){
            scanf("%d%d%d",&u,&v,&w);
            qi[i]=i;
            if(st[u]>st[v])swap(u,v);
            qlca[i]=SPTLCA(u,v);
            if(qlca[i]==u){
                qs[i]=st[u];
                qe[i]=st[v];
            }else{
                qs[i]=et[u];
                qe[i]=st[v];
            }
            qv[i]=w;
        }
       
        mo();
        for(int i=0;i<m;i++){
            if(ans[i])printf("Find\n");
            else printf("NotFind\n");
        }
    }
 
 
    return 0;
} 
