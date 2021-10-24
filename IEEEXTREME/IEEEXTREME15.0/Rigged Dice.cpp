//100%
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;


const int N = 1e5 +5 ;


int id[2];
int sixs[2];
int x,y;

int main(){
    //freopen("input.txt", "r", stdin);
    cin >> t;
    while(t--){
        cin >> n;
        id[0]=0;
        id[1]=1;
        sixs[0]=sixs[1]=0;
        for(int i=0;i<n;i++){
            cin >> x >> y;
            sixs[id[0]]+=x==6;
            if(x!=y){
                swap(id[0], id[1]);
            }
        }
        if(sixs[0]>sixs[1]){
            cout << 1 << endl;
        }else{
            cout << 2 << endl;
        }

    }
    return 0;
}
