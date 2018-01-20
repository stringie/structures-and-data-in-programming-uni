#include "iostream"
using namespace std;

struct VertexList{
    int v;
    VertexList* next;

    VertexList(int v_, VertexList* next_ = nullptr) : v(v_), next(next_) {}
};

struct Vertex
{
    int u;
    VertexList* successors;
    Vertex* next;  

    Vertex(int u_, VertexList* succ = nullptr, Vertex* v = nullptr) : u(u_), successors(succ), next(v) {}
};

// return length of list
int length(VertexList* l) {
    if (l == nullptr)
        return 0;
    return 1 + length(l->next);
}

//remove element from list
void remove(Vertex*& node, int elem){    
    if(node == nullptr){
        return;
    }

    remove(node->next, elem);
    if (node->u == elem){
        node = node->next;
    }
}

VertexList* longestPath(Vertex* graph, int u, int v){
    //base
    if (u == v){
        return new VertexList{u, nullptr};
    }

    //create temp copy and go to vertex u position in copy
    Vertex* tmp = graph;
    while (tmp != nullptr && tmp->u != u){
        tmp = tmp->next;
    }

    //create max list and if verex u not found in temp copy of graph, return max(nullptr)
    VertexList* max = nullptr;
    if (tmp == nullptr){
        return max;
    }
    //get successors temp list
    VertexList* tmplist = tmp->successors;
    //copy graph and remove vertex u from it to get rid of cycles
    Vertex* copyGraph = graph;
    remove(copyGraph, tmp->u);
    //update max from each following longest path
    while (tmplist != nullptr){
        VertexList* somePath = longestPath(copyGraph, tmplist->v, v);
        if (length(max) < length(somePath)){
            max = somePath;
        }
        tmplist = tmplist->next;
    }

    //construct longest path list or return nullptr
    if (max != nullptr){
        return new VertexList{u, max};
    }else{
        return max;
    }
}

using V = Vertex;
using VL = VertexList;

int main(){
    // Vertex* g = new Vertex{1, new VertexList{2, new VertexList{3, nullptr}}, new Vertex{2, new VertexList{4, nullptr}, new Vertex{3, new VertexList{5, nullptr}, new Vertex{4, new VertexList{1, new VertexList{5, nullptr}}, new Vertex{5, new VertexList{1, nullptr}, nullptr}}}}};
    V* g = new V(1, new VL(2, new VL(6, new VL(7))),
           new V(2, new VL(3, new VL(5, new VL(1))),
           new V(3, new VL(4, new VL(5, new VL(2))),
           new V(5, new VL(4, new VL(3)),
           new V(6, new VL(4, new VL(1, new VL(7))),
           new V(7, new VL(6)))))));

    //print
    VertexList* lp = longestPath(g, 2, 4);
    while (lp != nullptr)
    {
        cout << lp->v << " ";
        lp = lp->next;
    }
}