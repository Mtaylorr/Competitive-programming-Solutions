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

string s;
string person[N];
int n;
int q;
unordered_map<ll, int> freq;
unordered_map<ll, int> id;
int k;

void test_case() {
    cin >> n;
    unordered_set<ll> st;
    for (int i = 0; i < n; i++) {
        cin >> person[i];
        cin >> s;
        sort(all(s));
        st.clear();

        for (int j = 0; j < (1 << 8); j++) {
            ll cur = 0;
            for (int k = 0; k < 8; k++) {
                if ((1 << k) & j) {
                    cur = (11 * cur + (s[k] - '0') + 1);
                }
            }
            st.insert(cur);
        }

        for (auto &u : st) {
            //dbg(u, i);
            freq[u]++;
            id[u] = i;
        }
    }
    cin >> q;
    while (q--) {
        cin >> k;
        cin >> s;
        sort(all(s));
        ll cur = 0;

        for (int k = 0; k < s.size(); k++) {
            cur = (11 * cur + (s[k] - '0') + 1);
        }
        if (freq[cur] == 1) {
            cout << person[id[cur]] << "\n";
        } else if (freq[cur]) {
            cout << "MANY\n";
        } else {
            cout << "NONE\n";
        }
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
