//https://codeforces.com/contest/1088/problem/D

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 2e5 + 5, M=1000 +5,E = 1e6 +5 ;
const int MOD = 1e9 + 7   ;
const double eps = 1e-7;

int id;
int val[2];
int x=0;
bool done[30];
int a=5,b=3;
int simulate(int c, int d){
    if((c^a)==(b^d)){
        return 0;
    }
    if((c^a)>(b^d)){
        return 1;
    }
    return -1;
}

int query(int c, int d){
    int x;
    cout << "? " << c << " "<< d << endl;
    cin >> x;
    //x= simulate(c,d);
    return x;
}


int main() {
    //freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int x = query(0,0);
    id = x;
    if(x!=0){
        int cur = 29;
        while(cur>=0 && x!=0){
            x = query(val[0]+(1<<cur), val[1]+(1<<cur));
            if(x==0)
                break;
            if(x!=id){
                done[cur]=1;
                if(id==1){
                    val[0]+=(1<<cur);
                }else{
                    val[1]+=(1<<cur);
                }
                int y = query(val[0], val[1]);
                id=y;
                if(y==0)
                    break;
            }
            cur--;
        }
    }
    for(int i=29;i>=0;i--){
        if(done[i])
            continue;
        int x = query(val[0]+(1<<i), val[1]);
        if(x==-1){
            val[0]+=(1<<i);
            val[1]+=(1<<i);
        }
    }
    cout << "! " << val[0] << " " << val[1] << endl;

    return 0;
}
