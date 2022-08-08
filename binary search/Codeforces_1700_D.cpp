//https://codeforces.com/problemset/problem/1700/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5 , E = 2e6 + 5;
const int MOD = 1e9 + 7 ;

int n;
ll t;
int q;
ll v[N];
ll sum;
ll dp[N];

bool ok( ll u, ll t){
    ll q = u*t;
    return q>=sum && t>=dp[u];
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> v[i];
        sum+=v[i];
    }
    dp[1]=v[1];
    ll cur_sum=v[1];
    for(int i=2;i<=n;i++){
        ll q = (i)*(dp[i-1]) - cur_sum;
        if(q>=v[i]){
            dp[i]=dp[i-1];
        }else{
            dp[i]=dp[i-1]+((v[i]-q+i-1)/(i));
        }
        cur_sum+=v[i];
    }
    cin >> q;
    while(q--){
        cin >> t;
        int l=0;
        int r = n+1;
        while(l<r){
            int md =(l+r)/2;
            if(ok(md,t)){
                r=md;
            }else{
                l=md+1;
            }
        }
        if(r>n){
            cout << -1 << endl;
        }else{
            cout << l << endl;
        }
    }

    return 0;

}
