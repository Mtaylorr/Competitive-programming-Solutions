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

int manag[N];
map<string, int> ids;
vector<int> adj[N];

string idToName[N];
int idx = 0;
int getId(string &s) {
    if (ids.count(s)) return ids[s];
    idToName[idx] = s;
    return ids[s] = idx++;
}

string getBinary(int x) {
    string ans = "";
    while (x) {
        ans += to_string(x % 2);
        x /= 2;
    }
    reverse(all(ans));
    return ans;
}
string B;
vector<int> ord;
void dfsencode(int u) {
    B += "0";
    ord.pb(u);
    for (auto &v : adj[u]) {
        dfsencode(v);
    }
    B += "1";
}

void encode() {
    string s;
    string current_manager;
    int cur_manager = -1;
    while (cin >> s) {
        if (s.back() == ':') {
            current_manager = s;
            current_manager.pop_back();
            cur_manager = getId(current_manager);
        } else {
            int v = getId(s);
            adj[cur_manager].pb(v);
            manag[v] = cur_manager;
        }
    }
    dfsencode(0);
    for (auto &i : ord) {
        cout << idToName[i] << "\n";
    }
    cout << B << endl;
    // for (int i = 2; i < idx; i++) {
    //     cout << getBinary(manag[i]);
    // }
}
void decode() {
    vector<string> names;
    string s;
    while (cin >> s) {
        names.pb(s);
    }
    string B = names.back();
    names.pop_back();
    int j = 0;
    stack<int> st;
    for (int i = 0; i < B.size(); i++) {
        if (B[i] == '0') {
            if (st.size()) {
                adj[st.top()].pb(j);
            }
            st.push(j);
            j++;
        } else {
            st.pop();
        }
    }
    for (int i = 0; i < names.size(); i++) {
        if (adj[i].size()) {
            cout << names[i] << ": ";
            for (auto &u : adj[i]) {
                cout << names[u] << " ";
            }
            cout << endl;
        }
    }
}

void test_case() {
    string s;
    cin >> s;
    if (s[0] == 'E') {
        encode();
    } else {
        decode();
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    // cin >>T;
    while (T--) {
        test_case();
    }
    return 0;
}
