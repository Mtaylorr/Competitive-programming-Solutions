#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e6 + 5;
const int MOD = 1e9 + 7 ;

int h,w,g,e,n;
int x,y, we;
vector<vector<int> > edges;
set<pair<int,int> > graves, holes;
int u,v;
int dist[40*40];
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};

bool ingrid(int x, int y){
    return (x>=0 && x<w && y>=0 && y<h && (graves.count({x,y})==0));
}


void init(){
    graves.clear();
    edges.clear();
    holes.clear();
}

void bellmanford(){
    for(int i=0;i<n;i++){
        dist[i]=INT_MAX;
    }
    dist[0]=0;
    for(int i=0;i<n-1;i++){
        for(int j=0;j<edges.size();j++){
            x  = edges[j][0];
            y  = edges[j][1];
            int we = edges[j][2];
            if(dist[x]<INT_MAX)
                dist[y]=min(dist[y], dist[x]+we);
        }
    }
    int bf  = dist[n-1];
    bool cond=true;
    for(int j=0;j<edges.size();j++){
        x  = edges[j][0];
        y  = edges[j][1];
        int we = edges[j][2];
        if(dist[x]<INT_MAX && dist[y]>dist[x]+we){
            dist[y]=min(dist[y], dist[x]+we);
            cond=false;
        }

    }

    int af = dist[n-1];
    if(cond){
        if(af<INT_MAX){
            cout << af << endl;
        }else{
            cout << "Impossible" << endl;
        }
    }else{
        cout << "Never" << endl;
    }

}

int main()
{
    //freopen("input.txt", "r",stdin);
    while(1){
        scanf("%d%d",&w,&h);
        if(h==0 && w==0)
            break;
        init();
        scanf("%d",&g);
        n=h*w;
        for(int i=0;i<g;i++){
            scanf("%d%d",&u,&v);
            graves.insert({u,v});
        }
        scanf("%d",&e);
        for(int i=0;i<e;i++){
            scanf("%d%d",&u,&v);
            holes.insert({u,v});
            x=u*h+v;
            scanf("%d%d",&u,&v);
            y=u*h+v;
            scanf("%d",&we);
            edges.push_back({x,y,we});
        }
        for(int i=0;i<w;i++){
            for(int j=0;j<h;j++){
                if(!ingrid(i,j))
                    continue;
                if(holes.count({i,j}))
                    continue;
                if(i==w-1 && j==h-1)
                    continue;
                for(int k=0;k<4;k++){
                    int ni = i+dx[k];
                    int nj = j+dy[k];
                    if(ingrid(ni,nj)){
                        edges.push_back({i*h+j,ni*h+nj,1});
                    }
                }
            }
        }
        bellmanford();


    }
    return 0;
}
