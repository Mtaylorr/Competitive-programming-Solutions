// Mtaylor
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define fi first
#define se second
#define mp make_pair
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

int n;
set<int> s[N];
ll ans[N];

void test_case() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int l = i;
        while (s[i].count(l)) l--;
        cout << "? " << l << " " << i << endl;
        ll x, a, b;
        cin >> x >> a >> b;
        ll to_rem = 0;
        if (l != i)
            for (int j = l; j < i; j++) to_rem += ans[j];
        ans[i] = x - to_rem;
        s[b].insert(a);
    }
    cout << "! ";
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}

int main() {
    // freopen("input.txt", "r", stdin);
    int T = 1;
    while (T--) {
        test_case();
    }
    return 0;
}
