#include <bits/stdc++.h>
using namespace std;

int letterCost(char c){
    if('A'<=c && c<='Z') return c - 'A';
    return c - 'a' + 26;
}

struct Edge{
    int u, v, w;
    Edge(int _u,int _v,int _w):u(_u),v(_v),w(_w){}
};

int findp(vector<int>& p,int x){ return p[x]==x? x : p[x]=findp(p,p[x]); }
bool unite(vector<int>& p, vector<int>& r, int a,int b){
    a = findp(p,a); b = findp(p,b);
    if(a==b) return false;
    if(r[a]<r[b]) swap(a,b);
    p[b]=a;
    if(r[a]==r[b]) r[a]++;
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string countryStr, buildStr, destroyStr;
    if(!(cin >> countryStr >> buildStr >> destroyStr)) return 0;

    vector<string> country, build, destroy;
    {
        string tmp; stringstream sc(countryStr), sb(buildStr), sd(destroyStr);
        while(getline(sc,tmp,',')) country.push_back(tmp);
        while(getline(sb,tmp,',')) build.push_back(tmp);
        while(getline(sd,tmp,',')) destroy.push_back(tmp);
    }
    int n = (int)country.size();

    long long S = 0;
    vector<Edge> edges; edges.reserve(n*(n-1)/2);

    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(country[i][j]=='1'){
                int d = letterCost(destroy[i][j]);
                S += d;
                edges.emplace_back(i, j, -d);
            }else{
                int b = letterCost(build[i][j]);
                edges.emplace_back(i, j, +b);
            }
        }
    }

    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b){
        return a.w < b.w;
    });

    vector<int> parent(n), rankv(n,0);
    iota(parent.begin(), parent.end(), 0);

    long long mst_weight = 0;
    for(const auto& e : edges){
        if(unite(parent, rankv, e.u, e.v)){
            mst_weight += e.w;
        }
    }

    cout << (S + mst_weight) << "\n";
    return 0;
}
