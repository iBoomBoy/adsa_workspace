#include <bits/stdc++.h>
using namespace std;

int cost(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A';
    else return c - 'a' + 26;
}

struct Edge {
    int u, v, w;
    bool exist;
    Edge(int _u, int _v, int _w, bool _exist) : u(_u), v(_v), w(_w), exist(_exist) {}
};

int findParent(vector<int>& parent, int x) {
    if (parent[x] == x) return x;
    return parent[x] = findParent(parent, parent[x]);
}

bool unionSet(vector<int>& parent, vector<int>& rank, int a, int b) {
    a = findParent(parent, a);
    b = findParent(parent, b);
    if (a == b) return false;
    if (rank[a] < rank[b]) swap(a, b);
    parent[b] = a;
    if (rank[a] == rank[b]) rank[a]++;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string countryInput, buildInput, destroyInput;
    cin >> countryInput >> buildInput >> destroyInput;

    vector<string> countryParts, buildParts, destroyParts;
    stringstream sc(countryInput), sb(buildInput), sd(destroyInput);
    string temp;
    while (getline(sc, temp, ',')) countryParts.push_back(temp);
    while (getline(sb, temp, ',')) buildParts.push_back(temp);
    while (getline(sd, temp, ',')) destroyParts.push_back(temp);

    int n = countryParts.size();
    vector<Edge> edges;
    int totalDestroy = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (countryParts[i][j] == '1') {
                edges.emplace_back(i, j, cost(destroyParts[i][j]), true);
                totalDestroy += cost(destroyParts[i][j]);
            } else {
                edges.emplace_back(i, j, cost(buildParts[i][j]), false);
            }
        }
    }

    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
    });

    vector<int> parent(n), rank(n, 0);
    iota(parent.begin(), parent.end(), 0);

    int mstCost = 0;
    int usedDestroy = 0;

    for (auto& e : edges) {
        if (unionSet(parent, rank, e.u, e.v)) {
            if (e.exist)
                usedDestroy += e.w;
            else
                mstCost += e.w;
        }
    }

    cout << totalDestroy - usedDestroy + mstCost << "\n";
    return 0;
}
