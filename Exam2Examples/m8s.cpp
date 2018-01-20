#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct VertexList {
    int v;
    VertexList* next;

    explicit VertexList(int _v, VertexList* _next = nullptr) : v(_v), next(_next) {}
};

struct Vertex {
    int u;
    VertexList* successors;
    Vertex* next;

    explicit Vertex(int _u, VertexList* _successors = nullptr, Vertex* _next = nullptr)
            : u(_u), successors(_successors), next(_next) {}
};

VertexList* getSuccessors(Vertex *graph, int v) {
    if (graph == nullptr) {
        return nullptr;
    }

    if (graph->u == v) {
        return graph->successors;
    }

    return getSuccessors(graph->next, v);
}

using Path = stack<int>;

bool contains(Path p, int v) {
    while (!p.empty()) {
        if (p.top() == v) {
            return true;
        }

        p.pop();
    }

    return false;
}

void getAllPathsDFSRec(Vertex *graph, int u, int v, Path& currentPath, vector<Path>& paths) {

    currentPath.push(u);

    if (u == v) {
        paths.push_back(currentPath);
    } else {

        VertexList* successors = getSuccessors(graph, u);

        while (successors != nullptr) {
            int next = successors->v;

            if (!contains(currentPath, next)) {
                getAllPathsDFSRec(graph, next, v, currentPath, paths);
            }

            successors = successors->next;
        }
    }

    currentPath.pop();
}

vector<Path> getAllPaths(Vertex *graph, int u, int v) {
    vector<Path> paths;
    Path currentPath;
    getAllPathsDFSRec(graph, u, v, currentPath, paths);
    return paths;
}

VertexList* longestPath(Vertex* graph, int u, int v) {
    if (graph == nullptr) {
        return nullptr;
    }

    vector<Path> paths = getAllPaths(graph, u, v);

    if (paths.empty()) {
        return nullptr;
    }

    // Find longest path (stack of vertices)
    Path longest = paths.back();
    while (!paths.empty()) {
        if (paths.back().size() > longest.size()) {
            longest = paths.back();
        }

        paths.pop_back();
    }

    // Reverse path
    VertexList* result = nullptr;

    while (!longest.empty()) {
        if (result == nullptr) {
            result = new VertexList(longest.top());
        } else {
            VertexList* temp = result;
            result = new VertexList(longest.top(), temp);
        }

        longest.pop();
    }

    return result;
}

void printPath(VertexList* path) {
    if (path == nullptr) {
        cout << "\n";
    } else {
        cout << path->v << " ";
        printPath(path->next);
    }
}

void printPaths(vector<Path> paths) {
    for (auto path : paths) {
        while (!path.empty()) {
            cout << path.top() << " ";
            path.pop();
        }
        cout << "\n";
    }
}

using V = Vertex;
using VL = VertexList;

int main() {

    V* g = new V(1, new VL(2, new VL(6, new VL(7))),
           new V(2, new VL(3, new VL(5, new VL(1))),
           new V(3, new VL(4, new VL(5, new VL(2))),
           new V(5, new VL(4, new VL(3)),
           new V(6, new VL(4, new VL(1, new VL(7))),
           new V(7, new VL(6)))))));

    // printPath(longestPath(g, 1, 6));

    // Prints the other way around but who gives a shite.
    printPaths(getAllPaths(g, 2, 4));

    return 0;
}
