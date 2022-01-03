//https://vjudge.net/problem/UVA-1106
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5 +5 ;
const int MOD = 998244353 ;

int n,days;
ll b[N],d[N],s[N],sorted[N],p[N];
ll dp[N];

ll sub(const pair<ll,ll> &line, ll x){
    return line.fi*x + line.se;
}

double intersect(const pair<ll,ll> &a, const pair<ll,ll> &b){
    return (b.second-a.second+0.0)/(a.first-b.first+0.0);//(c2-c1)/(m1-m2);
}

bool useful(const pair<ll,ll> &b, const pair<ll,ll> &c,const pair<ll,ll> &a){
    return intersect(b,c)<intersect(c,a);
}

int main(){
    freopen("input.txt", "r",stdin);
    int ii=0;
    while(~scanf("%d%lld%d",&n,&s[0],&days),n||s[0]||days){
        for(int i=1;i<=n;i++){
            scanf("%lld%lld%lld%lld",&d[i],&b[i],&s[i],&p[i]);
            sorted[i]=i;
        }
        sort(sorted+1, sorted+n+1,[](int a , int b){return d[a]<d[b];});
        d[n+1]=days+1;
        dp[0]=0;
        sorted[n+1]=n+1;
        map<long long ,long long> lines;
        lines[0] = s[0];
        for(int i=1;i<=n+1;i++){
            int cur  = sorted[i];
            ll &r = dp[cur];
            r=0;
            long long x = d[cur];
            while(lines.size()>=2){
                auto second = lines.begin(), first = second++;
                long long p1 = sub(*first,x),p2 = sub(*second,x);
                if(p1>p2)
                    break;
                lines.erase(first);
            }
            r = sub(*lines.begin(),x);
            if(r<b[cur])
                continue;
            long long c = dp[cur]-b[cur] + s[cur] + - d[cur]*p[cur]-p[cur];
            long long m = p[cur];
            auto new_line = lines.emplace(m,c).first;
            new_line->second = max(new_line->second,c);
            auto b=new_line , a=new_line;
            if(b!=lines.begin()){
                b--;
            }
            if(a!=--lines.end())
                a++;
            if(a!=new_line && b!=new_line && !useful(*b , *new_line, *a)){
                lines.erase(new_line);
                continue;
            }
            while(new_line!=lines.begin()){
                b=new_line;
                b--;
                auto bb=b;
                if(b!=lines.begin())
                    bb--;
                else
                    break;
                if(!useful(*bb,*b, *new_line))
                    lines.erase(b);
                else
                    break;
            }
            while(new_line!=--lines.end()){
                a=new_line;
                a++;
                auto aa=a;
                if(a!=--lines.end())
                    aa++;
                else
                    break;
                if(!useful(*new_line,*a, *aa))
                    lines.erase(a);
                else
                    break;
            }
        }
        printf("Case %d: %lld\n",++ii, dp[n+1]);
    }
    return 0;
}
