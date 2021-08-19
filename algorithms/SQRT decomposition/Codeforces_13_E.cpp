//https://codeforces.com/contest/13/problem/E
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define pb push_back
#define fi first
#define se second

const int N = 1e5 +2;

#define all(v) (v).begin(), (v).end()

int n,m;
int a[N];
int x,y;
int ty;
int nxt[N], cnt[N];


int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }

    int B = 20;
    for(int i=n-1;i>=0;i--){
        int x = a[i]+i;
        if((x>=n) || x/B!=i/B){
            nxt[i]=i;
            cnt[i]=1;
        }else{
            nxt[i]=nxt[x];
            cnt[i]=cnt[x]+1;
        }
    }
    int l,lb,r;
    while(m--){
        scanf("%d",&ty);
        if(ty==0){
            scanf("%d%d",&x,&y);
            --x;
            a[x]=y;
            lb = x/B;
            l = lb*B;
            r = min( n-1,(lb+1)*B-1);
            for(int i=x;i>=l;i--){
                int newx=a[i]+i;
                if(newx>r) {
                    nxt[i]=i;
                    cnt[i]=1;
                }else{
                    nxt[i]=nxt[newx];
                    cnt[i]=cnt[newx]+1;
                }
            }
        }else{
            cin >> x;
            --x;
            int ans=0;
            int ansind = x;
            while(x<n){
                ansind = nxt[x];
                ans+=cnt[x];
                x = nxt[x]+a[nxt[x]];
            }
            printf("%d %d\n", ansind+1, ans);
        }
    }


    return 0;
}
