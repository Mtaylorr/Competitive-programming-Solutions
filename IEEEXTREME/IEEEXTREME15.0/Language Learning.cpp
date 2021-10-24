#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;


const int N = 2e5 +5 ;
const int MOD[] = {(int)1e9 + 7,(int) 1e9+9}, B[] = {29,37};

ll mul(ll u , ll v, ll mod=MOD[0]){
	return ((u%mod)*(v%mod))%mod;
}
ll add(ll u, ll v, ll mod=MOD[0]){
	return ((u%mod)+(v%mod)+mod)%mod;
}

ll sub(ll u, ll v , ll mod=MOD[0]){
	return ((u%mod)-(v%mod)+mod)%mod;
}


int tree[N];
int n,k;
int t;
pair<int,int> a[N];
char s[20];
map<pair<int,int> ,int> dp;
map<pair<int,int> , int> pos;
pair<int,int> gethash(){
    pair<int,int> res = {0,0};
    for(int i=0;s[i];i++){
        res.first = ((res.first*1ll*B[0]) %MOD[0] + (ll) (s[i]-'a'+1))%MOD[0];
        res.second = ((res.second*1ll*B[1]) %MOD[1] + (ll) (s[i]-'a'+1))%MOD[1];
    }
    return res;
}

void init(){
    for(int i=0;i<=n;i++){
        tree[i]=0;
    }
}

void upd(int x, int val){
    if(x==0)
        return ;
    for(;x<=n;x+=(x)&(-x)){
        tree[x]=add(tree[x],val);
    }
}

int get(int x){
    if(x<=0)
        return 0;
    int res=0;
    for(;x;x-=(x)&(-x)){
        res=add(res, tree[x]);
    }
    return res;
}
int getrange(int x , int y){
    if(x>y)
        return 0;
    return sub(get(y), get(x-1));
}


int main(){
    //freopen("input.txt", "r", stdin);
    cin >> t;
    while(t--){
        pos.clear();
        dp.clear();
        scanf("%d %d",&n,&k);
        for(int i=1;i<=n;i++){
            scanf("%s",s);
            a[i]=gethash();
        }
        init();
        int ans=0;
        for(int i=1;i<=n;i++){
            int r = max(0,i-k-1);
            int res = getrange(1,r);
            res=add(res,1);
            res=sub(res, dp[a[i]]);

            upd(i, res);
            dp[a[i]]=add(dp[a[i]],res);
            ans=add(ans,res);
            pos[a[i]]=i;
        }
        cout << ans << endl;
    }


    return 0;
}
