//https://codeforces.com/contest/1183/problem/F

#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5;
const int MOD = 1e9 + 7 ;

int t,n,a[N];
vector<int> v;
set<int> ss;

int ans=0;
int cursum=0;

void solve(int p=n-1,int  nb=0, int v1=-1,int v2=-1){
    if(nb<=3)
        ans=max(ans, cursum);
    if(nb==3 || p==-1)
        return;
    if(cursum+(3-nb)*v[p]<ans)
        return ;
    if(v1==-1){
        cursum+=v[p];
        solve(p-1,nb+1, v[p],v2);
        cursum-=v[p];
    }else if(v2==-1){
        if(v1%v[p]){
            cursum+=v[p];
            solve(p-1,nb+1, v1,v[p]);
            cursum-=v[p];
        }
    }else{
        if(v1%v[p] && v2%v[p]){
            cursum+=v[p];
            solve(p-1,nb+1, v1,v2);
            cursum-=v[p];
        }
    }
    solve(p-1,nb,v1,v2);
}

int main(){
    freopen("input.txt", "r",stdin);
    scanf("%d",&t);
    while(t--){
        v.clear();
        ss.clear();
        scanf("%d",&n);
        for(int i=0;i<n;i++){
            scanf("%d",&a[i]);
            if(!ss.count(a[i])){
                v.pb(a[i]);
            }
            ss.insert(a[i]);
        }
        n=v.size();
        sort(v.begin(),v.end());
        ans=cursum=0;
        solve();
        cout << ans << endl;

    }

    return 0;
}
