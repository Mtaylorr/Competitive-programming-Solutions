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
const int N = 5e3 + 5;

char grid[N][N];
int cnt[N];

int x,y,z;
bool found=false;
int n;
vector<int> v;

void rem(int x){
    for(int i=0;i<n;i++){
        if(grid[i][x]=='1'){
            cnt[x]--;
        }else{
            cnt[x]++;
        }
    }
}

void solve(vector<int> & v){
    if(found)
        return ;
    vector<int> lf;
    vector<int> rg;
    int mn=1e9;
    int s=-1;
    for(auto u:v){
        if(abs(cnt[u])<mn){
            mn=abs(cnt[u]);
            s=u;
        }
    }
    rem(s);
    for(auto u:v){
        if(u==s)
            continue;
        if(grid[s][u]=='1'){
            rg.pb(u);
        }else{
            lf.pb(u);
        }
    }
    for(auto l:lf){
        for(auto r:rg){
            if(grid[r][l]=='1'){
                found=1;
                x=s;
                y=r;
                z=l;
                return ;
            }
            if(grid[l][r]=='1'){
                cnt[l]--;
                cnt[r]++;
            }else{
                cnt[l]++;
                cnt[r]--;
            }
        }
    }
    if(lf.size())
        solve(lf);
    if(rg.size())
        solve(rg);
}

void solve(){
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> grid[i];
        for(int j=0;j<n;j++){
            if(grid[i][j]=='1'){
                cnt[i]++;
            }else{
                cnt[i]--;
            }
        }
        v.pb(i);
    }
    solve(v);
    if(found){
        cout << x+1 << " "<< y+1 << " " << z+1;
    }else{
        cout << -1 << endl;
    }
    
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
