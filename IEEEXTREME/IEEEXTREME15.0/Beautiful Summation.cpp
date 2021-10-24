//46.67%
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;


const int N = 1e6 +5 ;
const int MOD = 1e9 + 7;

ll n,m,p,q;

ll mul(ll u , ll v, ll mod=m){
    return ((u%mod)*(v%mod))%mod;
}
ll add(ll u, ll v, ll mod=m){
    return ((u%mod)+(v%mod)+mod)%mod;
}

ll sub(ll u, ll v , ll mod=m){
    return ((u%mod)-(v%mod)+mod)%mod;
}
ll powe(ll u, ll v, ll mod=m){
    if(u==0)
        return 0;
    ll ans=1;
    ll acc=u;
    while(v){
        if(v%2){
            ans=mul(ans,acc,mod);
        }
        acc = mul(acc,acc,mod);
        v/=2;
    }
    return ans;
}


ll getinv(ll u){
    for(int i=1;i<=m;i++){
        if(mul(u,i,m)==1)
            return i;
    }
    return 1;
}
int main(){
//    freopen("input.txt", "r", stdin);

    cin >> p >> q >> n >> m;
    if(n<=1e6){
        ll res=0;
        ll cur=1;
        for(int i=1;i<=n;i++){
            cur=mul(cur,p,m);
            ll x = mul(cur, powe(i,q,m),m);
            res=add(res,x,m);
        }
        cout << res << endl;
        return 0;
    }
    ll res=0;
    ll cyclesum = 0;
    ll cur=1;
    for(int i=0;i<m;i++){
        int x = mul(cur, powe(i,q,m),m);
        cyclesum=add(cyclesum,x,m);
        cur=mul(cur,p,m);
    }

    ll X = cur;
    ll u = (n+1)/m;
    ll y = 0;
    ll z = 1;
    for(int i=0;i<u;i++){
        y=add(y,z ,m);
        z=mul(z, X,m);
    }
    ll ans = mul(cyclesum, y, m);
    cur = powe(p, (u)*m,m);
    for(int i=u*m;i<=n;i++){
        ll x = mul(cur, powe(i%m,q,m),m);
        ans=add(ans,x,m);
        cur=mul(cur,p,m);
    }
    cout << ans << endl;

    return 0;
}
