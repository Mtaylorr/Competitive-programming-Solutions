#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5+5;
const int MOD = 1e9 + 7 ;

int n,m;
int src[N], dest[N], l[N], r[N];
ll id[N];
int x,y;
unordered_set<ll> ss;
int main(){
    //freopen("input.txt", "r",stdin);
    while(1){
        scanf("%d%d",&n,&m);
        if(n==0 && m==0)
            break;
        int cnt=0;
        for(int i=0;i<n;i++){
            scanf("%d%d%d%d",&src[i],&dest[i],&l[i],&r[i]);
            r[i]+=l[i]-1;
            if(src[i]>dest[i])
                swap(src[i],dest[i]);
            id[i] = src[i]*1ll*(10000001) + dest[i];
        }
        for(int i=0;i<m;i++){
            scanf("%d%d",&x,&y);
            y+=x-1;
            ss.clear();
            for(int j=0;j<n;j++){
                if(!((y<l[j]) || (x>r[j]))){
                    ss.insert(id[j]);
                }
            }
            cout << ss.size() <<endl;
        }
    }
    return 0;
}
