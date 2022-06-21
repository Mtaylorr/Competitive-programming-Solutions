//https://codeforces.com/problemset/problem/1365/E
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 5e5 + 5, P = 1e7 + 5;
const int MOD = 1e9 + 7;

int n;

ll a[N];

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    ll ans=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){
                ans=max(ans, a[i]|a[j]|a[k]);
            }
        }
    }
    cout << ans << endl;


    return 0;

}
