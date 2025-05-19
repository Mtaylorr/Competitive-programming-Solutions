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
const int N = 3e5 + 5;

ll n,m;

void test_case(){
    cin >> n >> m;
    ll x = n*m/__gcd(n,m);
    cout << (x/n) * (x/m) << endl;
}

int main() {
// #ifndef ONLINE_JUDGE
//     freopen("in.txt", "r", stdin);
// #endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T=1;
    cin >>T;
    while(T--){
        test_case();
    }
    return 0;
}
