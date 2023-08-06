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
const int N = 5e5 + 5;
string s;
int n;
void test_case() {
    cin >> s;
    n = s.size();
    int nbl = 0;
    int nb = 0;
    for (auto &c : s) {
        if (c == ')') {
            if (nb) {
                nb--;
            } else {
                nbl++;
            }
        } else {
            nb++;
        }
    }
    if (nb % 2 == nbl % 2) {
        cout << abs(nb-nbl)/2 + (nb+nbl)/2 << endl;
    } else {
        cout << "-1\n";
    }
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
