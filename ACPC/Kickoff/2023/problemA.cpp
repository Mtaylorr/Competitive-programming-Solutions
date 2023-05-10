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

char grid[8][8];
bool vis[8][8];
int dx[] = {0, 0, 1, -1, 1, -1, 1, -1, 1, 1, -1, -1, 2, 2, -2, -2};
int dy[] = {1, -1, 0, 0, 1, 1, -1, -1, 2, -2, 2, -2, 1, -1, 1, -1};

bool ingrid(int x, int y) { return x >= 0 && x < 8 && y >= 0 && y < 8; }

void addKnight(int i, int j) {
    for (int k = 8; k < 15; k++) {
        int ni = i + dx[k];
        int nj = j + dy[k];
        if (ingrid(ni, nj)) {
            vis[ni][nj] = 1;
        }
    }
}

void addBishop(int i, int j) {
    for (int k = 4; k < 8; k++) {
        for (int o = 1;; o++) {
            int ni = i + dx[k] * o;
            int nj = j + dy[k] * o;
            if ((!ingrid(ni, nj))) {
                break;
            }
            vis[ni][nj] = 1;
            if (grid[ni][nj] != '.' && grid[ni][nj] != 'K') break;
        }
    }
}

void addRook(int i, int j) {
    for (int k = 0; k < 4; k++) {
        for (int o = 1;; o++) {
            int ni = i + dx[k] * o;
            int nj = j + dy[k] * o;
            if ((!ingrid(ni, nj))) {
                break;
            }
            vis[ni][nj] = 1;
            if (grid[ni][nj] != '.' && grid[ni][nj] != 'K') break;
        }
    }
}

void addPawn(int i, int j) {
    vector<int> tmp = {5, 7};
    for (auto k : tmp) {
        int ni = i + dx[k];
        int nj = j + dy[k];
        if (ingrid(ni, nj)) {
            vis[ni][nj] = 1;
        }
    }
}

void addQueen(int i, int j) {
    addBishop(i, j);
    addRook(i, j);
}

void test_case() {
    for (int i = 0; i < 8; i++) {
        cin >> grid[i];
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            switch (grid[i][j]) {
                case 'N': {
                    addKnight(i, j);
                    break;
                }
                case 'Q': {
                    addQueen(i, j);
                    break;
                }
                case 'P': {
                    addPawn(i, j);
                    break;
                }
                case 'B': {
                    addBishop(i, j);
                    break;
                }
                case 'R': {
                    addRook(i, j);
                    break;
                }
            }
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (grid[i][j] == 'K') {
                for (int k = 0; k < 8; k++) {
                    int ni = i + dx[k];
                    int nj = j + dy[k];
                    if (ingrid(ni, nj) && vis[ni][nj] == 0) {
                        cout << "Yes\n";
                        return;
                    }
                }
                cout << "No\n";
                return;
            }
        }
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
