//https://codeforces.com/contest/935/problem/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 1e5 + 100, M = 1000 + 5, E = 1e6 + 5;
const int MOD = 1e9 + 7;
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

int dp[N];
int a[N];
int b[N];
int n,m;
int invm;
int inv2;



int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin  >> n >> m;
    invm = inv(m);
    inv2 = inv(2);
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    for(int i=0;i<n;i++){
        cin >> b[i];
    }
    dp[n]=0;
    for(int i=n-1;i>=0;i--){
        if(a[i]!=0 && b[i]!=0){
            if(a[i]>b[i]){
                dp[i]=1;
            }else if(a[i]<b[i]){
                dp[i]=0;
            }else{
                dp[i]=dp[i+1];
            }
        }else if(a[i]!=0){
            dp[i] = mul((a[i]-1), invm);
            dp[i] = add(dp[i],mul(invm, dp[i+1]));
        }else if(b[i]!=0){
            dp[i] = mul((m-b[i]), invm);
            dp[i] = add(dp[i],mul(invm, dp[i+1]));
        }else{
            dp[i]=mul(invm, dp[i+1]);
            int x = mul((m), (m-1));
            x=mul(x, inv2);
            x=mul(x, invm);
            x=mul(x, invm);
            dp[i]=add(dp[i],x);
        }
    }
    cout << dp[0];
    return 0;

}
