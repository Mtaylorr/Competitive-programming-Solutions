// Mtaylor
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define fi first
#define se second
#define mp make_pair
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

char s[N];

int n;
int ask(int x, string s) {
    cout << "? " << x << " " << s << endl;
    int r;
    cin >> r;
    return r;
}

void guessLastOnes() {
    string st = "";
    st += s[n - 1];
    int r = ask(n - 1, st + "a");
    if (r == 2) {
        s[n] = 'a';
        return;
    }
    r = ask(n - 1, st + "b");
    if (r == 2) {
        s[n] = 'b';
        return;
    }
    s[n] = 'c';
}
int freq[3];

void guessLastTwo() {
    int r = ask(n - 1, "aa");
    memset(freq, 0, sizeof(freq));
    if (r == 2) {
        s[n - 1] = s[n] = 'a';
        return;
    }
    freq[0] += r;
    r = ask(n - 1, "bb");
    if (r == 2) {
        s[n - 1] = s[n] = 'b';
        return;
    }
    freq[1] += r;
    freq[2] += 2 - (freq[0] + freq[1]);
    if (freq[2] == 2) {
        s[n - 1] = s[n] = 'c';
        return;
    }
    vector<int> p;
    for (int i = 0; i < 3; i++) {
        if (freq[i]) {
            p.pb(i);
        }
    }
    assert(p.size() == 2);
    string st = "";
    st += char('a' + p[0]);
    st += char('a' + p[1]);
    r = ask(n - 1, st);
    if (r == 2) {
        s[n - 1] = st[0];
        s[n] = st[1];
    } else {
        s[n - 1] = st[1];
        s[n] = st[0];
    }
}

void guess(int x, int d) {
    if (d == -1) {
        string st = "";
        st += s[x - 1];
        int r = ask(x - 1, st + "a");
        if (r == 2) {
            s[x] = 'a';
        } else {
            r = ask(x - 1, st + "b");
            if (r == 2) {
                s[x] = 'b';
            } else {
                s[x] = 'c';
            }
        }
    } else {
        string st = "";
        st += s[x + 1];
        int r = ask(x, "b" + st);
        if (r == 2) {
            s[x] = 'b';
        } else {
            s[x] = 'c';
        }
    }
}
string _s;
void guessBoth(int i) {
    int x = ask(i, "bb");
    if (x == 2) {
        s[i] = s[i + 1] = 'b';
        return;
    } else if (x == 0) {
        s[i] = s[i + 1] = 'c';
        return;
    }
    x = ask(i, "bc");
    if (x == 0) {
        s[i] = 'c';
        s[i + 1] = 'b';
    } else {
        s[i] = 'b';
        s[i + 1] = 'c';
    }
}

void test_case() {
    //cin >> _s;
    for (int i = 1; i + 2 <= n; i += 3) {
        int x = ask(i, "ab");
        if (x == 0) {
            x = ask(i + 1, "ab");
            if (x == 2) {
                s[i + 1] = 'a';
                s[i + 2] = 'b';
            } else if (x == 1) {
                int y = ask(i + 1, "ac");
                if (y == 1) {
                    s[i + 1] = 'a';
                    s[i + 2] = 'a';
                } else if (y == 0) {
                    s[i + 1] = 'c';
                    s[i + 2] = 'b';
                } else {
                    s[i + 1] = 'a';
                    s[i + 2] = 'c';
                }
            } else {
                s[i + 1] = 'c';
                x = ask(i + 1, "ca");
                if (x == 2) {
                    s[i + 2] = 'a';
                } else {
                    s[i + 2] = 'c';
                }
            }
            guess(i, 1);
        } else if (x == 1) {
            int y = ask(i, "cb");
            if (y == 1) {
                s[i + 1] = 'b';
                s[i] = 'b';
                guess(i + 2, -1);
            } else if (y == 2) {
                s[i] = 'c';
                s[i + 1] = 'b';
                guess(i + 2, -1);
            } else {
                s[i] = 'a';
                x = ask(i + 1, "ab");
                if (x == 2) {
                    s[i + 1] = 'a';
                    s[i + 2] = 'b';
                    continue;
                } else if (x == 1) {
                    y = ask(i + 1, "ac");
                    if (y == 1) {
                        s[i + 1] = 'a';
                        s[i + 2] = 'a';
                    } else if (y == 0) {
                        s[i + 1] = 'c';
                        s[i + 2] = 'b';
                    } else {
                        s[i + 1] = 'a';
                        s[i + 2] = 'c';
                    }
                } else {
                    s[i + 1] = 'c';
                    x = ask(i + 1, "ca");
                    if (x == 2) {
                        s[i + 2] = 'a';
                    } else {
                        s[i + 2] = 'c';
                    }
                }
            }
        } else {
            s[i] = 'a';
            s[i + 1] = 'b';
            guess(i + 2, -1);
        }
    }
    if (n % 3 == 1) {
        guessLastOnes();
    } else if (n % 3 == 2) {
        guessLastTwo();
    }
    //cout << _s << endl;
    cout << "! ";
    for (int i = 1; i <= n; i++) {
        cout << s[i];
    }
    cout << endl;
}

int main() {
    // freopen("input.txt", "r", stdin);
    int T = 1e9;
    while (cin >> n) {
        if (n == 0) exit(0);
        test_case();
    }
    return 0;
}
