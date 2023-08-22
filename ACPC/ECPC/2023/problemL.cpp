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
/*
6
2 2
2 1
2 0
4 2
4 6
7 4
*/

int n;
ll k;
bool done[N];
int ans[N];
void test_case() {
    cin >> n >> k;
    if (k % 2) {
        cout << "No\n";
        return;
    }
    for (int i = 1; i <= n; i++) {
        done[i] = 0;
    }
    int l = 1;
    int r = n;
    while (k) {
        if (l >= r) {
            break;
        }
        if (2 * (r - l) <= k) {
            k -= 2 * (r - l);
            done[l] = 1;
            done[r] = 1;
            ans[l] = r;
            ans[r] = l;
            l++;
            r--;
        } else {
            r--;
        }
    }
    if (k) {
        cout << "No\n";
        return;
    }
    cout << "Yes\n";
    for(int i=1;i<=n;i++){
        if(done[i]){
            cout << ans[i] << " ";
        }else{
            cout << i << " ";
        }
    }
    cout << endl;
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
