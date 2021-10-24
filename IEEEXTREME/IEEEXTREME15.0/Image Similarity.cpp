//100%
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;


const int N = 1e5 +5 ;


char img1[32][32], img2[32][31], qu[32][32], tmp[32][32];
int r1, c1, r2,c2;
int r1q, c1q;

void show()
{
    cout <<"---------------\n";
    for(int i=0;i<r1q;i++){
        for(int j=0;j<c1q;j++){
            cout << qu[i][j];
        }
        cout << endl;
    }
    cout <<"---------------\n";
}
void init(){
    r1q=r1;
    c1q=c1;
    for(int i=0;i<r1;i++){
        for(int j=0;j<c1;j++){
            qu[i][j]=img1[i][j];
        }
    }
}

void cpy(){
    for(int i=0;i<r1q;i++){
        for(int j=0;j<c1q;j++){
            tmp[i][j]=qu[i][j];
        }
    }
}

void draw1(){
    cpy();
    for(int i=0;i<r1q;i++){
        for(int j=0;j<c1q;j++){
            qu[j][r1q-i-1]=tmp[i][j];
        }
    }
    swap(r1q, c1q);
}

void draw2(){
    cpy();
    for(int i=0;i<r1q;i++){
        for(int j=0;j<c1q;j++){
            qu[r1q-i-1][j]=tmp[i][j];
        }
    }
}

void draw3(){
    cpy();
    for(int i=0;i<r1q;i++){
        for(int j=0;j<c1q;j++){
            qu[i][c1q-j-1]=tmp[i][j];
        }
    }
}


void draw(int u){
    if(u==0)
        draw2();
    if(u==1)
        draw3();
}

int getans(){
    int res=0;
    for(int i=-r1q;i<r2;i++){
        for(int j=-c1q;j<c2;j++){
            int cur=0;
            for(int o=0;o<r1q;o++){
                for(int p=0;p<c1q;p++){
                    if(o+i>=0 && o+i<r2 && p+j>=0 && p+j<c2){
                        cur+=(qu[o][p]=='#' && qu[o][p]== img2[o+i][p+j]);
                    }
                }
            }
            res=max(res,cur);
        }
    }
    return res;
}
int t;

int main(){
    //freopen("input.txt", "r", stdin);
    cin >> t;
    while(t--){
        cin >> r1 >> c1;
        for(int i=0;i<r1;i++){
            cin >> img1[i];
        }
        cin>> r2 >> c2;
        for(int i=0;i<r2;i++){
            cin >> img2[i];
        }

        int mx=0;
        for(int u=0;u<1;u++){
            for(int mask=0;mask<4;mask++){
                init();
                for(int bit=0;bit<2;bit++){
                    if((1<<bit)&mask){
                        draw(bit);
                    }
                }
                for(int i=0;i<4;i++){
                    mx=max(mx, getans());
                    draw1();
                }
            }
            for(int i=0;i<r1;i++){
                for(int j=0;j<r1;j++){
                    tmp[i][j]=img1[i][j];
                }
            }
            for(int i=0;i<r2;i++){
                for(int j=0;j<c2;j++){
                    img1[i][j]=img2[i][j];
                }
            }
            for(int i=0;i<r1;i++){
                for(int j=0;j<c1;j++){
                    img2[i][j]=tmp[i][j];
                }
            }
            swap(r1,r2);
            swap(c1,c2);
        }
        cout << mx << endl;
    }
    return 0;
}
