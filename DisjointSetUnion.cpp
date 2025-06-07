#include <bits/stdc++.h>
using namespace std;

class DisjointSetUnion
{
private:
    vector<int> parent, size, rank;

public:
    DisjointSetUnion(int n)
    {
        rank.resize(n + 1, 0);
        size.resize(n + 1);
        parent.resize(n + 1);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int findUlimateParent(int node)
    {
        if (node == parent[node])
        {
            return node;
        }
        return parent[node] = findUlimateParent(node);
    }

    void unionBySize(int u, int v)
    {
        int ulp_u = findUlimateParent(u);
        int ulp_v = findUlimateParent(v);

        if (ulp_u == ulp_v)
            return;

        if (size[ulp_u] < size[ulp_v])
        {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        else
        {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }

    void unionByRank(int u, int v)
    {
        int ulp_u = findUlimateParent(u);
        int ulp_v = findUlimateParent(v);

        if (ulp_u == ulp_v)
            return;

        if (rank[ulp_u] < rank[ulp_v])
        {
            parent[ulp_u] = ulp_v;
        }
        else if (rank[ulp_v] < rank[ulp_u])
        {
            parent[ulp_v] = ulp_u;
        }
        else
        {
            parent[ulp_u] = ulp_v;
            rank[ulp_v]++;
        }
    }
};

int main()
{
    DisjointSetUnion dsu(7);

    auto printState = [&](string step) {
        cout << "After " << step << ":\n";
        for (int i = 1; i <= 7; i++) {
            cout << "Node: " << i
                 << ", Parent: " << dsu.findUlimateParent(i)
                 //<< ", Rank: " << dsu.rank[i] 
                 << endl;
        }
        cout << "-------------------\n";
    };

    dsu.unionByRank(1, 2);
    printState("union(1,2)");

    dsu.unionByRank(2, 3);
    printState("union(2,3)");

    dsu.unionByRank(4, 5);
    printState("union(4,5)");

    dsu.unionByRank(6, 7);
    printState("union(6,7)");

    dsu.unionByRank(5, 6);
    printState("union(5,6)");

    dsu.unionByRank(3, 7);
    printState("union(3,7)");

    return 0;
}
