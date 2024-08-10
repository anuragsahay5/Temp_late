#include<bits/stdc++.h>
using namespace std;

class SegmentTree{
    vector<int>nodes;
    int size;

    void build(int idx,int low,int high,vector<int>&arr){
        if(low == high){
            nodes[idx] = arr[low];
            return;
        }
        int mid = (low+high)/2;
        build(2*idx+1,low,mid,arr);
        build(2*idx+2,mid+1,high,arr);

        nodes[idx] = nodes[2*idx+1] + nodes[2*idx+2]; // backtrack set value as operation on child (like + or AND, OR etc)
    }

    int getQuery(int idx,int l,int r,int low,int high){
        if(low>=l && high <=r) return nodes[idx]; // this node completly lie inside the given range
        int mid = (low+high)/2;
        if(r <= mid) return getQuery(2*idx+1,l,r,low,mid); // range lie in left child
        else if(l>mid)  return getQuery(2*idx+2,l,r,mid+1,high); // range lie in right child
 
        return getQuery(2*idx+1,l,mid,low,mid) + getQuery(2*idx+2,mid+1,r,mid+1,high); // lie in both child 
        
    }
    
public:
    SegmentTree(vector<int>&arr){
        
        size = arr.size();
        nodes.resize(4*size);
        build(0,0,size-1,arr);
    }

    int getSize(){
        return size;
    }

    void update(int idx,int val){
        int node_idx = 0; 
        int low=0,high=size-1,mid;
        while(low<=high){
            if(low == high) { // update idx
                nodes[node_idx] = val;
                break;
            }

            mid = (low+high)/2;
            node_idx*=2;
            node_idx++;
            if(idx <= mid){ // the update id lie in left
                 high = mid;
                 node_idx*=2;
                 node_idx+=1;
            }
            else{ // update index lie in right
                low = mid+1;
                node_idx*=2;
                node_idx+=1;
            }  
        }
        int parNode;
        while(node_idx > 0){ // keep updating parent after the child is updated
            parNode = (node_idx -1) /2;
            nodes[parNode] = nodes[2*parNode+1] + nodes[2*parNode+2];
            node_idx = parNode;
        }
    }

    int query(int l,int r){
        int low = 0,high=size-1;
        int idx = 0;
        return getQuery(0,l,r,low,high);
    }

};

int main(){
    vector<int>arr = {13,13,15,14,12};
    SegmentTree s1(arr);
    cout<<s1.query(0,4);
    s1.update(0,1);
    cout<<s1.query(0,4);
    return 0;
}