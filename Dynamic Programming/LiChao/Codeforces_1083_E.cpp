//https://codeforces.com/problemset/problem/1083/E
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e6 + 5;
const int MOD = 1e9 +7 ;

ll sub(const pair<ll,ll> &line, ll x){
    return line.fi*x + line.se;
}

double intersect(const pair<ll,ll> &a, const pair<ll,ll> & b){
    return (b.se-a.se+0.0)/(a.fi-b.fi+0.0);
}

struct node{
    node *l,*r;
    pair<ll,ll> line;
    node(){
        l=r=NULL;
        line={0,0};
    }
}*root;

void ins(pair<ll,ll> line , node *&cur=root, int ns=0, int ne=1e9){
    if(cur==NULL){
        cur=new node();
    }
    if(line.fi==cur->line.first){
        cur->line = max(line, cur->line);
        return ;
    }
    double x = intersect(line , cur->line);
    if(x<ns || x>ne){
        if(sub(line, ns)>sub(cur->line, ns)){
            cur->line = line;
        }
        return ;
    }
    if(ns==ne)
        return ;
    int md = ns+(ne-ns)/2;
    if(x<=md){
        if(sub(line , ne)>sub(cur->line, ne)){
            swap(line, cur->line);
        }
        ins(line, cur->l ,ns, md);
    }else{
        if(sub(line, ns)>sub(cur->line,ns)){
            swap(line, cur->line);
        }
        ins(line, cur->r, md+1, ne);
    }
}
long long query(ll x, node*&cur=root, int ns=0, int ne=1e9){
    if(x<ns || x>ne || cur==NULL){
        return -1e18;
    }
    long long rt = sub(cur->line, x);
    if(ns==ne)
        return rt;
    int md = ns+(ne-ns)/2;
    rt=max(rt, query(x, cur->l, ns, md));
    rt=max(rt, query(x,cur->r, md+1,ne));
    return rt;
}

vector<int> ord;
int n;
ll x[N], y[N], a[N];

int main()
{
    //ios::sync_with_stdio(0);
    freopen("input.txt", "r",stdin);
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%lld%lld%lld",&x[i],&y[i],&a[i]);
        ord.pb(i);
    }
    ins({0,0});
    sort(ord.begin(), ord.end(), [](int a, int b){return y[a]<y[b];});
    ll ans=0;
    for(auto i:ord){
        ll rs = query(x[i]);
        ll dp = x[i]*y[i]-a[i]+rs;
        ans=max(ans,dp);
        ins({-y[i], dp});
    }
    printf("%lld\n",ans);
    return 0;

}
