//https://www.spoj.com/problems/GOODG/
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e6 +5 ;
const int MOD = 998244353 ;


int n;
int a,d;

pair<ll,ll> tree[4*N];

ll sub(const pair<ll,ll> & line , ll x){
    return line.fi*x + line.se;
}

double intersect(const pair<ll,ll> & a,const pair<ll,ll> & b){
    return (a.se-b.se+0.0)/(b.fi-a.fi+0.0);
}


void ins(pair<ll,ll>  line , int id=0, int ns=1, int ne=n+1){
    if(line.fi == tree[id].fi){
        if(sub(line,ns)>sub(tree[id],ns)){
            tree[id]=line;
        }
        return ;
    }
    if(ns==ne){
        if(sub(line,ns)>sub(tree[id],ns)){
            tree[id]=line;
        }
        return ;
    }
    int md = ns+(ne-ns)/2;
    double x = intersect(line, tree[id]);
    if(x<ns || x>ne){
        if(sub(line,md)>sub(tree[id],md)){
            tree[id]=line;
        }
        return ;
    }
    if(x<=md){
        if(sub(line,ne)>sub(tree[id],ne)){
            swap(tree[id],line);
        }
        ins(line, 2*id+1, ns, md);
    }else{
        if(sub(line,ns)>sub(tree[id],ns)){
            swap(tree[id],line);;
        }
        ins(line, 2*id+2, md+1,ne);
    }
}

ll query(ll x, int id=0, int ns=1, int ne=n+1){
    if(ns>x || ne<x)
        return -1e18;
    ll rt = sub(tree[id],x);
    if(ns==ne){
        return rt;
    }
    int md = ns+(ne-ns)/2;
    rt=max(rt, query(x, 2*id+1, ns, md));
    rt=max(rt, query(x, 2*id+2, md+1, ne));
    return rt;
}


int main(){
    freopen("input.txt", "r",stdin);
    scanf("%d",&n);
    ll r=0;
    for(int i=1;i<=n;i++){
        scanf("%d%d",&a,&d);
        d*=-1;
        ll z = max(query(i),0ll)+a;
        z=max(z,0ll);
        r=z;
        ll  m = z-i*1ll*d;
        ll c = d;
        ins({c,m});
    }
    r=query(n+1);
    printf("%lld\n",query(n+1));

    return 0;
}

