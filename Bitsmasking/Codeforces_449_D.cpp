//https://codeforces.com/problemset/problem/449/D
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1048576 + 5;
const int MOD = 1e9 +7 ;

int mul(int u , int v, ll mod=MOD){
	return ((u%mod)*1ll*(v%mod))%mod;
}
int add(int u, int v, ll mod=MOD){
	return ((u%mod)+0ll+(v%mod)+mod)%mod;
}

int sub(int u, int v , ll mod=MOD){
	return ((u%mod)+0ll-(v%mod)+mod)%mod;
}

int a[N];
int freq[N];
int n;
int dp[N];

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

int BitCount(int x){
    int rs=0;
    while(x){
        rs+=(x%2);
        x/=2;
    }
    return rs;
}

int main()
{
    freopen("input.txt", "r",stdin);
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
        freq[a[i]]++;
    }

    for(int i=0;i<(1<<20);i++){
        dp[i]=freq[i];
    }
    for(int i=0;i<20;i++){
        for(int mask=0;mask<(1<<20);mask++){
            if(!(mask&(1<<i))){
                dp[mask]+=dp[mask+(1<<i)];

            }
        }
    }
    int ans=0;
    for(int i=0;i<(1<<20);i++){
        int x = BitCount(i);
        if(x%2){
            ans=sub(ans, powe(2,dp[i]));
        }else{
            ans=add(ans, powe(2,dp[i]));
        }
    }
    cout << ans;

    return 0;

}
