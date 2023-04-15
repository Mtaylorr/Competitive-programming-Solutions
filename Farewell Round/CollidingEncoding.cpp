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

int code[30];
int n;
string st;
set<string> s;

void test_case() {
    for (int i = 0; i < 26; i++) {
        cin >> code[i];
    }
    cin >> n;
    s.clear();
    bool cond = false;
    for (int i = 0; i < n; i++) {
        cin >> st;
        string tmp = "";
        for (int j = 0; j < st.size(); j++) {
            tmp += char('0' + code[st[j] - 'A']);
        }
        if (s.count(tmp)) cond = true;
        s.insert(tmp);
    }
    if (cond) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
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
