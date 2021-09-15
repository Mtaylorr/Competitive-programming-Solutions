#include <bits/stdc++.h>

using namespace std;
const int N = 2e6+5;
const int MOD = 1e9 + 7;

#define fi first
#define se second
#define pb push_back

typedef long long ll;

ll mul(ll u , ll v, ll mod=MOD){
	return ((u%mod)*(v%mod))%mod;
}
ll add(ll u, ll v, ll mod=MOD){
	return ((u%mod)+(v%mod)+mod)%mod;
}

ll sub(ll u, ll v , ll mod=MOD){
	return ((u%mod)-(v%mod)+mod)%mod;
}

int t;
int n;
char s[N];
vector<pair<char,int> > v;

int main(){
    freopen("weak_typing_chapter_2_input.txt", "r", stdin);
    freopen("output.txt","w", stdout);
    scanf("%d",&t);
    int tt=0;
    while(t--){
        v.clear();
        scanf("%d",&n);
        scanf("%s",s);
        int cnt=0;
        for(int i=0;i<n;i++){
            if(s[i]=='F')
                cnt++;
            else {
                v.pb({s[i],cnt});
                cnt=0;
            }
        }
        int cur=0;
        int ans=0;
        int last=0;
        int nb=0;
        int cumcur=0;
        if(v.size()>1){
            for(int i=0;i<v.size();i++){

                cur+=(i>0 && v[i].fi!=v[i-1].fi);
                ans=add(ans, mul(v[i].se,last));
                ll curdp = mul(cur, nb);
                curdp = sub(curdp, cumcur);
                ans=add(ans, curdp);
                cumcur =add(cumcur, mul(cur, v[i].se+1));
                last=curdp;
                nb+=v[i].se+1;
            }
        }
        if(cnt)
            ans=add(ans, mul(last, cnt));
        printf("Case #%d: %lld\n",++tt,ans);
    }
    return 0;
}
