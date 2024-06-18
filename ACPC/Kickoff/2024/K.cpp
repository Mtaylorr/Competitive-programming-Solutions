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
int n;
int freq[26];
int idx;
void test_case() {
    cin >> s;
    cin >> idx;
    --idx;
    n = s.size();
    memset(freq, 0, sizeof(freq));
    for (int i = 0; i < n; i++) {
        if (i == idx - 1 || i == idx + 1) continue;
        freq[s[i] - 'a']++;
    }
    string tmp = "";
    for (int i = 0; i < 26; i++) {
        while (freq[i]--) {
            tmp += char('a' + i);
        }
    }
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (i == idx - 1 || i == idx + 1) continue;
        s[i] = tmp[j++];
    }
    cout << s << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
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
