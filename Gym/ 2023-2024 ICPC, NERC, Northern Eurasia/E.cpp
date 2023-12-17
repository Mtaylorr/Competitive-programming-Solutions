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

ll p, q;

string getans(ll x) {
    x = (x / 2);
    if (x < 0) {
        return "0-" + to_string(abs(x)) + "-0+" + "0-" + to_string(abs(x)) + "+0";
    } else {
        return "0+" + to_string(abs(x)) + "-0+" + "0+" + to_string(abs(x)) + "+0";
    }
}

string solve(ll p, ll q) {
    string ans = "";
    if (((abs(p) / 2) % 10 == 0 && p != 0) || ((abs(q) / 2) % 10 == 0 && q != 0)) {
        for (int i = 2; i <= 8; i++) {
            if (((abs(p - i) / 2) % 10 != 0 || (p - i) == 0) &&
                ((abs(q - i) / 2) % 10 != 0 || (q - i) == 0)) {
                p -= i;
                q -= i;
                ans += to_string(i) + "+";
                break;
            }
            if (((abs(p + i) / 2) % 10 != 0 || (p + i) == 0) &&
                ((abs(q + i) / 2) % 10 != 0 || (q + i) == 0)) {
                p += i;
                q += i;
                ans += "0-" + to_string(i) + "-0+";
                break;
            }
        }
    }
    ans += getans(p);
    ans += "+";
    string t = getans(q);
    reverse(all(t));
    ans += t;
    return ans;
}

void test_case() {
    cin >> p >> q;
    string ans;
    if (abs(p) % 2 == 1 && abs(q) % 2 == 1) {
        ans = "1+";
        p--;
        q--;
    } else if (abs(p) % 2 == 0 && abs(q) % 2 == 1) {
        ans = "12*12+";
        p -= 12 * 12;
        q -= 21 * 21;
    } else if (abs(p) % 2 == 1 && abs(q) % 2 == 0) {
        ans = "21*21+";
        p -= 21 * 21;
        q -= 12 * 12;
    }
    ans += solve(p, q);
    cout << ans << endl;
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
