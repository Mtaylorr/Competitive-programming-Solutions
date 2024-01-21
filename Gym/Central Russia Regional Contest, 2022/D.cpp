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
string s = "YOLP";
string sp = "YL";

int n;

char grid[1005][1005];

int applyeven(int x, int y, int n) {
    int k = n / 2;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            if (i < k - 1 && j < k - 1) {
                grid[i][j] = 'O';
            } else {
                grid[i][j] = sp[(i + j) % 2];
            }
        }
    }
    return k;
}
void test_case() {
    cin >> n;
    if (n == 1) {
        cout << 1 << endl;
        cout << "Y";
        return;
    }
    if (n <= 3 || n == 5) {
        cout << -1 << endl;
        return;
    }
    if (n % 2 == 0) {
        int k = applyeven(0, 0, n);
        cout << k << endl;
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                cout << grid[i][j];
            }
            cout << endl;
        }
        return;
    } else {
        int nn = n - 3;
        int k = applyeven(0, 0, nn);
        for (int i = 0; i < k; i++) {
            for (int j = k; j < 2 * k; j++) {
                grid[i][j] = 'O';
            }
        }
        for (int i = k; i < 2 * k; i++) {
            for (int j = k; j < 2 * k; j++) {
                grid[i][j] = 'P';
            }
        }
        for (int i = k; i < 2 * k; i++) {
            for (int j = 0; j < k; j++) {
                grid[i][j] = 'O';
            }
        }
        k *= 2;
        cout << k << endl;
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                cout << grid[i][j];
            }
            cout << endl;
        }
        return;
    }
    cout << -1 << endl;
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
