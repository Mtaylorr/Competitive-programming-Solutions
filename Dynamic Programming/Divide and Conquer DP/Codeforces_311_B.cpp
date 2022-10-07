//https://codeforces.com/contest/311/problem/B
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = (1e5) + 100, M = 1000 + 5, E = 2e6 + 5;
const int MOD = 1e9 + 7;
const double eps = 1e-7;

int n,p,m;
ll dp[2][N];
ll d[N];
ll h,t;
vector<ll> vals;
ll sum[N];

void compute(int id, int l, int r, int optl, int optr){
    if(l>r)
        return ;
    int md = (l+r)/2;
    pair<ll,int> best = {LLONG_MAX, -1};
    for(int k=optl;k<=min(md, optr);k++){
        ll c = vals[md]*(md-k) -(sum[md-1]-(k>0?sum[k-1]:0));
        best = min(best, {(k ? dp[id^1][k - 1] : 0) +c, k});
    }
    dp[id][md]=best.first;
    int opt =best.second;
    compute(id, l, md-1, optl, opt);
    compute(id, md+1, r, opt, optr);
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m >> p;
    for(int i=1;i<n;i++){
        cin >> d[i];
        d[i]+=d[i-1];
    }
    ll ans=0;
    for(int i=0;i<m;i++){
        cin >> h >> t;
        ll x = t-d[h-1];
        vals.pb(x);
    }

    sort(vals.begin(),vals.end());
    sum[0]=vals[0];
    for(int i=1;i<m;i++){
        sum[i]=vals[i]+sum[i-1];
    }
    ll sm=0;
    for(int i=0;i<m;i++){
        dp[1][i]=vals[i]*i -sm;
        sm+=vals[i];
    }
    ll res=dp[1][m-1];
    for(int i=2;i<=p;i++){
        int id = i&1;
        compute(id, 0,m-1, 0,m-1);
        res=min(res, dp[id][m-1]);
    }
    cout << res << endl;

    return 0;

}
