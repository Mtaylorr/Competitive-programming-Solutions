//https://codeforces.com/problemset/problem/494/B
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 2e5 + 5, M=1000 +5,E = 1e6 +5 ;
const int MOD = 1e9 + 7   ;
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

int tree[N];



string s,t;
int n;
int m;
int isbegin[N];
int z[N];

int dp[N];

void upd(int x, int v){
    for(;x<=n;x+=(x)&-(x)){
        tree[x]=add(tree[x],v);
    }
}

int get(int x){
    int rs=0;
    for(;x;x-=(x)&-(x)){
        rs=add(rs,tree[x]);
    }
    return rs;
}

void Z_algo(){
    z[0]=0;
    int l=1,r=1;
    for(int i=1;i<n+m+1;i++){
        if(z[i-l]+i<r){
            z[i]=z[i-l];
        }else{
            l=i;
            r=max(r,i);
            while(r<(n+m+1) && t[r-l]==t[r]){
                r++;
            }
            z[i]=r-l;
        }
    }
}


int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> s;
    cin >> t;
    n=s.size();
    m=t.size();
    t+='#';
    t+=s;
    Z_algo();
    for(int i=m+1;i<n+m+1;i++){
        if(z[i]>=m){
            isbegin[i-(m+1)+1]=1;
        }
    }
    ll ans=0;
    for(int i=n;i>=1;i--){
        if(isbegin[i]){
            dp[i]=add(dp[i], sub(get(n),get(i+m-1)));
            dp[i]=add(dp[i],n-(i+m-1)+1);
        }else{
            dp[i]=dp[i+1];
        }

        ans=add(ans, dp[i]);
        upd(i, ans);
    }
    cout << ans;

    return 0;
}
