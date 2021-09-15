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
    freopen("weak_typing_chapter_3_input.txt", "r", stdin);
    freopen("output.txt","w", stdout);
    scanf("%d",&t);
    int tt=0;
    while(t--){
        v.clear();
        scanf("%d",&n);
        scanf("%s",s);
        int cntf=0;
        int ans=0;
        int lastdp=0;
        int lastx=-1;
        int lastxf=0;
        int curx=0;
        int sz=0;
        int pos=0;
        int cumdp=0;
        int cur=0;
        int cumcur=0;
        int firstfs=-1;
        int firstx=-1;
        for(int i=0;i<n;i++){
            if(s[i]=='F'){
                sz=add(sz,1);
                cntf=add(cntf,1);
                ans=add(ans, lastdp);
                cumdp=add(cumdp, lastdp);
                cumcur=add(cumcur, cur);
            }else if(s[i]=='X'){
                if(firstfs==-1){
                    firstfs=cntf;
                    firstx=1;
                }
                sz=add(sz,1);
                curx=1;
                int diff = (lastx==0);
                lastdp = add(lastdp,mul(diff, pos));
                ans=add(ans,lastdp);
                pos=sz;
                cntf=0;
                cur=add(cur, diff);
                cumdp=add(cumdp, lastdp);
                cumcur=add(cumcur, cur);
                lastx=1;
            }else if(s[i]=='O'){
                if(firstfs==-1){
                    firstfs=cntf;
                    firstx=0;
                }
                cntf=0;
                sz=add(sz,1);
                curx=0;
                int diff = (lastx==1);
                lastdp = add(lastdp,mul(diff, pos));
                ans=add(ans,lastdp);;
                pos=sz;
                cur=add(cur, diff);
                cumdp=add(cumdp, lastdp);
                cumcur=add(cumcur, cur);
                lastx=0;
            }else{
                if(cntf==sz)
                {
                    sz=mul(sz,2);
                    cntf=mul(cntf,2);
                    continue;
                }
                ll res=0;
                res=add(res, cumdp);
                res=add(res, mul(lastdp, firstfs));
                ll lastfsv = mul(cumcur, cntf);
                res=add(res, lastfsv);
                int newsz = sub(sz, firstfs);
                res=add(res, mul(lastdp, newsz));
                int diff = (firstx!=lastx);
                int newcumcur = add(cumcur , mul(newsz , diff));
                res=add(res,mul(newcumcur, pos));
                int newcur = add(cur,diff);
                int newlastdp = add(mul(2,lastdp),mul(newcur,pos));
                newlastdp = add(newlastdp, mul(cntf,cur));
                lastdp = newlastdp;
                int translation = mul(cur,sz);
                cumcur=add(cumcur,add(translation,newcumcur));
                cur = add(newcur,cur);
                sz = mul(sz,2);
                pos = sub(sz, cntf);
                ans=add(ans,res);
                cumdp=add(cumdp, res);
            }

        }

        printf("Case #%d: %lld\n",++tt,ans);
    }
    return 0;
}
