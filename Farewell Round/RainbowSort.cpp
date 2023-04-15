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

int n;
int s[N];
map<int, int> freq;

void test_case() {
    cin >> n;
    freq.clear();
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        freq[s[i]]++;
    }
    vector<int> ans;
    for (int i = 0; i < n;) {
        int x = s[i];
        int j = i;
        while (j < n && s[j] == x) {
            j++;
        }
        j--;
        if (j - i + 1 != freq[x]) {
            cout << "IMPOSSIBLE\n";
            return;
        }
        ans.pb(x);
        i = j + 1;
    }
    for (auto u : ans) {
        cout << u << " ";
    }
    cout << endl;
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    cin >> T;
    int tst = 0;
    while (T--) {
        cout << "Case #" << ++tst << ": ";
        test_case();
    }
    return 0;
}
