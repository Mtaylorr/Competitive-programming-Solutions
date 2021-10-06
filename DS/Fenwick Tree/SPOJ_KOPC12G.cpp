//https://www.spoj.com/problems/KOPC12G/
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;


using namespace std;

const int N = 505;

int tree[N][N];
int n,q,t;
char grid[N][N];
char str[N];
int a,b,c,d;
int ty;

void upd(int x, int y, int val){
    for(;x<=n;x+=(x)&(-x)){
        for(int u=y;u<=n;u+=(u)&(-u)){
            tree[x][u]+=val;
        }
    }
}

int get(int x, int y){
    int res=0;
    for(;x;x-=(x)&(-x)){
        for(int u=y;u;u-=(u)&(-u)){
            res+=tree[x][u];
        }
    }
    return res;
}

int getrange(int a, int b, int c, int d){
    return get(c,d) + get(a-1,b-1) - get(a-1, d) - get(c, b-1);
}

int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&q);
        for(int i=0;i<=n;i++){
            for(int j=0;j<=n;j++){
                tree[i][j]=0;
            }
        }
        for(int i=0;i<n;i++){
            scanf("%s" ,grid[i]);
            for(int j=0;j<n;j++){
                int id = grid[i][j]-'A' +1;
                upd(i+1, j+1, id);
            }
        }
        while(q--){
            scanf("%d",&ty);
            if(ty==0){
                scanf("%d %d %s", &a, &b, str);
                if(a==0){
                    for(int j=0;j<n;j++){
                        int id = grid[b][j]-'A'+1;
                        upd(b+1, j+1,-id);
                        grid[b][j]=str[j];
                        id = grid[b][j]-'A'+1;
                        upd(b+1, j+1,id);
                    }
                }else{
                    for(int j=0;j<n;j++){
                        int id = grid[j][b]-'A'+1;
                        upd(j+1, b+1,-id);
                        grid[j][b]=str[j];
                        id = grid[j][b]-'A'+1;
                        upd(j+1, b+1,id);
                    }
                }
            }else{
                scanf("%d%d%d%d",&a,&b,&c,&d);
                a++;b++;c++;d++;
                printf("%d\n", getrange(a,b,c,d));
            }
        }
    }


    return 0;
}
