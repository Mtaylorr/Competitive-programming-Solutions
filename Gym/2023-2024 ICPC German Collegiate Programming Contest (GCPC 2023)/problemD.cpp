// Mtaylor
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define fi first
#define se second
#define mp make_pair
#define endl '\n';
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
void dbg_out() { cerr << endl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << ' ' << H;
    dbg_out(T...);
}
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
typedef long long ll;
const int N = 3e5 + 5;
int cnt[10];
int val[10];

void test_case() {
    val[0] = 4;
    val[1] = 6;
    val[2] = 8;
    val[3] = 12;
    val[4] = 20;

    int mx = 0;
    int mn = 0;
    for (int i = 0; i < 5; i++) {
        cin >> cnt[i];
        mx += val[i] * cnt[i];
        mn += cnt[i];
    }
    vector<int> tmp;
    while (mn <= mx) {
        tmp.pb(mx);
        if (mx == mn) break;
        tmp.pb(mn);
        mn++;
        mx--;
    }
    reverse(all(tmp));
    for(auto u:tmp){
        cout << u << " ";
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    while (T--) {
        test_case();
    }
    return 0;
}
