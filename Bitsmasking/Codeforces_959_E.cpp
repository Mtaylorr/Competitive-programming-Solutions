//https://codeforces.com/contest/959/problem/E
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e6 + 5, E = 1 << 17;
const int MOD =  998244353 ;


ll n;
int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    ll ans=0;
    ll cur= 1 ;
    for(int i=0;i<=50;i++){
        ans+=cur*(((n+cur-1))/(cur*2));
        cur = cur*2;
    }
    cout << ans << endl;
    return 0;
}
