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

int n, s[N];
int m;
void test_case() {
    cin >> n >> m;
    set<pair<int, int> > st;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        st.insert({-s[i], i});
    }
    while (!st.empty()) {
        pair<int, int> p = *st.begin();
        st.erase(st.begin());
        int x = -p.fi;
        int i = p.se;
        for (int j = i - 1; j <= i + 1; j += 2) {
            if (j >= 0 && j < n && s[j] < s[i] - m) {
                st.erase({-s[j],j});
                s[j] = s[i] - m;
                st.insert({-s[j], j});
            }
        }
    }
    for(int i=0;i<n;i++){
        cout << s[i] << " ";
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
