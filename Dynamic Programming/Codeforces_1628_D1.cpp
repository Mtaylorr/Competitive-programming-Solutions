//https://codeforces.com/problemset/problem/1628/D1
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 3e5 +5 ;
const int MOD = 1e9 + 7 ;

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



int dp[2005][2005];
int n,k,m,t;
int inv2 = inv(2);


int main(){
    freopen("input.txt", "r",stdin);
    for(int i=1;i<=2000;i++){
        dp[i][i]=i;
        for(int j=i+1;j<=2000;j++){
            int k1= dp[i][j-1];
            int k2 = dp[i-1][j-1];
            dp[i][j]=add(k2,mul(sub(k1,k2),inv2));
        }
    }

    scanf("%d",&t);
    while(t--){
        scanf("%d%d%d",&n,&m,&k);
        int res = dp[m][n];
        res=mul(res, k);
        printf("%d\n",res);
    }
    return 0;
}
