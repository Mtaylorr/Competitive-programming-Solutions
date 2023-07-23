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
string cur = "";
int n;
void solve(int i) {
    if (i >= n) {
        cout << cur << endl;
        return;
    }
    cur+=tolower(s[i]);
    solve(i + 1);
    cur.pop_back();
    if(i+1<n && s[i]=='S' && s[i+1]=='S'){
        cur+='B';
        solve(i+2);
        cur.pop_back();
    }

}

void test_case() {
    cin >> s;
    n=s.size();
    solve(0);
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
