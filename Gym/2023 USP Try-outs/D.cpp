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
const int N = 4e5 + 5;

int n;
int k;
int tin[N];
int tout[N];
queue<int> q[N];
bool isadd[N];
int val[N];
bool done[N];

void test_case() {
    cin >> n >> k;
    for (int i = 0; i < 2 * n; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, y;
            cin >> x >> y;
            x--;
            y--;
            tin[x] = i;
            isadd[i] = 1;
            val[i] = x;
            q[y].push(x);
        } else {
            int y;
            cin >> y;
            --y;
            int x = q[y].front();
            val[i] = x;
            q[y].pop();
            tout[x] = i;
        }
    }
    set<int> st;
    set<int>::iterator it;
    for (int i = 0; i < 2 * n; i++) {
        if (isadd[i]) {
            st.insert(tin[val[i]]);
        } else {
            if (st.count(tin[val[i]])) {
                st.erase(tin[val[i]]);
            }
            while (!st.empty() && *st.begin() <= tin[val[i]]) {
                done[*st.begin()] = 1;
                st.erase(st.begin());
            }
        }
    }
    vector<int> ans;
    for (int i = 0; i < 2 * n; i++) {
        if (done[i]) {
            ans.pb(val[i]);
        }
    }
    sort(all(ans));
    cout << ans.size() << endl;
    for (auto &u : ans) {
        cout << u + 1 << " ";
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
