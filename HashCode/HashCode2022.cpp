#include <bits/stdc++.h>


#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 1e5+5, E=1e6;
const int MOD = 1e9 + 7 ;


struct contributor {
    int id;
    string name;
    map<string,int> skills;
    map<string,int> new_skills;

    contributor(int idd, string n, map<string,int> s)
    {
        id=idd;
        name=n;
        skills=s;
        new_skills= s;
    }
};

struct project {
    int id;
    string name;
    int days;
    int score;
    int best_before;
    vector<int> roles;
    vector<string> order;
    vector<int> contributors;

    project(int idd, string n, int d, int s, int bb, vector<int> r, vector<string> orders)
    {
        id=idd;
        name=n;
        days=d;
        score=s;
        best_before=bb;
        roles=r;
        order=orders;
    }
};

bool compare(project &a, project &b)
{
    if (a.score == b.score)
        return a.best_before < b.best_before;

    return a.score < b.score;
}

bool compare_score(project &a, project &b)
{
    if (a.score == b.score)
        return a.best_before < b.best_before;

    return a.score > b.score;
}

bool compare_bb(project &a, project &b)
{
    if (a.best_before == b.best_before)
        return a.score > b.score;

    return a.best_before < b.best_before;
}

bool compare_nb(project &a, project &b)
{
    if (a.order.size() == b.order.size())
        return a.score > b.score;

    return a.order.size()  < b.order.size() ;
}


int st[N];

ll c,p,n,level,d,b,r,s;
string name,skill;

vector<contributor> contributors;
vector<project> projects;

void init_contributors(){
    for(int i=0;i<c;i++){
        contributors[i].new_skills = contributors[i].skills;
    }
}

ll test(vector<int> &projs){
    memset(st, 0, sizeof(st));
    ll ans=0;
    init_contributors();
    for(auto i :projs){
        int minStartDate = 0;
      	map<string,int> maxSkill;
        if(projects[i].order.size()!=projects[i].contributors.size())
            return -1;
      	for(auto c: projects[i].contributors){
            for(auto u:contributors[c].new_skills){
              maxSkill[u.fi]=max(maxSkill[u.fi],u.se);
            }
        }
        for(int j=0;j<projects[i].order.size();j++){
            string skill = projects[i].order[j];
            int lv = projects[i].roles[j];
            int id = projects[i].contributors[j];
            if( lv > 1+ contributors[id].new_skills[skill]){
                return -1;
            }
            if(lv == 1+ contributors[id].new_skills[skill] && maxSkill[skill]<lv){
                return -1;
            }
        }
        for(auto c: projects[i].contributors){
            minStartDate=max(minStartDate, st[c]);
        }
        for(auto c: projects[i].contributors){
            st[c] = minStartDate + projects[i].days;
        }
        int endDate = minStartDate + projects[i].days;
        if(endDate<=projects[i].best_before){
            ans+=projects[i].score;
        }else{
            int diff = endDate-projects[i].best_before;
            ans+=max(0,projects[i].score-diff);
        }
        for(int j=0;j<projects[i].order.size();j++){
            string skill = projects[i].order[j];
            int lv = projects[i].roles[j];
            int id = projects[i].contributors[j];
            if(lv <= 1 + contributors[id].new_skills[skill]){
                contributors[id].new_skills[skill]++;
            }
        }
    }
    return ans;
}

map<string,vector<pair<int,int> > > globalSkills;


#define neig(u,e,v) for(int e=head[u],v;(~e)&&(v=to[e],1);e=nxt[e])
int head[N], nxt[E], to[E],edgcnt=0;
ll cap[E], cst[N];
int src, snk , vis[N], vid=0,par[N];
bool used[N];
ll dist[N];
ll fl[N];
void addEdge(int a, int b, ll cs, ll cp){
    nxt[edgcnt]=head[a];
    to[edgcnt]=b;
    cap[edgcnt]=cp;
    cst[edgcnt]=cs;
    head[a]=edgcnt++;
}

void addAug(int a, int b,ll cs,  ll fcp, ll rcp=0){
    addEdge(a,b,cs, fcp);
    addEdge(b,a,-cs, rcp);
}
void init(){
    memset(head, -1, n*sizeof(head[0]));
    edgcnt=0;
}

bool bellmanford(){
    queue<int> q;
    memset(dist, 63, n*sizeof(dist[0]));
    dist[src]=0;
    vis[src]=++vid;
    fl[src]=1e18;
    fl[snk]=0;
    q.push(src);
    while(q.size()){
        int s = q.size();
        while(s--){
            int u = q.front();
            q.pop();
            vis[u]=0;
            neig(u,e,v){
                if(!cap[e])
                    continue;
                ll d = max(dist[u],cst[e]);
                if(d<dist[v]){
                    dist[v]=d;
                    fl[v]=min(fl[u], cap[e]);
                    par[v]=e;
                    if(vis[v]!=vid){
                        vis[v]=vid;
                        q.push(v);
                    }
                }else if(dist[v]==d && min(fl[u], cap[e])>fl[v]){
                    dist[v]=d;
                    fl[v]=min(fl[u], cap[e]);
                    par[v]=e;
                    if(vis[v]!=vid){
                        vis[v]=vid;
                        q.push(v);
                    }
                }
            }
        }
    }
    return fl[snk]>0;

}

pair<ll,ll> mcmf(){
    ll f=0, c=0;
    while(bellmanford()){
        f+=fl[snk];
        c=max(c,fl[snk]*dist[snk]);
        for(int u=snk;u!=src;u=to[par[u]^1]){
            cap[par[u]]-=fl[snk];
            cap[par[u]^1]+=fl[snk];
        }
    }
    return {f,c};
}

int main()
{
    //freopen("a_an_example.in.txt", "r",stdin);
    freopen("b_better_start_small.in.txt", "r",stdin);
    //freopen("c_collaboration.in.txt", "r",stdin);
    //freopen("d_dense_schedule.in.txt", "r",stdin);
    //freopen("e_exceptional_skills.in.txt","r",stdin);
    //freopen("f_find_great_mentors.in.txt", "r",stdin);
    //freopen("output.txt", "w", stdout);

    cin>>c>>p;


    for (int i=0 ; i<c ; i++)
    {
        cin>>name>>n;
        map<string,int> skills;
        for (int j=0 ; j<n ; j++)
        {
            cin>>skill>>level;
            skills[skill]=level;
            globalSkills[skill].pb({level,i});
        }

        contributor con = contributor(i,name,skills);
        contributors.pb(con);
    }

    for (int i=0 ; i<p ; i++)
    {
        cin>>name>>d>>s>>b>>r;
        vector<int> roles;
        vector<string> order;
        bool cond=true;
        for (int j=0 ; j<r ; j++)
        {
            cin>>skill>>level;
            roles.pb(level);
            order.pb(skill);
        }
        project proj = project(i,name,d,s,b,roles,order);
        projects.pb(proj);
    }

    sort(projects.begin(), projects.end(), compare_score);

    vector<int> solvedProjects;
    memset(st, 0, sizeof(st));

    int ind=-1;
    for (auto &project:projects)
    {
        memset(used, 0,sizeof(used));
        project.contributors.assign(project.order.size(),-1);
        ++ind;
        n = 1 + 1 + c + project.order.size();
        init();
        src = n-1;
        snk = n-2;
        for(int i=0;i<c;i++){
            addAug(src, i,st[i],1);
        }
        for(int j=0;j<project.order.size();j++){
            addAug(c+j, snk ,0, 1);
            string skill = project.order[j];
            for(auto u:globalSkills[skill]){
                int id = u.se;
                if(contributors[id].new_skills[skill]>=project.roles[j]){
                    addAug(id, c+j, 0,1,0);
                }
            }
        }

        pair<ll,ll> res = mcmf();
        map<string,int> maxSkill;
        while(res.fi!=project.order.size()){
            for(int u=0;u<c;u++){
                if(used[u])
                    continue;
                neig(u,e,v){
                    if(v>=c && v!=src && cap[e]==0){
                        used[u]=1;
                        project.contributors[v-c]=u;
                        for(auto y:contributors[u].new_skills){
                            maxSkill[y.fi]=max(maxSkill[y.fi], y.se);
                        }
                        break;
                    }
                }
            }
            n = 1 + 1 + c + project.order.size();
            init();
            src = n-1;
            snk = n-2;
            for(int i=0;i<c;i++){
                if(used[i])
                    continue;
                addAug(src, i,st[i],1);
            }
            for(int j=0;j<project.order.size();j++){
                if(project.contributors[j]!=-1)
                    continue;
                addAug(c+j, snk ,0, 1);
                string skill = project.order[j];
                if(maxSkill[skill]<project.roles[j])
                    continue;
                for(auto u:globalSkills[skill]){
                    int id = u.se;
                    if(used[id])
                        continue;
                    if(contributors[id].new_skills[skill]>=project.roles[j]-1){
                        addAug(id, c+j, 0,1,0);
                    }
                }
            }


            pair<ll,ll> newres = mcmf();
            if(newres.fi==0)
                break;
            res.fi+=newres.fi;
            res.se=max(res.se, newres.se);

        }
        if(res.fi!=project.order.size())
            continue;
        int endDate = res.se + project.days;
        int score = 0;
        if(endDate<=project.best_before){
            score+=project.score;
        }else{
            int diff = endDate-project.best_before;
            score+=max(0,project.score-diff);
        }
        if(score==0)
            continue;
        solvedProjects.pb(ind);

        for(int u=0;u<c;u++){
            if(used[u])
                continue;
            neig(u,e,v){
                if(v>=c && v!=src && cap[e]==0){
                    string skill = project.order[v-c];
                    project.contributors[v-c]=u;

                    break;
                }
            }
        }

        for(auto u:project.contributors){
            st[u]=endDate;
        }
        for(int j=0;j<project.order.size();j++){
            int id = project.contributors[j];
            string skill = project.order[j];
            if(contributors[id].new_skills[skill]==project.roles[j] || contributors[id].new_skills[skill]==project.roles[j]-1){
                contributors[id].new_skills[skill]++;
            }

        }

    }
    cout << test(solvedProjects)<< endl;
    /*cout << solvedProjects.size() << endl;
    for(auto i:solvedProjects){
        cout << projects[i].name  << endl;
        for(auto j:projects[i].contributors){
            cout << contributors[j].name << " ";
        }
        cout << endl;
    }*/

    return 0;
}
