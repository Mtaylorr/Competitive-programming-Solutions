//https://codeforces.com/problemset/problem/660/D

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e5 + 5, E = 1 << 17;
const int MOD =  1e9 + 7;

map<pair<ll,ll>,int > freq;
int n;
int x[N],y[N];
int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll ans=0;
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> x[i] >> y[i];
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(j==i)
                continue;
            if(x[j]<x[i])
                continue;
            if(x[j]==x[i] && y[i]<y[j])
                continue;
            ll dx = x[j]-x[i];
            ll dy = y[j]-y[i];
            if(freq.count({dx,dy})){
                ans+=freq[{dx,dy}];
            }
            freq[{dx,dy}]++;
        }
    }
    cout << ans/2;
    return 0;
}
