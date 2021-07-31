// https://www.spoj.com/problems/MKTHNUM/
#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 1e5;
vector<int> seg[1<<18]; // number of leafs 1<<17
int arr[N], n,m,x,y,k;
 
void build(int ind=0, int nst=0, int nen=n-1){
    if(nst==nen){
        seg[ind].push_back(arr[nst]);
        return ;
    }
    int l = 2*ind+1;
    int r = l+1;
    int md = nst+(nen-nst)/2;
    build(l, nst, md);
    build(r, md+1, nen);
    merge(seg[l].begin(), seg[l].end(),
          seg[r].begin(), seg[r].end(),
          inserter(seg[ind] , seg[ind].begin()));
}
 
int query(int qst, int qen,int qval ,int ind=0, int nst=0, int nen=n-1 ){
    if(nst>qen || nen<qst){
        return 0;
    }
    if(nst>=qst && nen<=qen){
        return lower_bound(seg[ind].begin(), seg[ind].end(), qval) - seg[ind].begin();
    }
    int l = 2*ind+1;
    int r = l+1;
    int md = nst+(nen-nst)/2;
    int v1 = query(qst, qen, qval,l,nst, md);
    int v2 = query(qst,qen, qval, r, md+1, nen);
    return v1+v2;
}
int solve(int x, int y, int k){
    int st = -1e9;
    int en = 1e9;
    int md;
    while(st<en){
        md = st + (en-st)/2;
        int rs = query(x,y,md);
        if(rs>=k){
            en = md;
        }else{
            st = md+1;
        }
    }
    return st;
}
 
int main() {
    //FAST;

    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++){
        scanf("%d",arr+i);
    }
    build();
    while(m--){
        scanf("%d%d%d",&x,&y,&k);
        printf("%d\n", solve(x-1,y-1,k)-1);
    }
    return 0;
} 
