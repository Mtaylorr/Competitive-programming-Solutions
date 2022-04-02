#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e5 + 5;
const int MOD = 1e9 + 7 ;

int p;
vector<string> s;
vector<int> v;
int l[N],r[N];
string t;
int x;

int main()
{
   // freopen("input.txt", "r",stdin);
    scanf("%d",&p);
    for(int i=0;i<p;i++){
        l[i]=1e9;
        r[i]=-1;
    }
    for(int i=0;i<p;i++){
        cin >> t;
        s.pb(t);
        cin >> x;
        v.pb(x*100);
    }
    bool cond=true;
    int mx=0;
    int mn=0;
    for(int i=0;i<p;i++){
        int u = min(100*100, v[i]+49);
        mx+=u;
        u =  max(0, v[i]-50);
        mn+=u;
    }
    for(int i=0;i<p;i++){
        int u = min(100*100, v[i]+49);
        mx-=u;
        u  = max(0, v[i]-50);
        mn-=u;

        for(int j=max(0,v[i]-50);j<=min(100*100,v[i]+49);j++){
            int rem = 100*100-j;
            if(rem>=mn && rem<=mx){
                l[i]=min(l[i],j);
                r[i]=max(r[i],j);
            }
        }
        if(l[i]>r[i]){
            cond=false;
            break;
        }
        u = min(100*100, v[i]+49);
        mx+=u;
        u = max(0, v[i]-50);
        mn+=u;
    }
    if(!cond){
        puts("IMPOSSIBLE");
        return 0;
    }
    for(int i=0;i<p;i++){
        cout << s[i]<<" "<< fixed << setprecision(2) << (1.0*l[i])/100.0<<" "<<(1.0*r[i])/100.0<< endl;
    }
    return 0;

}
