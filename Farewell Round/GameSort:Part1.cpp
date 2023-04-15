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

const int E = 1e6 + 5;

int n;
string s[N];
int p;
int freq[26];

string construct(string &x) {
    string rs = x;
    for (int i = 25; i >= 0; i--) {
        for (int j = 0; j < freq[i]; j++) {
            rs += char('A' + i);
        }
    }
    return rs;
}

bool possible(string &l, string &r) { return r >= l; }

void test_case() {
    cin >> p;
    for (int i = 0; i < p; i++) {
        cin >> s[i];
    }
    sort(all(s[0]));
    for (int i = 1; i < p; i++) {
        memset(freq, 0, sizeof(freq));
        for (auto &c : s[i]) {
            freq[c - 'A']++;
        }
        string tmp = "";
        for (int j = 0; j < s[i].size(); j++) {
            for (int k = 0; k < 26; k++) {
                if (freq[k] == 0) continue;
                freq[k]--;
                tmp += char('A' + k);
                string a = construct(tmp);
                int x = possible(s[i - 1], a);
                // dbg(s[i - 1], a, x);

                if (x == 1) {
                    break;
                }
                tmp.pop_back();
                freq[k]++;
            }
            if (tmp.size() != (j + 1)) {
                cout << "IMPOSSIBLE\n";
                return;
            }
        }
        s[i] = tmp;
    }
    cout << "POSSIBLE\n";
    for (int i = 0; i < p; i++) {
        cout << s[i] << " ";
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
    int tst = 0;
    while (T--) {
        cout << "Case #" << ++tst << ": ";
        test_case();
    }
    return 0;
}
