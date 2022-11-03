//https://codeforces.com/problemset/problem/484/D
//Mtaylor 
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define fi first
#define se second
#define mp make_pair
#define endl '\n';
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
void dbg_out() {cerr<<endl;}
template<typename Head, typename... Tail>
void dbg_out(Head H, Tail... T){cerr << ' '<<H;dbg_out(T...);}
#define dbg(...) cerr << "(" << #__VA_ARGS__<<"):", dbg_out(__VA_ARGS__)
typedef long long ll;
const int N = 1e6 + 5;

int n;
ll dp[N];
ll a[N];
void solve(){
    cin >> n;
    for(int i=1;i<=n;i++){
        cin>> a[i];
    }
    dp[1]=0;
    ll dpl = -a[1];
    ll dpu = +a[1];
    ll mxdp=0;
    for(int i=2;i<=n;i++){
        dp[i]=dp[i-1];
        dp[i]=max(dp[i], a[i]+dpl);
        dp[i]=max(dp[i], dpu-a[i]);
        mxdp=max(mxdp, dp[i-1]);
        dpl=max(dpl, mxdp-a[i]);
        dpu=max(dpu, mxdp+a[i]);
    }
    cout << dp[n];
}

int main() {
    //freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    //cin >>T;
    T=1;
    while(T--){
        solve();
    }
    return 0;
}
