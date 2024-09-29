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

map<string, int> teamtoid, nametoid[2];
int cnt[2][N];
int cid[2];
vector<pair<string, int> > players;
vector<string> teams;
set<int> current[2];

void readTeam(int id) {
    string s;
    cin >> s;
    teamtoid[s] = id;
    cid[id] = 5;
    teams.push_back(s);
    for (int i = 0; i < 5; i++) {
        cin >> s;
        nametoid[id][s] = i;
        current[id].insert(i);
        players.push_back({s, id});
    }
}

int q;
void test_case() {
    readTeam(0);
    readTeam(1);
    cin >> q;
    while (q--) {
        string team, op, player1, player2;
        int score;
        cin >> team >> team >> op;
        if (op == "scored") {
            cin >> score;
            int id = teamtoid[team];
            for (auto &u : current[id]) {
                cnt[id][u] += score;
            }
            for (auto &u : current[id^1]) {
                cnt[id^1][u] -= score;
            }
        } else {
            int id = teamtoid[team];
            string with;
            cin >> player1 >> with >> player2;

            int id1 = nametoid[id][player1];
            int id2 = -1;
            if (nametoid[id].count(player2)==0) {
                id2 = cid[id]++;
                nametoid[id][player2] = id2;
                players.push_back({player2, id});

            } else {
                id2 = nametoid[id][player2];
            }
            current[id].erase(id1);
            current[id].insert(id2);
        }
    }
    for (auto &u : players) {
        string playerName = u.first;
        int teamId = u.se;
        string teamName = teams[teamId];
        // dbg(playerName, teamId);
        int sc = cnt[teamId][nametoid[teamId][playerName]];
        cout << playerName << ' ' << "(" << teamName << ")" << " ";
        if (sc == 0) {
            cout << 0 << endl;
        } else if (sc > 0) {
            cout << "+" << sc << endl;
        } else {
            cout << sc << endl;
        }
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
    // cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
