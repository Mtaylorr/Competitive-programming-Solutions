//https://codeforces.com/contest/1717/problem/E
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5, E = 1 << 17;
const int MOD =  1e9 + 7;

ll fact[N];
ll invfact[N];

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

void init_fact(ll n, ll mod=MOD){
    fact[0]=fact[1]=1;
    for(int i=2;i<=n;i++){
        fact[i]=mul(i,fact[i-1],mod);
    }
}

ll cnk (ll n , ll k){
    if(k>n)return 0;
    if(n==0)return 1;
    ll ans = mul(fact[n],invfact[k]);
    ans= mul(ans,invfact[n-k]);
    return ans;
}

void init_inv_fact(ll n, ll mod=MOD){
    for(int i=0;i<=n;i++){
        invfact[i]=powe(fact[i],mod-2,mod);
    }
}
void init(ll n, ll mod=MOD){
    init_fact(n,mod);
    init_inv_fact(n,mod);
}


int n;
int sum[N];
int mob[N];
int invd[N];
vector<int> divs;

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i=1;i<=n;i++){
        int m = 1;
        int y=i;
        for(int j=2;j*j<=y;j++){
            int x=0;
            while(y%j==0){
                y/=j;
                x++;
            }
            if(x>=2){
                m=0;
            }else if(x==1){
                m*=-1;
            }
        }
        if(y!=1){
            m*=-1;
        }
        mob[i]=m;
    }
    for(int i=2;i<=n;i++){
        sum[i]=0;
        for(int j=1;j*j<=i;j++){
            if(i%j)
                continue;
            int x = j;
            sum[i]=add(sum[i],mob[x]*((i/x)-1));
            if(j*j!=i){
                x=i/j;
                sum[i]=add(sum[i],mob[x]*((i/x)-1));
            }
        }
    }
    int ans=0;
    for(int c=1;c<=n-2;c++){
        invd[c]=inv(c);
        int z = n-c;
        for(int j=1;j*j<=(z);j++){
            if(z%j)
                continue;
            int x = j;
            int d= __gcd(x,c);
            ans=add(ans, mul(mul(c,x),mul(sum[z/x], invd[d])));
            if(j*j!=z){
                x = z/j;
                int d= __gcd(x,c);
                ans=add(ans, mul(mul(c,x),mul(sum[z/x], invd[d])));
            }
        }
    }
    cout << ans << endl;
    return 0;
}
