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

vector<char> chars;

string a, b, c, d;
int query(string &s) {
    cout << s << endl;
    cin >> a >> b;
    if (b == "DENIED") {
        cin >> c >> d;
        c = c.substr(1, c.size() - 1);
        return stoi(c);
    } else {
        exit(0);
    }
}
int sm[N];

void test_case() {
    for (char c = 'a'; c <= 'z'; c++) {
        chars.pb(c);
    }
    for (char c = 'A'; c <= 'Z'; c++) {
        chars.pb(c);
    }
    for (char c = '0'; c <= '9'; c++) {
        chars.pb(c);
    }
    string p = "";
    for (int i = 1; i <= 20; i++) {
        p += chars[0];
        int x = query(p);
        if (x != 5) {
            break;
        }
    }
    int r = 6;
    int step = 3 + 1 + 3 + 1;
    sm[0] = r + step;
    for (int i = 1; i <= 20; i++) {
        sm[i] = sm[i - 1] + step + 1;
    }

    while (1) {
        int x = query(p);
        int idx = 0;
        for (int i = 0; i < 20; i++) {
            if (x == sm[i]) {
                idx = i;
                break;
            }
        }
        for (int j = 0; j < chars.size(); j++) {
            if (chars[j] == p[idx]) {
                p[idx] = chars[j + 1];
                break;
            }
        }
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    int T = 1;
    while (T--) {
        test_case();
    }
    return 0;
}
