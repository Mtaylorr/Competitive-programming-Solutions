//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=565
#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5+5;
const int MOD = 998244353 ;


int n, k, a[55];
int bst;
int cur;
int sol;


int main(){
    freopen("input.txt", "r",stdin);
    while(~scanf("%d",&n)){
        scanf("%d",&k);
        for(int i=0;i<k;i++){
            scanf("%d",&a[i]);
        }
        bst=0;
        for(int msk=0;msk<(1<<k);msk++){
            cur=0;
            for(int j=0;j<k;j++){
                if((msk>>j)&1){
                    cur+=a[j];
                }
            }
            if(cur<=n && cur>bst){
                bst=cur;
                sol=msk;
            }
        }
        for(int i=0;i<k;i++){
            if((sol>>i)&1){
                cout << a[i]<< " ";
            }
        }
        cout << "sum:" << bst << endl;

    }
    return 0;
}
