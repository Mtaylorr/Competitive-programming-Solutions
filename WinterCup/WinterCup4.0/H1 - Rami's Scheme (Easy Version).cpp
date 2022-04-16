#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e6+5 + 5;
const int MOD = 1e9 + 7;


int r;
int p,a,b;
int u0,u1, v0,v1;
int x0,x1;
map<pair<int,pair<pair<int,int>,pair<int,int> > >,int> pos;
int s;
vector<int> v;
vector<int> wv;
int n[N];
int ans[N];


int main() {
    //ios::sync_with_stdio(0);
    //freopen("input.txt", "r", stdin);
    scanf("%d%d%d",&p,&a,&b);
    scanf("%d%d",&x0,&x1);
    u0=x0;
    u1=x1;
    int w = u1;
    int tmp;
    int r=1e9;
    pair<int,pair<pair<int,int>,pair<int,int> > >pa;
    for(int i=2;;i++){
        tmp = u1;
        u1 = ((a*u1)+(b*u0))%p;
        u0=tmp;
        w+=(i*u1);
        w%=p;
        pa={w,{{u0,u1},{((i-1)*u0)%p,((i)*u1)%p}}};
        if(pos.count(pa)){
            r = min(r,i-pos[pa]);
            break;
        }else{
            pos[pa]=i;
        }
    }


    cin >> s;
    for(int i=0;i<s;i++){
        scanf("%d",&n[i]);
        v.pb(i);
    }
    sort(v.begin(),v.end(),[](int x, int y){return n[x]<n[y];});
    u0=x0;
    u1=x1;
    w = u1;
    int cur=1;
    for(auto u:v){
        if(n[u]==0){
            ans[u]=0;
        }else{
            while(cur<n[u]){
                tmp = u1;
                u1 = ((a*u1)+(b*u0))%p;
                u0=tmp;
                cur++;
                w+=u1*cur;
                w%=p;
            }
            ans[u]=w;
        }
    }
    cout << r << endl;
    for(int i=0;i<s;i++){
        cout << ans[i] << " ";
    }

    return 0;

}
