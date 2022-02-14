//https://codeforces.com/contest/559/problem/C
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 3e5 + 5;
const int MOD = 1e9 + 7 ;

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

int h,w,n,x,y;
vector<pair<int,int> > v;
int dp[N];

int main(){
    freopen("input.txt", "r",stdin);
    init(200002);
    scanf("%d%d%d",&h,&w,&n);
    for(int i=0;i<n;i++){
        scanf("%d%d",&x,&y);
        v.pb({x,y});
    }
    sort(v.begin(),v.end());
    for(int i=0;i<n;i++){
        pair<int,int> u = v[i];
        dp[i]=cnk(u.fi+u.se-2, u.fi-1);
        for(int j=0;j<i;j++){
            if(u.fi>=v[j].fi && u.se>=v[j].se){
                int dw = u.se-v[j].se;
                int dh = u.fi-v[j].fi;
                dp[i]=sub(dp[i], mul(dp[j],cnk(dw+dh,dw)));
            }
        }
    }
    int ans = cnk(h+w-2,h-1);
    for(int j=0;j<n;j++){
        int dw = w-v[j].se;
        int dh = h-v[j].fi;
        ans=sub(ans, mul(dp[j],cnk(dw+dh,dw)));
    }
    printf("%d\n",ans);

    return 0;
}
