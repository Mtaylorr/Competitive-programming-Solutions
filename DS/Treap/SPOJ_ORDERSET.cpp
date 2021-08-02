//https://www.spoj.com/problems/ORDERSET/
#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll, ll> pl;
typedef long double ld;
 
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(),(v).rend()
#define max(a, b) (a>b ? a : b)
#define min(a, b) (a<b ? a : b)
#define FAST ios::sync_with_stdio(0), cin.tie(0),cout.tie(0)
 
 
const int N = int(3e6) + 3;
const int MOD = int(1e9) + 7;
 
struct node;
extern node *emp;
 
enum DIR {
    L, R
};
 
struct node {
    long long v;
    int p, sz, freq;
    node *chld[2];
 
    node() {
        chld[L] = chld[R] = emp;
        v = 0;
        p = INT_MIN;
        freq = 0;
        sz = 0;
    }
 
    node(long long val, node *l = emp, node *r = emp) {
        p = rand();
        v = val;
        freq = 1;
        this->chld[L] = l;
        this->chld[R] = r;
        push_up();
    }
 
    void push_up() {
        sz = chld[L]->sz + chld[R]->sz + freq;
    }
 
};
 
node *emp = new node();
 
void rotate(node *&rt, DIR dir){
    node* p = rt;
    node* q = rt->chld[!dir];
    p->chld[!dir] = q->chld[dir];
    q->chld[dir]=p;
    p->push_up();
    q->push_up();
    rt=q;
}
 
void balance(node *&rt){
     if(rt->chld[L]->p >rt->p){
         rotate(rt, R);
     }else if(rt->chld[R]->p >rt->p)
         rotate(rt, L);
}
 
void erase(node *&rt, const long long & val){
    if (rt==emp){
        return;
    }
    if(rt->v==val){
        if(rt->freq>1){
            rt->freq--;
            rt->sz--;
        }
        int mxp=-1;
        int idx = 0;
        for(int i=0;i<2;i++){
            if(mxp<rt->chld[i]->p){
                mxp = rt->chld[i]->p;
                idx = i;
            }
            if(rt->chld[i]==emp){
                node* tmp =  rt->chld[!i];
                delete rt;
                rt = tmp;
                return;
            }
        }
        rotate(rt, (DIR)!idx);
        erase(rt, val);
        return;
    }else if(rt->v<val){
        erase(rt->chld[R], val);
    }else
        erase(rt->chld[L], val);
    rt->push_up();
}
 
void insert(node *&rt,const long long &val){
    if (rt==emp){
        rt = new node(val);
        return;
    }
    if(rt->v==val){
        rt->sz++;
        rt->freq++;
        return;
    }else if(rt->v<val){
        insert(rt->chld[R], val);
    }else
        insert(rt->chld[L], val);
    rt->push_up();
    balance(rt);
}
 
 
int getCount(node *&rt,const long long &val){
    if (rt==emp){
        return 0;
    }
    if(rt->v==val){
        return rt->freq;
    }else if(rt->v<val){
        return getCount(rt->chld[R], val);
    }
    return getCount(rt->chld[L], val);
}
 
const long long & getByIndex(node* rt, int ind){
    if(ind<rt->chld[L]->sz){
        return getByIndex(rt->chld[L], ind);
    }
    int sm = rt->chld[L]->sz+rt->freq;
    if(ind>=sm){
        return getByIndex(rt->chld[R], ind-sm);
    }
    return rt->v;
}
 
int lower_bound(node* rt, const long long &val){
    if(rt==emp)
        return 0;
    if(rt->v==val)
        return rt->chld[L]->sz;
    if(rt->v>val){
        return lower_bound(rt->chld[L],  val);
    }
    return lower_bound(rt->chld[R], val) + rt->freq+rt->chld[L]->sz;
}
 
void print(node *rt, int dpth=0){
    if(rt==emp)
        return;
    print(rt->chld[L],dpth+1);
    printf("%s%2d,%2d\n", string(dpth*5, ' ').c_str(), rt->v, rt->p);
    print(rt->chld[R], dpth+1);
}
int n, val;
char c;
int main() {
    node *rt = emp;
    cin >> n;
    while(n--){
        cin >> c >> val;
        switch(c){
            case 'I':
                if(getCount(rt, val)==0){
                    insert(rt, val);
                }
                break;
            case 'D':
                erase(rt, val);
                break;
            case 'K':
                if(val>rt->sz){
                    puts("invalid");
                }else{
                    cout << getByIndex(rt, val-1) << endl;
                }
                break;
            case 'C':
                cout << lower_bound(rt, val) << endl;
                break;
        }
    }
    return 0;
} 
