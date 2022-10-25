//https://codeforces.com/contest/1182/problem/E
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

typedef vector<vector<ll> > M;

const int MOD = 1e9 + 7;
const int D = 3;
void init(M &v) {
    v.resize(D);
    for (int i = 0; i < D; i++) {
        v[i].assign(D, 0);
    }
}

void getId(M &rs) {
    init(rs);
    for (int i = 0; i < D; i++) rs[i][i] = 1;
}

M mul(M &u, M &v, int mod = MOD) {
    M rs;
    init(rs);
    for(int n=0;n<D;n++)
        for(int m=0;m<D;m++)
            for(int k=0;k<D;k++)
                rs[n][m]=(rs[n][m]+0ll+(u[n][k]*1ll*v[k][m])%mod)%mod;
    return rs;
}

M add(M &u, M &v, int mod = MOD) {
    M rs;
    init(rs);
    for(int n=0;n<D;n++)
        for(int m=0;m<D;m++)
            rs[n][m]=(u[n][m]%mod + v[n][m]%mod)%mod;
    return rs;
}

M sub(M &u, M v, int mod = MOD) {
     M rs;
    init(rs);
    for(int n=0;n<D;n++)
        for(int m=0;m<D;m++)
            rs[n][m]=(u[n][m]%mod + 0ll - v[n][m]%mod +mod)%mod;
    return rs;
}

M powe(M &u, ll v, int mod = MOD) {
    M ans;
    getId(ans);
    M acc = u;
    while (v) {
        if (v % 2) ans = mul(ans, acc, mod);
        acc = mul(acc, acc, mod);
        v /= 2;
    }
    return ans;
}

void show(M & v){
    for(int i=0;i<D;i++){
        for(int j=0;j<D;j++){
            cout << v[i][j] <<" ";
        }
        cout << endl;
    }
}

#define MODDtype int

MODDtype mul(MODDtype u, MODDtype v, MODDtype mod = MOD) {
    return ((u % mod) * 1ll * (v % mod)) % mod;
}

MODDtype add(MODDtype u, MODDtype v, MODDtype mod = MOD) {
    return ((u % mod) + 0ll + (v % mod) + mod) % mod;
}

MODDtype sub(MODDtype u, MODDtype v, MODDtype mod = MOD) {
    return ((u % mod) + 0ll - (v % mod) + mod) % mod;
}

MODDtype powe(MODDtype u, ll v, MODDtype mod = MOD) {
    MODDtype ans = 1;
    MODDtype acc = u;
    while (v) {
        if (v % 2)
            ans = mul(ans, acc, mod);
        acc = mul(acc, acc, mod);
        v /= 2;
    }
    return ans;
}

MODDtype inv(MODDtype u, MODDtype mod = MOD) {
    return powe(u, mod - 2, mod);
}
ll n,f[3];
ll c;
ll pf[3];

void solve() {
    cin >> n;
    for(int i=0;i<3;i++){
        cin >> f[i];
    }
    cin >> c;
    M  mat;
    init(mat);

    mat[0][1]=mat[1][2]=mat[2][0]=mat[2][1]=mat[2][2]=1;
    mat = powe(mat,n-3, MOD-1);
    //show(mat);
    int ans=1;
    for(int i=0;i<3;i++){
        ans=mul(ans, powe(f[i],mat[2][i]));
    }
    int pc = 0;
    for(int i=0;i<3;i++){
        pc=add(pc, mul(mat[2][i],(i+1), MOD-1),MOD-1);
    }
    pc = sub(pc, n%(MOD-1), MOD-1);
    ans=mul(ans,powe(c, pc));
    cout << ans << endl;
}

int main() {
    // freopen("input.txt", "r", stdin);
    int T;
    //cin >> T;
    T=1;
    while (T--) {
        solve();
    }
    return 0;
}
