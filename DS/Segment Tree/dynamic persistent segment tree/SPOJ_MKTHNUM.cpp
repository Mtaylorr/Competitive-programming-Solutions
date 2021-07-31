// https://www.spoj.com/problems/MKTHNUM/
#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 1e5 + 5;
int a, n,m,x,y,k;
 
struct node;
extern node* empty;
struct node{
    int freq;
    node *l , *r;
    node(){
        freq=0;
        l=this;
        r=this;
    }
    node(int f  , node *l = empty , node *r=empty){
        freq=f;
        this->l=l;
        this->r=r;
    }
};
node* empty = new node;
 
node * insert(node *root,int val , int nst=-1e9,int nen=1e9){
 
    if(val>nen || val<nst){
        return root;
    }
    if(nst ==  nen){
        return new node(1);
    }
    int md = nst+(nen-nst)/2;
    node * ln = insert(root->l, val, nst,md );
    node * rn = insert(root->r, val , md+1, nen);
    return new node(ln->freq+rn->freq, ln, rn);
}
node* roots[N];
 
int query(node * rtst, node * rten, int k, int nst = -1e9, int nen=1e9){
 
    if(nst==nen){
        return nst;
    }
    int lsz = rten->l->freq - rtst->l->freq;
    int md = nst+(nen-nst)/2;
    if(k<=lsz){
        return query(rtst->l, rten->l, k, nst,md);
    }else{
        return query(rtst->r, rten->r, k-lsz, md+1, nen);
    }
}
 
int main() {
    //FAST;
    scanf("%d%d",&n,&m);
    roots[0]=empty;
    for(int i=1;i<=n;i++){
        scanf("%d",&a);
        roots[i] = insert(roots[i-1], a);
    }
    while(m--){
        scanf("%d%d%d",&x,&y,&k);
        printf("%d\n", query(roots[x-1],roots[y],k));
    }
    return 0;
} 
