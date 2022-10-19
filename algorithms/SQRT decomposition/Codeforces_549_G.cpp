//https://codeforces.com/problemset/problem/549/G
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 2e5 + 5, M = 1000 + 5, E = 1e6 + 5;
const int MOD = 1e9 + 7;
const double eps = 1e-7;

int a[N];
int n;
int cur = 1;
vector<int> vals[N];
int to_add[N];
int B = 450;

void unlazy(int i) {
    if (to_add[i]) {
        for (auto &u: vals[i]) {
            u += to_add[i];
        }
        to_add[i] = 0;
    }
}

void reprocess() {
    vector<int> tmp;
    for (int i = 0; i < cur; i++) {
        unlazy(i);
        for (auto u: vals[i])
            tmp.pb(u);
        vals[i].clear();
    }
    for (int i = 0; i < tmp.size(); i++) {
        cur = (i / B) + 1;
        vals[i / B].pb(tmp[i]);
    }
}

bool ins(int b, int x) {
    unlazy(b);
    vector<int> tmp;
    bool cmp = true;
    for (auto u: vals[b]) {
        if (u == x - 1) {
            return 0;
        }

        if (u >= x && cmp) {
            tmp.pb(x);

            cmp = false;
        }
        x--;
        if (cmp)
            tmp.pb(u + 1);
        else
            tmp.pb(u);
    }
    if (cmp) {
        tmp.pb(x);
    }
    vals[b] = tmp;
    return 1;
}

void showans() {
    for (int i = 0; i < cur; i++) {
        unlazy(i);
        for (auto u: vals[i])
            cout << u << " ";
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cur = 1;
    vals[0].pb(a[n - 1]);
    for (int i = n - 2; i >= 0; i--) {
        if (i % B == 0) {
            reprocess();
        }
        if (vals[0][0] + to_add[0] >= a[i]) {
            bool c = ins(0, a[i]);
        } else if (a[i] - (n - i - 1) >= vals[cur - 1].back() + 1 + to_add[cur - 1]) {
            int lsz=0;
            if(cur>0){
                for(int i=0;i<cur-1;i++){
                    to_add[i]++;
                    lsz+=vals[i].size();
                }
            }
            bool c = ins(cur - 1, a[i]-lsz);
        } else {
            int target_batch = -1;
            int lfsz = 0;
            for (int j = 0; j < cur; j++) {

                int v = a[i] - lfsz + 1 - vals[j].size();
                if (vals[j].back() + to_add[j] >= v) {
                    bool c = ins(j, a[i] - lfsz);
                    if (c) {
                        target_batch = j;
                    }
                    break;
                }
                lfsz += vals[j].size();
            }
            if (target_batch == -1) {
                cout << ":(";
                return 0;
            }
            for (int i = 0; i < target_batch; i++) {
                to_add[i]++;
            }
        }

    }
    showans();


    return 0;

}
