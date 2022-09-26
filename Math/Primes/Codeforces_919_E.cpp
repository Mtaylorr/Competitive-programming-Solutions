//https://codeforces.com/problemset/problem/919/E
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 1e6 + 5, M=1000 +5,E = 1e6 +5 ;
const int MOD = 1e9 + 7  ;
const double eps = 1e-7;

ll mul(ll u , ll v, ll mod=MOD){
    return ((u%mod)*(v%mod))%mod;
}
ll add(ll u, ll v, ll mod=MOD){
    return ((u%mod)+(v%mod)+mod)%mod;
}

ll sub(ll u, ll v , ll mod=MOD){
    return ((u%mod)-(v%mod)+mod)%mod;
}

ll powe(ll u, ll v, ll mod=MOD){
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
ll  inv(ll u,ll mod=MOD){
    return powe(u,mod-2,mod);
}


int a,b,p;
ll z;
int po[N];
int minans[N];

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    memset(minans, -1, sizeof(minans));
    cin >> a >> b >> p >> z;
    po[0]=1;
    int l=1;
    int invb = inv(b,p);
    minans[1]=0;
    for(int i=1;i<=p-1;i++){
        po[i]=mul(po[i-1],a,p);
        if(po[i]==1){
            l=i;
            break;
        }
        ll x = inv(po[i],p);
        if(minans[x]==-1){
            minans[x]=i;
        }
    }
    ll ans=0;
    for(int i=1;i<=p-1;i++){
        ll x = mul(i,invb,p);
        if(minans[x]==-1){
            continue;
        }

        ll y = minans[x];
        if(y>i){
            y-=((i-y)/l)*l;
        }else if(y<i){
            y+=((i-y+l-1)/l)*l;
        }
        ll pas = l*1ll*p;
        y = (y-i)*1ll*p+i;
        if(y<=z){
            ans+=(z-y)/pas +1;
        }
    }
    cout << ans;
    return 0;
}
