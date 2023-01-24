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
int n, x;
map<string, queue<int> > vals;
set<string> strings;

void test_case() {
    vals.clear();
    cin >> n;
    strings.clear();
    for (int i = 0; i < n; i++) {
        cin >> s >> x;
        vals[s].push(x);
        strings.insert(s);
    }
    while (strings.size()) {
        set<string> tmp;
        for (auto &u : strings) {
            cout << u << " " << vals[u].front() << "\n";
            vals[u].pop();
            if (vals[u].empty()) {
                tmp.insert(u);
            }
        }
        for(auto u:tmp){
            strings.erase(u);
        }
    }

}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
