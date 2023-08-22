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

/*
4
5 3
2 5 1
4 2
1 3
4 2
3 2
6 4
*/

int a[N];
int n, m;

bool ok[N];
void test_case() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        ok[i] = 1;
    }
    for (int i = 0; i < m; i++) {
        cin >> a[i];
        ok[a[i]] = 0;
    }
    int mn = 1e9;
    for (int i = 1; i <= n; i++) {
        if (ok[i]) {
            mn = i;
            break;
        }
    }
    if (mn < a[0]) {
        cout << "No\n";
    } else {
        cout << "Yes\n";
        for (int i = 1; i <= n; i++) {
            if (ok[i]) {
                cout << i << " ";
            }
        }
        for(int i=0;i<m;i++){
            cout << a[i] << " ";
        }
        cout << endl;
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
