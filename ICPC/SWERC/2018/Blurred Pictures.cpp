#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e5 + 5;
const int MOD = 1e9 + 7 ;

int n;
int a[N], b[N];
multiset<int> as, bs;
bool ok(int l){
    as.clear();
    bs.clear();
    for(int i=0;i<l;i++){
        as.insert(-a[i]);
        bs.insert(b[i]);
    }
    int rs = 0;
    rs=max(rs, (*as.begin())+(*bs.begin())+1);
    for(int i=l;i<n;i++){
        as.erase(as.find(-a[i-l]));
        bs.erase(bs.find(b[i-l]));
        as.insert(-a[i]);
        bs.insert(b[i]);
        rs=max(rs, (*as.begin())+(*bs.begin())+1);
    }
    return rs>=l;
}

int main()
{
    //freopen("input.txt", "r",stdin);
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d%d",&a[i],&b[i]);
    }
    int l = 1;
    int r = n;
    while(l<r){
        int md  = (l+r+1)/2;
        if(ok(md)){
            l=md;
        }else{
            r=md-1;
        }
    }
    cout << l ;
    return 0;

}
