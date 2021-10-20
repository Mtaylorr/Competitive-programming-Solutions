#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;


const int N = 1e3+5;

int t,n;

int a[N][N], b[N][N], grid[N][N];

void init(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            grid[i][j]=0;
    }
}

void draw0(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            if(a[i][j])
                grid[i][j]=1;
    }
}

void draw180(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(a[i][j])
                grid[n-1-i][n-1-j]=1;
        }
    }
}

void draw90(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(a[i][j])
                grid[j][n-1-i]=1;
        }
    }
}

void draw270(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(a[i][j])
                grid[n-j-1][i]=1;
        }
    }
}

void draw(int u){
    if(u==0)
        draw0();
    if(u==1)
        draw90();
    if(u==2)
        draw270();
    if(u==3)
        draw180();
}
bool isequal(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(b[i][j]!=grid[i][j])
                return 0;
        }
    }
    return 1;
}

int main(){
    freopen("input.txt", "r", stdin);
    //freopen("cipher.in", "r", stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++)
                scanf("%d",&a[i][j]);
        }

        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++)
                scanf("%d",&b[i][j]);
        }
        bool cond=false;
        for(int mask=0;mask<(1<<4);mask++){
            init();
            for(int i=0;i<4;i++){
                if((1<<i)&mask)
                    draw(i);
            }

            if(isequal())
                cond=true;
            if(cond)
                break;
        }
        if(cond)
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}
