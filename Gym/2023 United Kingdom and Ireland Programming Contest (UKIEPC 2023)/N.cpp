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
string cur = "a";
int n;
map<string, string> st;
void inc() {
    if (cur.back() == 'z') {
        for (auto &c : cur) {
            c = 'a';
        }
        cur += 'a';
    }
    cur.back()++;
}

string prcocess() {
    string ret = "";
    string tmp = s;
    tmp.pop_back();
    auto p = tmp.find(".");
    bool haspoint = "";

    if (p != string::npos) {
        while (tmp.size() && tmp.back() == '0') {
            tmp.pop_back();
        }
    }
    if (tmp.back() == '.') {
        tmp.pop_back();
    }
    ret = tmp + "L";
    return ret;
}

void test_case() {
    cin >> n;
    while (n--) {
        cin >> s;
        s = prcocess();
        if (st.count(s)) {
            cout << st[s] << "\n";
        } else {
            st[s] = cur;
            cout << st[s] << "\n";
            inc();
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
