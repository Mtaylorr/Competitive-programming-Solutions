#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;


const int N = 1e5+5;
const int MOD = 1e9 +7;


vector<int> up[1005], down[1005];
int B = 3000;
int a[N];
set<int> small, big;
int x[N], y[N], x_cnt[N], y_cnt[N];
int n,q;
int cum[N];

void init(){
    small.clear();
    big.clear();
    for(int i=1;i<=B;i++){
        up[i].clear();
        down[i].clear();
    }
}

void work(int u){
    for(int i=0;i<n;){
        if(a[i]>u)
            break;
        int j=i;
        int res=0;
        while(j<n && res+a[j]<=u){
            res+=a[j];
            j++;
        }
        up[u].pb(j-1);
        i=j;
    }
    for(int i=n-1;i>=0;){
        if(a[i]>u)
            break;
        int j=i;
        int res=0;
        while(j>=0 && res+a[j]<=u){
            res+=a[j];
            j--;
        }
        down[u].pb(j+1);
        i=j;
    }
}

int sum(int l, int r){
    return cum[r]-(l==0?0:cum[l-1]);
}

int getup(int x, int x_cnt){
    if(x_cnt==0)
        return -1;
    if(small.count(x)){
        int sz = min(x_cnt,(int)up[x].size());
        if(sz>0){
            return up[x][sz-1];
        }
        return -1;
    }else{
        int nb=0;
        int last=-10;
        for(int i=0;i<n;){
            if(a[i]>x)
                break;
            int r=n-1;
            int l=i;
            while(l<r-1){
                int md = (l+r)/2 ;
                if(sum(i,md)<=x){
                    l=md;
                }else{
                    r=md-1;
                }
            }
            nb++;
            if(sum(i,r)<=x){
                last=r;
            }else{
                last=l;
            }
            i=last+1;

            if(nb==x_cnt)
                break;
        }
        return last;
    }
}

int getdown(int x, int x_cnt){
    if(x_cnt==0)
        return n;
    if(small.count(x)){
        int sz = min(x_cnt,(int)down[x].size());
        if(sz>0){
            return down[x][sz-1];
        }
        return n;
    }else{
        int nb=0;
        int last=n+10;
        for(int i=n-1;i>=0;){
            if(a[i]>x)
                break;
            int l=0;
            int r=i;
            while(l<r-1){
                int md = (l+r)/2 ;
                if(sum(md,i)<=x){
                    r=md;
                }else{
                    l=md+1;
                }
            }
            nb++;
            if(sum(l,i)<=x){
                last=l;
            }else{
                last=r;
            }
            i=last-1;
            if(nb==x_cnt)
                break;
        }
        return last;
    }
}


int t;

int main(){
    freopen("input.txt", "r", stdin);
    //freopen("adhm.in", "r", stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        init();
        for(int i=0;i<n;i++){
            scanf("%d",&a[i]);
            cum[i]=a[i];
        }
        for(int i=1;i<n;i++)
            cum[i]+=cum[i-1];
        scanf("%d",&q);

        for(int i=0;i<q;i++){
            scanf("%d%d%d%d",&x[i],&x_cnt[i],&y[i], &y_cnt[i]);
            if(x[i]<=B)
                small.insert(x[i]);
            else
                big.insert(x[i]);
            if(y[i]<=B)
                small.insert(y[i]);
            else
                big.insert(y[i]);
        }

        for(auto u:small){
            work(u);
        }
        for(int i=0;i<q;i++){
            int lef = getup(x[i], x_cnt[i]);
            int rig = getdown(y[i], y_cnt[i]);
            if(lef+1>=rig){
                puts("Yes");
            }else{
                puts("No");
            }
        }

    }
    return 0;
}
