// https://codeforces.com/contest/1552/problem/F
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
const int MOD = 998244353;

ll fact[N];
ll invfact[N];

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

void init_fact(ll n, ll mod=MOD){
    fact[0]=fact[1]=1;
    for(int i=2;i<=n;i++){
        fact[i]=mul(i,fact[i-1],mod);
    }
}

ll cnk (ll n , ll k){
    if(k>n)return 0;
    if(n==0)return 1;
    ll ans = mul(fact[n],invfact[k]);
    ans= mul(ans,invfact[n-k]);
    return ans;
}

void init_inv_fact(ll n, ll mod=MOD){
    for(int i=0;i<=n;i++){
        invfact[i]=powe(fact[i],mod-2,mod);
    }
}
void init(ll n, ll mod=MOD){
    init_fact(n,mod);
    init_inv_fact(n,mod);
}

int n;
int x[N],y[N]; 
set<int> ss; // to store distinct values
map<int,int> code, decode; // to compress the values
int cn; //  cound of distinct numbers
bool isx[N]; //  if the position is an x of a certain portal
int ind[N]; //  the position of the first to the right portal
int s[N];  
ll tree[2][N]; //  Fenwick tree data structure
int dp[N]; //  the minimum time required to reach the portal i at inactive state

void upd(int x, ll val, int bit){
    for(;x<=n;x+=(x)&(-x)){
        tree[bit][x]=add(tree[bit][x],val);
    }
}

ll get(ll x, int bit){
    ll res=0;
    for(;x;x-=(x)&(-x)){
        res=add(tree[bit][x], res);
    }
    return res;
}

ll getrange(ll l, ll r, ll bit){
    if(l>r)
        return 0;
    return sub(get(r, bit),get(l-1,bit));
}



int main() {
    FAST;
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> x[i]  >> y[i] >> s[i];
        ss.insert(x[i]);
        ss.insert(y[i]);
    }
    // values compression
    cn=1;
    for(auto u:ss){
        code[u]=cn;
        decode[cn]=u;
        cn++;
    }

    for(int i=0;i<n;i++){
        int xx = code[x[i]];
        int yy = code[y[i]];
        isx[xx]=1;
        ind[xx]=i;
        ind[yy]=i;
    }
    int id= cn;
    for(int i=cn-1;i>=1;i--){
        if(isx[i]){
            id = ind[i];
        }else{
            ind[i]=id;
        }
    }
    // tree 1 for the cumulative sum of differences of x position
    for(int i=1;i<n;i++){
        int p = i+1;
        upd(p,sub(x[i],x[i-1]),1);
    }
  
    if(s[0]==0){
        dp[1] = add(x[0],0);
    }else{
        dp[1] = add(x[0],sub(x[0],y[0]));
    }
    upd(1, sub(x[0],y[0]),0);
    for(int i=1;i<n;i++){
        int p = i+1; //  1-indexed position
        dp[p] = sub(x[i],x[i-1]); //  added the first time to reach i-1
        dp[p] = add(dp[p],dp[p-1]); // added the time difference from i-1 to i
        // calculating the necessary time to reach the position i if the state was active
        int yy = code[y[i]]; 
        int id = ind[yy]; // the first portal's x to the right
        ll res = sub(x[id], y[i]); // added  the time diff to reach that portal
        ll ress = getrange(id+1, p-1,0); // added the time necessary to go from that portal to the current one

        ll range_sum = getrange(id+2, p, 1); //  added the time necessary to pass every portal between them when the state was active
      
        res=add(res, ress);
        res=add(res, range_sum);
      
        upd(p,res,0); 

        if(s[i]==1){ // if the current state is active then we need to add the time necessary to go back
            dp[p]=add(dp[p],res);
        }

    }
    cout << add(dp[n],1);

    return 0;
}
