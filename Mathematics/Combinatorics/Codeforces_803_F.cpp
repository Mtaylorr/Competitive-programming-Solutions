//https://codeforces.com/problemset/problem/803/F

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = (3e5) + 100, M = 1000 + 5, E = 2e6 + 5;
const int MOD = 1e9 + 7;
const double eps = 1e-7;

int mul(int u , int v, int mod=MOD){
    return ((u%mod)*1ll*(v%mod))%mod;
}
int add(int u, int v, int mod=MOD){
    return ((u%mod)+0ll+(v%mod)+mod)%mod;
}

int sub(int u, int v , int mod=MOD){
    return ((u%mod)+0ll-(v%mod)+mod)%mod;
}

int powe(int u, int v, int mod=MOD){
    int ans=1;
    int acc=u;
    while(v){
        if(v%2){
            ans=mul(ans,acc,mod);
        }
        acc = mul(acc,acc,mod);
        v/=2;
    }
    return ans;
}

int n, a,freq[N];
int dp[N];

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> a;
        for(int j=1;j*j<=a;j++){
            if(a%j==0){
                freq[j]++;
                if(j*j!=a){
                    freq[a/j]++;
                }
            }
        }
    }
    for(int i=1e5;i>=1;i--){
        dp[i]=sub(powe(2, freq[i]),1);
        for(int j=2*i;j<=1e5;j+=i){
            dp[i]=sub(dp[i], dp[j]);
        }
    }
    cout << dp[1];


    return 0;

}
