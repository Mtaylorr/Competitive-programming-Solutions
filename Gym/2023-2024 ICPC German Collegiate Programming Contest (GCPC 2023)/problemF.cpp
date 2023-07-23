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
const int N = 1e6 + 5;

int w, h;
int hi[N];
int tmp[2];

void test_case() {
    cin >> w >> h;
    ll sm = 0;
    for (int i = 0; i < w; i++) {
        cin >> hi[i];
        if (hi[i] > h) {
            cout << "impossible";
            return;
        }
        hi[i] = h - hi[i];
        sm += hi[i];
    }
    if (sm % 2) {
        cout << "impossible";
        return;
    }
    for (int i = 0; i < w; i++) {
        int id = i & 1;
        if (tmp[id^1] - 1 >= hi[i]) {
            cout << "impossible";
            return;
        }
        int x = hi[i] - tmp[id ^ 1];
        if (x % 2 == 0) {
            tmp[id] = max(tmp[id ^ 1] - 1, 0);
        } else {
            tmp[id] = (tmp[id ^ 1] + 1);
        }
    }
    if(tmp[(w-1)&1]!=0){
        cout << "impossible\n";
        return ;
    }
    cout << "possible\n";
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
