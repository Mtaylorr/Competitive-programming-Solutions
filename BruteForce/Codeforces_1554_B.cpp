//https://codeforces.com/contest/1554/problem/B
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll, ll> pl;
typedef long double ld;

#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(),(v).rend()
#define max(a, b) (a>b ? a : b)
#define min(a, b) (a<b ? a : b)
#define FAST ios::sync_with_stdio(0), cin.tie(0),cout.tie(0)


const int N = int(1e6) + 3;
const int MOD = int(1e9) + 7;


int t;
int n;
ll a[N];
ll k;
int main() {
    FAST;
    cin >> t;
    while (t--) {
        cin >> n >> k;
        for(int i=0;i<n;i++){
            cin >> a[i];
        }
        ll ans=-1e18;
        for(ll i=n-1;i>=0;i--){
            for(ll j=i-1;j>=max(0,i-k-2);j--){
                //cout << (i+1)*j)-k*(a[i]|a[j]) << endl;
                ans=max(ans,(i+1)*(j+1)-k*(a[i]|a[j]));
            }
        }
        cout << ans << endl;
    }

    return 0;
}
