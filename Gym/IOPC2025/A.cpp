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

void test_case() {
    cin >> s;
    vector<string> v;
    string cur = "";
    for (auto &c : s) {
        if (c == '.') {
            v.push_back(cur);
            cur = "";
        } else {
            cur += c;
        }
    }
    v.push_back(cur);
    if (v.size() != 3) {
        cout << "No\n";
        return;
    }
    if (v[2] != "com") {
        cout << "No\n";
        return;
    }
    if (v[1] != "odoo") {
        cout << "No\n";
        return;
    }
    cur = v[0];

    if (cur.size() < 4 || cur.size() > 30) {
        cout << "No\n";
        return;
    }
    if (cur[0] == '-') {
        cout << "No\n";
        return;
    }
    if (cur.back() == '-') {
        cout << "No\n";
        return;
    }
    for (auto &c : cur) {
        if (c >= 'a' && c <= 'z') {
            continue;
        }
        if (c >= '0' && c <= '9') {
            continue;
        }
        if (c == '-') {
            continue;
        }
        cout << "No\n";
        return;
    }
    cout << "Yes";
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
