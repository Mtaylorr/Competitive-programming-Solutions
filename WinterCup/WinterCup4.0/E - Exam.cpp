#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5+5;
const int MOD = 998244353  ;

int t;
int n,c[N],r[N];
int grid[2005][2005];
vector<int> vc,vr;

bool cmpc(int a, int b){
    return c[a]>c[b];
}
bool cmpr(int a, int b){
    return r[a]>r[b];
}


int main(){
    //freopen("input.txt", "r",stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        vr.clear();
        vc.clear();
        int sum1=0;
        int sum2=0;
        for(int i=0;i<n;i++){
            scanf("%d",&c[i]);
            vc.pb(i);
            sum1+=c[i];
        }
        for(int i=0;i<n;i++){
            scanf("%d",&r[i]);
            vr.pb(i);
            sum2+=r[i];
        }

        if(sum1!=sum2){
            puts("-1");
            continue;
        }
        sort(vc.begin(),vc.end(),cmpc);
        sort(vr.begin(),vr.end(),cmpr);
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                grid[i][j]=0;
            }
        }
        bool cond=true;
        for(int i=0;i<n;i++){
            sort(vc.begin(),vc.end(),cmpc);

            for(int j=0;j<r[vr[i]];j++){
                if(c[vc[j]]==0){
                    cond=false;
                    break;
                }
                c[vc[j]]--;
                grid[vr[i]][vc[j]]=1;
            }

        }
        if(!cond){
            puts("-1");
            continue;
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cout << grid[i][j] << " ";
            }
            cout << "\n";
        }
    }

    return 0;
}
