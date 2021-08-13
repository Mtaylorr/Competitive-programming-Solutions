//https://www.spoj.com/problems/ZQUERY/
#pragma GCC optimize("03")
#include <bits/stdc++.h>
 
using namespace std;
 
typedef int ll;
 
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(),(v).rend()
#define min(a, b) (a<b ? a : b)
#define FAST ios::sync_with_stdio(0), cin.tie(0),cout.tie(0)
 
 
const int N = int(5e5) + 3;
const int MOD = int(1e9) + 7;
 
int bs;
int n,m;
int l[N],r[N];
multiset<int> lens;
vector<int> v;
int a[N], ans[N];
deque<int> dq[N];
int sum=0;
int mi=1e7;
int up, lo;
 
void add(const int & cur){
    sum=a[cur]-mi;
    if(dq[sum].size()==0){
        dq[sum].push_back(cur);
    }else{
        up = dq[sum].back();
        lo = dq[sum].front();
        lens.erase(lens.find(lo-up));
        if(cur<dq[sum].front()){
            dq[sum].push_front(cur);
        }else{
            dq[sum].push_back(cur);
        }
    }
    up = dq[sum].back();
    lo = dq[sum].front();
    lens.insert(lo-up);
}
 
void rem(const int & cur){
    sum=a[cur]-mi;
 
    if(dq[sum].size()>=1) {
        up = dq[sum].back();
        lo = dq[sum].front();
        lens.erase(lens.find(lo - up));
    }
    if(dq[sum].front()==cur){
        dq[sum].pop_front();
    }else{
        dq[sum].pop_back();
    }
    if(dq[sum].size()){
        up = dq[sum].back();
        lo = dq[sum].front();
        lens.insert(lo-up);
    }
}
 
int getans(){
    return (lens.empty()?0:*lens.begin());
}
 
 
bool cmp(int &x , int &y){
    if(l[x]/bs!=l[y]/bs){
        return l[x]<l[y];
    }
    return r[x]<r[y];
}
 
 
int main() {
    scanf("%d%d",&n,&m);
    int ss=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        ss+=a[i];
        a[i]+=a[i-1];
        mi=min(mi,ss);
    }
 
    sum=-mi;
    for(int i=0;i<m;i++){
        v.pb(i);
        scanf("%d%d",&l[i],&r[i]);
    }
    bs = sqrt(n);
    sort(all(v), cmp);
    int curl=1;
    int curr=0;
    for(auto i:v){
        int li = l[i];
        int ri = r[i];
        while(curr<ri){
            curr++;
            add(curr);
        }
        while(curl>=li){
            curl--;
            add(curl);
        }
        while(curr>ri){
            rem(curr);
            curr--;
        }
        while(curl<li-1){
            rem(curl);
            curl++;
        }
        ans[i]=getans();
    }
    for(int i=0;i<m;i++){
        printf("%d\n", -ans[i]);
    }
} 
