#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 + 5, E= 2e5+5;
const int MOD = 998244353 ;

int n,m;
ll p[N];
ll x[N];
vector<int> tmp;


int main() {
    ios::sync_with_stdio(0);
   // freopen("input.txt", "r", stdin);
    cin >> n >> m;
    for(int i=0;i<n;i++){
        cin >> p[i];
    }
    x[0]=-1e9;
    for(int i=1;i<=m;i++){
        cin >> x[i];
    }
    x[m+1]=2e9;
    sort(x, x+(m+2));
    int cur=0;
    ll ans=0;
    for(int i=0;i<=m;i++){
        tmp.clear();
        while(cur<n && 100*cur<=x[i+1]) {
            if(100*cur>x[i] && 100*cur <x[i+1]){
                tmp.pb(cur);
            }
            cur++;
        }
        if(tmp.size()==0){
            continue;
        }
        if(tmp.size()==1){
            ans=max(ans, p[tmp[0]]);
            continue;
        }
        int r=0;
        ll cursum=0;
        for(int j=0;j<tmp.size();j++){
            ll pos = 100*tmp[j];
            ll nexpos;
            if(abs(x[i+1]-pos)<abs(x[i]-pos)){
                break;
            }else if(abs(x[i+1]-pos)==abs(x[i]-pos)){
                nexpos=x[i+1]-1;
            }else{
                nexpos=pos+abs(pos-x[i]);
            }
            while(r<tmp.size() && abs(100*tmp[r]-x[i+1])>abs(100*tmp[r] -nexpos)){
                cursum+=p[tmp[r]];
                r++;
            }
            ans=max(ans, cursum);
            cursum-=p[tmp[j]];
        }

        r=tmp.size()-1;
        cursum=0;
        for(int j=tmp.size()-1;j>=0;j--){
            ll pos = 100*tmp[j];
            ll nexpos;
            if(abs(x[i+1]-pos)>abs(x[i]-pos)){
                break;
            }else if(abs(x[i+1]-pos)==abs(x[i]-pos)){
                nexpos=x[i]+1;
            }else{
                nexpos=pos-abs(pos-x[i+1]);
            }
            while(r>=0 && abs(100*tmp[r]-x[i])>abs(100*tmp[r] -nexpos)){
                cursum+=p[tmp[r]];
                r--;
            }
            ans=max(ans, cursum);
            cursum-=p[tmp[j]];
        }
    }
    cout << ans << endl;


    return 0;

}
