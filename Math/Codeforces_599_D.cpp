//https://codeforces.com/problemset/problem/599/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 3e5 + 5, M=1000 +5,E = 2e5 +5 ;
const int MOD = 1e9 + 7  ;
const double eps = 1e-7;

set<pair<ll,ll> > ans;

ll getsquares(ll n){
    return ((n)*(n+1)*(2*n+1))/6;
}

ll getsum(ll n){
    return ((n)*(n+1))/2;
}
ll v;

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> v;
    for(ll i=1;;i++){
        ll x = getsquares(i-1);
        ll y = getsum(i-1);
        ll z = y*i;
        ll curv = v-x+z;
        ll fact = i*i  - y;
        if(curv<0){
            break;
        }

        if(fact>0 && curv%fact==0){
            if(curv/fact<i){
                break;
            }
            ans.insert({i,curv/fact});
            ans.insert({curv/fact,i});

        }
    }
    cout << ans.size() << endl;
    for(auto u:ans){
        cout << u.fi << " " << u.se << "\n";
    }
    return 0;
}
