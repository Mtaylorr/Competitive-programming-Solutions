#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;


using namespace std;

const int N = 2e5+7;
int n,k;
ll ans[N];
char c;
ll hill[N][2], valley[N][2], rais[N], depress[N];
ll cumh[N][2], cumv[N][2];

int x,y;
int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d",&n);
    scanf("%d",&k);
    for(int i=0;i<k;i++){
        scanf(" %c",&c);
        scanf("%d %d",&x,&y);
        switch(c){
        case 'R':
            rais[x]++;
            rais[y+1]--;
            break;
        case 'D':
            depress[x]++;
            depress[y+1]--;
            break;
        case 'H':{
            if(abs(y-x)<=1){
                if(x==y)
                    ans[x]++;
                else {
                    ans[x]++;
                    ans[y]++;
                }
                break;
            }
            ll xx, yy;
            if((y-x)%2){
                xx=x+(y-x)/2;
                yy = y-(y-x)/2;
            }else{
                int d2 = (y-x)/2;
                xx = x+d2;
                yy = y-d2+1;
            }
            hill[x][0]++;
            hill[xx+1][0]-=1;//(xx-x +1 );
            cumh[xx+1][0]-=(xx-x +1 );
            hill[y][1]++;
            hill[yy-1][1]-=1;//(y-yy +1 );
            cumh[yy-1][1]-=(y-yy +1 );
            break;
        }
        case 'V':{
            if(abs(y-x)<=1){
                if(x==y)
                    ans[x]--;
                else {
                    ans[x]--;
                    ans[y]--;
                }
                break;
            }

            ll xx, yy;
            if((y-x)%2){
                xx=x+(y-x)/2;
                yy = y-(y-x)/2;
            }else{
                int d2 = (y-x)/2;
                xx = x+d2;
                yy = y-d2+1;
            }
            valley[x][0]++;
            valley[xx+1][0]-=1;
            cumv[xx+1][0]-=(xx-x +1 );
            valley[y][1]++;
            valley[yy-1][1]-=1;
            cumv[yy-1][1]-=(y-yy +1 );
            break;
        }

        }
    }
    ll cur=0;
    for(int i=1;i<=n;i++){
        cur+=rais[i];
        ans[i]+=cur;
    }

    cur=0;
    for(int i=1;i<=n;i++){
        cur+=depress[i];
        ans[i]-=cur;
    }

    cur=0;
    ll curnb = 0;
    for(int i=1;i<=n;i++){
        curnb+=hill[i][0];
        cur+=curnb+cumh[i][0];

        ans[i]+=cur;
    }

    cur=0;
    curnb = 0;
    for(int i=n;i>=1;i--){
        curnb+=hill[i][1];
        cur+=curnb+cumh[i][1];
        ans[i]+=cur;
    }

    cur=0;
    curnb = 0;
    for(int i=1;i<=n;i++){
        curnb+=valley[i][0];

        cur+=curnb+cumv[i][0];
        ans[i]-=cur;
    }

    cur=0;
    curnb = 0;
    for(int i=n;i>=1;i--){
        curnb+=valley[i][1];
        cur+=curnb+cumv[i][1];
        ans[i]-=cur;
    }
    for(int i=1;i<=n;i++){
            cout << ans[i] << "\n";
    }
    return 0;
}

