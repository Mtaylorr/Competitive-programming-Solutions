//https://codeforces.com/problemset/problem/982/D

//Mtaylor 
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define fi first
#define se second
#define mp make_pair
#define endl '\n';
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
void dbg_out() {cerr<<endl;}
template<typename Head, typename... Tail>
void dbg_out(Head H, Tail... T){cerr << ' '<<H;dbg_out(T...);}
#define dbg(...) cerr << "(" << #__VA_ARGS__<<"):", dbg_out(__VA_ARGS__)
typedef long long ll;
const int N = 3e5 + 5;

struct DSUArray {
    vector<int> id, l, r, sz;
    DSUArray(int n) { init(n); }
    void init(int n) {
        id.assign(n, 0);
        l.assign(n, 0);
        r.assign(n, 0);
        sz.assign(n, 0);
        for (int i = 0; i < n; i++) {
            id[i] = i;
            l[i] = i;
            r[i] = i;
            sz[i] = 1;
        }
    }
    int getid(int u) { return (u == id[u] ? u : id[u] = getid(id[u])); }
    bool sameSet(int u, int v) { return getid(u) == getid(v); }
    void uni(int u, int v) {
        v = getid(v);
        u = getid(u);
        if (u == v) return;
        id[u] = v;
        l[v] = min(l[v], l[u]);
        r[v] = max(r[v], r[u]);
        sz[v] += sz[u];
    }
};

int n,a[N];
map<int,int> pos;

int freq[N];

void solve(){
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> a[i];
        pos[a[i]]=i;
    }
    DSUArray dsu = DSUArray(n);
    int mxlocations = 0;
    int ans = 0;
    int nbcomps=0;
    for(auto &u:pos){
        int i = u.se;
        nbcomps++;
        freq[dsu.sz[dsu.getid(i)]]++;
        
        if(i>0 && a[i-1]<a[i]){
            nbcomps--;
            freq[dsu.sz[dsu.getid(i-1)]]--;
            freq[dsu.sz[dsu.getid(i)]]--;
            dsu.uni(i-1,i);
            freq[dsu.sz[dsu.getid(i)]]++;
        }
        if(i+1<n && a[i+1]<a[i]){
            nbcomps--;
            freq[dsu.sz[dsu.getid(i+1)]]--;
            freq[dsu.sz[dsu.getid(i)]]--;
            dsu.uni(i,i+1);
            freq[dsu.sz[dsu.getid(i)]]++;
        }
        
        if(freq[dsu.sz[dsu.getid(i)]]==nbcomps){
            if(mxlocations<nbcomps){
                mxlocations=nbcomps;
                ans=u.fi+1;
            }
        }
        
    }
    cout << ans;
}

int main() {
    //freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    //cin >>T;
    T=1;
    while(T--){
        solve();
    }
    return 0;
}
