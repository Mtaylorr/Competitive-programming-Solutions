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

void invalid() { cout << "invalid\n"; }

void test_case() {
    cin >> s;
    if (s[0] == '-') {
        invalid();
        return;
    }
    if (s.back() == '-') {
        invalid();
        return;
    }
    for (int i = 0; i < s.size() - 1; i++) {
        if (s[i] == '-' && s[i + 1] == '-') {
            invalid();
            return;
        }
    }
    int nb = 0;
    for (int i = 0; i < s.size(); i++) {
        nb += s[i] == '-';
    }
    if (nb >= 4) {
        invalid();
        return;
    }
    if (nb >= 3 && s[s.size() - 2] != '-') {
        invalid();
        return;
    }
    int lst = 0;
    if (s.back() == 'X') {
        lst = 10;
    } else {
        lst = s.back() - '0';
    }
    int sm = 0;
    int cur = 10;
    for (int i = 0; i < s.size() - 1; i++) {
        if (s[i] == '-') continue;
        if (s[i] == 'X') {
            invalid();
            return;
        }
        sm += (cur * (s[i] - '0'));
        cur--;
    }
    if (cur != 1) {
        invalid();
        return;
    }
    sm += lst;
    if (sm % 11 != 0) {
        invalid();
        return;
    }
    s = "978-" + s;
    sm = 0;
    cur = 1;
    for (int i = 0; i < s.size() - 1; i++) {
        if (s[i] == '-') continue;
        sm += cur * (s[i] - '0');
        cur = 4 - cur;
    }
    sm = (10 - sm % 10) % 10;
    s.back() = char('0' + sm);
    cout << s << endl;
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
