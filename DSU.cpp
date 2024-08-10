#include <bits/stdc++.h>
using namespace std;

class DSU
{
    int nodes;
    int number_of_components;
    vector<int> ultimate_parent;
    vector<int> size;

public:
    DSU(int n)
    {
        nodes = n;
        number_of_components = n;
        ultimate_parent.resize(nodes + 1);
        int i = 0;
        for (int &x : ultimate_parent)
            x = i++;

        size.resize(nodes + 1, 1);
    }

    int findUltimateParent(int u)
    {
        int node = u;
        while (ultimate_parent[node] != node)
        {
            node = ultimate_parent[node];
        }
        return ultimate_parent[u] = node;
    }

    void unionBySize(int u, int v)
    {
        int u_pu = findUltimateParent(u);
        int u_pv = findUltimateParent(v);

        if (size[u_pu] >= size[u_pv])
        {
            ultimate_parent[u_pv] = ultimate_parent[u_pu];
            size[u_pu] += size[u_pv];
        }
        else
        {
            ultimate_parent[u_pu] = ultimate_parent[u_pv];
            size[u_pv] += size[u_pu];
        }
        number_of_components--;
    }

    bool belongToSame(int u, int v)
    {
        return findUltimateParent(u) == findUltimateParent(v);
    }

    int countComponents(){
        return number_of_components;
    }

};

int main(){


    // DSU d1 = DSU(9);

    // vector<pair<int,int>>edges = {{8,7},{9,3},{7,6},{1,2},{3,6},{9,7},{3,4},{8,9},{1,8},{2,3},{4,5},{6,5},{2,8},{4,6}};

    // for(pair<int,int>&edge : edges){
    //     if(!d1.belongToSame(edge.first,edge.second)) d1.unionBySize(edge.first,edge.second);
    //     for(int &x : d1.ultimate_parent) cout<<x<<" ";
    //     cout<<endl;
    // }

    

    
 

    return 0;
}
