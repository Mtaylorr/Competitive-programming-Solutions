//https://vjudge.net/problem/UVA-1106
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 +5 ;
const int MOD = 998244353 ;

int n,days;
ll b[N],d[N],s[N],sorted[N],p[N];
ll dp[N];

ll sub(const pair<ll,ll> &line, ll x){
    return line.fi*x + line.se;
}

double intersect(const pair<ll,ll> &a, const pair<ll,ll> &b){
    return (b.second-a.second+0.0)/(a.first-b.first+0.0);//(c2-c1)/(m1-m2);
}

struct node{
    node *l,*r;
    pair<ll,ll>  line;
    node(){
        l=r=NULL;
        line={0,0};
    };
}*root;
void ins(pair<ll,ll> line,node*&cur=root, int ns=0, int ne=days+1){
    if(cur==NULL){
        cur =new node();
    }
    if(line.first==cur->line.first){
        cur->line=max(line, cur->line);
        return ;
    }
    double x = intersect(line , cur->line);
    if(x<ns || x>ne){
        if(sub(line,ns)>sub(cur->line, ns)){
           cur->line=line;
        }
        return ;
    }
    int md = ns+(ne-ns)/2;
    if(x<=md){
        if(sub(line,ne)>sub(cur->line, ne)){
           swap(line, cur->line);
        }
        ins(line, cur->l, ns, md);
    }else{
        if(sub(line,ns)>sub(cur->line, ns)){
           swap(line, cur->line);
        }
        ins(line, cur->r, md+1, ne);
    }
}

long long query(int x, node*&cur=root, int ns=0, int ne=days+1){
    if(x<ns || x>ne || cur==NULL)
        return -1e18;
    long long ret = sub(cur->line,x);
    if(ns==ne)
        return ret;
    int md = ns+(ne-ns)/2;
    ret=max(ret,query(x, cur->l, ns, md) );
    ret=max(ret, query(x, cur->r, md+1, ne));
    return ret;
}


int main(){
    freopen("input.txt", "r",stdin);
    int ii=0;
    while(~scanf("%d%lld%d",&n,&s[0],&days),n||s[0]||days){
        for(int i=1;i<=n;i++){
            scanf("%lld%lld%lld%lld",&d[i],&b[i],&s[i],&p[i]);
            sorted[i]=i;
        }
        sort(sorted+1, sorted+n+1,[](int a , int b){return d[a]<d[b];});
        d[n+1]=days+1;
        dp[0]=0;
        sorted[n+1]=n+1;
        root=NULL;
        ins({0,s[0]});
        for(int i=1;i<=n+1;i++){
            int cur  = sorted[i];
            ll &r = dp[cur];
            r=0;
            long long x = d[cur];

            r = query(x);
            if(r<b[cur])
                continue;
            long long c = dp[cur]-b[cur] + s[cur] + - d[cur]*p[cur]-p[cur];
            ins({p[cur],c});
        }
        printf("Case %d: %lld\n",++ii, dp[n+1]);
    }
    return 0;
}

