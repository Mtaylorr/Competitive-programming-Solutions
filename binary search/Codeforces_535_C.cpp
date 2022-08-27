//https://codeforces.com/problemset/problem/535/C
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5, E = 1 << 17;
const int MOD = 998244353;

ll a,b;
int n,l,t,m;

bool ok(int u){
    int r = l+u;
    ll xl = a + b * (l-1);
    ll xr = a + b * (r-1);
    ll sm = ((r-l+1) * (xl+xr) ) / 2;
    return max(xr,(sm+m-1)/m)<=t;
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> a >> b >> n;
    while(n--){
        cin >> l >> t >> m;
        int lf = 0;
        int rg = 1e6;
        while(lf<rg){
            int md = (rg+lf+1)/2;
            if(ok(md)){
                lf=md;
            }else{
                rg=md-1;
            }
        }
        if(ok(lf)){
            cout << l+lf << endl;
        }else{
            cout << -1 << endl;
        }
    }
    return 0;
}
