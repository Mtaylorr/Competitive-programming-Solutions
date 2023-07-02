#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define pi pair<ll,ll>
#define F first
#define S second
#define all(x) (x).begin(), (x).end()
#define alll(x) ((x).begin()+1), (x).end()
#define yes cout<<"YES"<<endl;
#define no cout<<"NO"<<endl;
#define mod mod
#define endl '\n'
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const ll mod = 998244353;

void io() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
}

template<class T>
bool ckmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

template<class T>
bool ckmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }

void nop() {
    cout << -1 << endl;
    return;
}



struct point{
    ll x{} , y{} ;
    point(){
        x = 0 ;
        y = 0 ;
    }
    point(ld xx , ld yy){
        x = xx ;
        y = yy ;
    }
    bool operator < (const point& b) const{
        return make_pair(x , y)< make_pair(b.x , b.y) ;
    }
    bool operator <= (const point& b) const{
        return make_pair(x , y)<= make_pair(b.x , b.y) ;
    }
    bool operator == (const point& b) const{
        return make_pair(x , y)== make_pair(b.x , b.y) ;
    }
    ll operator * (const point& b) const{
        return y*b.x - x*b.y ;
    }
    point operator - (const point& b) const{
        return point(x-b.x , y-b.y) ;
    }
    point operator + (const point& b) const{
        return point(x+b.x , y+b.y) ;
    }
    point operator * (const ld& k) const{
        return point(x*k , y*k) ;
    }
    point operator / (const ld& k) const{
        return point(x/k , y/k) ;
    }

    long long triangle(const point& b ,const point& c) const{
        return (b - *this) * (c - *this) ;
    }


};

void print(point p){
    cout<<"p.x = "<<p.x<<" p.y = "<<p.y<<endl;
}

const long double PI = acos(-1) ;

point read()
{
    point p ;
    cin>>p.x>>p.y ;
    return p ;
}


const int N = 1e6+5 ;
int py[N] , px[N] ;

struct node {
    long long val;
    node *l, *r;

    node(long long x) : val(x), l(nullptr), r(nullptr) {}
    node(node *ll, node *rr) {
        l = ll, r = rr;
        val = 0;
        if (l) val += l->val;
        if (r) val += r->val;
    }
    node(node *cp) : val(cp->val), l(cp->l), r(cp->r) {}
};

node* roots[N] ;

node *build(int l = 1, int r = N)
{
    if(l==r){
        return new node(0LL) ;
    }
    int md = (l+r)/2 ;
    return new node(build(l , md),build(md+1 , r)) ;

}

node* upd(node* p , int l , int r , int idx , int val)
{
    if(l==r){
        return new node(val) ;
    }
    int md = (l+r)/2 ;
    if(idx<=md) return new node(upd(p->l , l , md , idx , val),p->r) ;
    return new node(p->l,upd(p->r , md+1 , r , idx , val)) ;

}
void upd(int k , int idx , int val)
{
    roots[k] = upd(roots[k] , 1 , N , idx , val) ;
}

int a , b ;
long long query(node* p , int l = 1 , int r = N)
{
    if(b<l || a>r) return 0 ;
    if(a<=l && r<=b){
        return p->val ;
    }
    int md = (l+r)/2 ;
    return query(p->l , l , md) + query(p->r , md+1 , r) ;

}


set<pi> mp[N] ;
set<pi> mp1[N] ;


void solve() {
    int n ; cin>>n ;
    vector<point> v(n) , poly(n) ;
    for(int i = 0 ; i<n ; i++){
        v[i] = read() ;
        v[i].x++ ;
        v[i].y++ ;
    }
    vector<array<ll,3>> lines ;

    for(int i = 0 ; i<n ; i++){
        if(v[(i-1+n)%n].x==v[i].x){
            int yl = min(v[(i-1+n)%n].y , v[i].y) , yr = max(v[(i-1+n)%n].y , v[i].y) ;
            lines.pb({v[i].x , yl ,yr }) ;
            mp[v[i].x].insert({yl , yr}) ;
        }
        else{
            int xl = min(v[(i-1+n)%n].x , v[i].x) , xr = max(v[(i-1+n)%n].x , v[i].x) ;
            mp1[v[i].y].insert({xl , xr}) ;
        }
    }

    sort(all(lines)) ;
    reverse(all(lines)) ;
    roots[0] = build() ;
    for(int i = 0 ; i<lines.size() ; i++){
        roots[i+1] = roots[i] ;
        a = lines[i][1] , b = lines[i][1] ;
        upd(i+1 , lines[i][1] , 1 + query(roots[i+1])) ;
        a = lines[i][2] , b = lines[i][2] ;
        upd(i+1 , lines[i][2] , -1 + query(roots[i+1])) ;
    }
    int q ; cin>>q ;
    while(q--){
        point pii = read() ;
        pii.x++ ; pii.y++ ; 
        //need to check if it lies inside some lines
        auto it = mp[pii.x].upper_bound({pii.y,1e7}) ;
        if(it!=mp[pii.x].begin()){
            --it ;
            if(pii.y>=it->first && pii.y<=it->second){
                yes ;
                continue;
            }
        }
        it = mp1[pii.y].upper_bound({pii.x,1e7}) ;
        if(it!=mp1[pii.y].begin()){
            --it ;
            if(pii.x>=it->first && pii.x<=it->second){
                yes ;
                continue;
            }
        }
        // query the number of lines having their x>pii.x and l<=y and r>y
        int l = 0 , r = lines.size() -1 , pos = -1;
        while(l<=r){
            int md = (l+r)/2 ;
            if(lines[md][0]>pii.x){
                pos = md ;
                l = md+1 ;
            }
            else r = md-1 ;
        }
        a = 1 , b = pii.y ;
        int nb = query(roots[pos+1] , 1 , N) ;
        if(nb%2){
            yes ;
        }
        else{
            no ;
        }
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
#endif
    io();
    ll tt = 1;
    //cin>>tt ;
    while (tt--) {
        solve();
    }

    return 0;
}
