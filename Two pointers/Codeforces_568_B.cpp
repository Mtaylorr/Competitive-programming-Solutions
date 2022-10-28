//https://codeforces.com/problemset/problem/568/B
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

int n,m,k,s;
ll a[2][N];
ll t[N],c[N];
vector<pair<int,int> > sorted[2];
pair<int,int> mn[2][N];
int val[N];

bool ok( int u){
    u--;
    memset(val, -1, sizeof(val));
    int cur_s = s;
    int cur_k = k;
    int i=0;
    int j=0;

    while(cur_k){
        ll val0 = 1e18;
        if(i<sorted[0].size()){
            val0=sorted[0][i].fi*1ll*mn[0][u].fi;
        }
        ll val1 = 1e18;
        if(j<sorted[1].size()){
            val1=sorted[1][j].fi*1ll*mn[1][u].fi;
        }
        
        if(min(val0,val1)>cur_s){
            return 0;
        }
        if(val0<val1){
            val[sorted[0][i].se]=mn[0][u].se;
            cur_s-=val0;
            i++;
            cur_k--;
        }else{
            val[sorted[1][j].se]=mn[1][u].se;
            cur_s-=val1;
            j++;
            cur_k--;
        }
    }
    return 1;
}

void solve(){
    cin >> n >> m >> k >> s;
    for(int i=0;i<2;i++){
        for(int j=0;j<n;j++){
            cin >> a[i][j];
            if(j==0){
                mn[i][j]={a[i][j],j};
            }else{
                mn[i][j]=min(mn[i][j-1],{a[i][j],j});
            }
        }
    }
    mn[0][n]=mn[0][n-1];
    mn[1][n]=mn[1][n-1];
    for(int i=0;i<m;i++){
        cin >> t[i] >> c[i];
        t[i]--;
        sorted[t[i]].pb({c[i],i});
    }
    sort(all(sorted[0]));
    sort(all(sorted[1]));
    int l=1;
    int r=n+1;
    while(l<r){
        int md = (l+r)/2;
        if(ok(md)){
            r=md;
        }else{
            l=md+1;
        }
    }
    if(l>n){
        cout << -1;
    }else{
        ok(l);
        cout << l << endl;
        for(int i=0;i<m;i++){
            if(val[i]!=-1){
                cout << i+1 << " " << val[i]+1 << endl;
            }
        }
    }
}

int main() {
    //freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
   // cin >>T;
    T=1;
    while(T--){
        solve();
    }
    return 0;
}
