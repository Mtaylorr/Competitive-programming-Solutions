//https://codeforces.com/contest/514/problem/C
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 6e5 + 5, P = 1e7 + 5;
const int MOD = 1e9 + 7;
const int K = 5;
ll mul(ll u , ll v, ll mod=MOD){
    return ((u%mod)*(v%mod))%mod;
}
ll add(ll u, ll v, ll mod=MOD){
    return ((u%mod)+(v%mod)+mod)%mod;
}

ll sub(ll u, ll v , ll mod=MOD){
    return ((u%mod)-(v%mod)+mod)%mod;
}

ll powe(ll u, ll v, ll mod=MOD){
    ll ans=1;
    ll acc=u;
    while(v){
        if(v%2){
            ans=mul(ans,acc,mod);
        }
        acc = mul(acc,acc,mod);
        v/=2;
    }
    return ans;
}
ll  inv(ll u,ll mod=MOD){
    return powe(u,mod-2,mod);
}
int invK = inv(K);

int n,m;
string s;
map<int,set<int> > dp[N][3];
vector<int> v;

void preprocess(){
    int l = s.size();
    v.assign(l+1,0);
    int h = 0;
    for(int i=l-1;i>=0;i--){
        h = add(mul(h,K) , ((s[i]-'a')+1) );
        v[i]=h;
    }
    h=0;
    int p =1;
    for(int i=0;i<l;i++){
        int cur_h = add(h, mul(p,v[i+1])) ;
        dp[l][s[i]-'a'][i].insert(cur_h);
        h=add(h, mul(((s[i]-'a')+1),p) );
        p=mul(p,K);
    }
}

bool process(){
    int l = s.size();
    v.assign(l+1,0);
    int h = 0;
    for(int i=l-1;i>=0;i--){
        h = add(mul(h,K) , ((s[i]-'a')+1) );
        v[i]=h;
    }
    h=0;
    int p =1;
    for(int i=0;i<l;i++){
        int cur_h = add(h, mul(p,v[i+1])) ;
        int x = s[i]-'a';
        if(dp[l][(x+1)%3][i].count(cur_h)){
            return 1;
        }
        if(dp[l][(x+2)%3][i].count(cur_h)){
            return 1;
        }
        h=add(h, mul(((s[i]-'a')+1),p) );
        p=mul(p,K);
    }
    return 0;
}

int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("game.in", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for(int i=0;i<n;i++){
        cin >> s;
        preprocess();
    }
    for(int i=0;i<m;i++){
        cin >> s;
        bool rs = process();
        if(rs){
            cout << "YES\n";
        }else{
            cout << "NO\n";
        }
    }
    return 0;

}
