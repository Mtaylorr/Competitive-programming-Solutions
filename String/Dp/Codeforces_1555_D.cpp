//https://codeforces.com/contest/1555/problem/D
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll, ll> pl;
typedef long double ld;

#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(),(v).rend()
#define max(a, b) (a>b ? a : b)
#define min(a, b) (a<b ? a : b)
#define FAST ios::sync_with_stdio(0), cin.tie(0),cout.tie(0)


const int N = int(1e6) + 3;
const int MOD = int(1e9) + 7;

int n,m;
string s;
int l,r;
ll dp[6][N];
vector<char> c;
// the string should be in the form abcabcabc where a, b, c take differenct values from 'a' , 'b', 'c'
int main() {
    FAST;
    cin >> n >> m;
    cin >> s;
    c.pb('a');
    c.pb('b');
    c.pb('c');
    int j=0;
    do{
        for(int i=1;i<=n;i++){
            dp[j][i]=dp[j][i-1] + (s[i-1]!=c[(i-1)%3]);
        }
        j++;
    }while(next_permutation(all(c)));
    while(m--){
        cin >> l >> r;
        int ans=1e7;
        for(int i=0;i<6;i++){
            ans=min(ans,dp[i][r]-dp[i][l-1]);
        }
        cout << ans << endl;
    }
    return 0;
}
