//1000%
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;


const int N = 2e5 +5 ;
const int MOD = 1e9 + 7;


int t;
int nr, nb;
int e;
int par[N];
char c, c1,c2;
int y,x;
int d[N];
bool vis[N];

int getid(char c , int x){
    if(c=='R')
        return x;
    return nr+x;
}

void setpar(int u, char c , int x){
    par[u]=getid(c,x);
}

void calcdist(int u){
    int di=0;
    while(u!=-1 && !vis[u]){
        d[u]=min(di,d[u]);
        vis[u]=1;
        u=par[u];
        di++;
    }
}

void init(){
    for(int i=0;i<nr+nb;i++){
        vis[i]=0;
    }
}

int main(){
    //freopen("input.txt", "r", stdin);
    cin >> t;
    while(t--){
        cin >> nr >> nb >> e;
        par[0]=-1;
        for(int i=1;i<nr;i++){
            cin >> c >> x;
            x--;
            setpar(i,c,x);
        }
        par[nr]=-1;
        for(int i=nr+1;i<nr+nb;i++){
            cin >> c >> x;
            x--;
            setpar(i, c, x);
        }
        while(e--){
            cin >> c;
            if(c=='w'){
                cin >>c1 >> x >> c2 >> y;
                x--;
                y--;
                int u1 = getid(c1,x);
                int u2 = getid(c2,y);
                d[0]=1e9;
                d[nr]=1e9;
                init();
                calcdist(u1);
                init();
                calcdist(u2);
                if(d[0]>1e7 && d[nr]>1e7){
                    puts("NONE");
                }else if(d[0]==d[nr]){
                    printf("TIE %d\n", d[0]);
                }else if(d[0]<d[nr]){
                    printf("RED %d\n", d[0]);
                }else{
                    printf("BLUE %d\n", d[nr]);
                }
            }else{
                cin >>c1 >> x >> c2 >> y;
                x--;
                y--;
                int u = getid(c1,x);
                setpar(u, c2,y);
            }
        }
    }


    return 0;
}
