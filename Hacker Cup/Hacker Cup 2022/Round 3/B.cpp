#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 1e6 + 100, M = 1000 + 5, E = 2e6 + 5;
const int MOD[2] = {(int)(1e9 + 7), (int)(1e9 + 9)};
const double eps = 1e-7;
const int alpha = 256;
const int BASE[2] = {37, 31};

int mul(int u , int v, int mod=MOD[0]){
    return ((u%mod)*1ll*(v%mod))%mod;
}
int add(int u, int v, int mod=MOD[0]){
    return ((u%mod)+0ll+(v%mod)+mod)%mod;
}


int T;
ll n;
int sz[N];
map<pair<int,int>,int > tmp[N],ha[N];
int curh[2][N];
int mi;
char c;
int p;
int main() {
    //freopen("input.txt", "r", stdin);
    freopen("third_trie_input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    for(int tt=1;tt<=T;tt++){
        cout << "Case #" << tt << ": ";
        cin >> n;
        for(int i=0;i<=1e6;i++){
            ha[i].clear();
        }
        for(int i=0;i<n;i++){
            cin >> mi;
            for(int i=0;i<=mi;i++){
                tmp[i].clear();
            }
            sz[1]=0;
            curh[0][1]=0;
            curh[1][1]=0;
            for(int i=2;i<=mi;i++){
                cin >> p >> c;
                for(int j=0;j<2;j++)
                    curh[j][i]=add(mul(curh[j][p], BASE[j], MOD[j]), (c-'a')+1);
                sz[i]=sz[p]+1;
                tmp[sz[i]][{curh[0][i],curh[1][i]}]=1;
            }
            for(int i=1;i<=mi;i++){
                for(auto u:tmp[i]){
                    ha[i][u.fi]++;
                }
            }
        }
        ll all = (n*(n-1)*(n-2))/6;
        ll ans=0;
        for(int i=0;i<=1e6;i++){
            for(auto u:ha[i]){
                ll k = n-u.se;
                ll ssz = (k*(k-1)*(k-2))/6;
                ans+=all-ssz;
            }
        }
        cout << ans+all << endl;
    }



    return 0;

}
