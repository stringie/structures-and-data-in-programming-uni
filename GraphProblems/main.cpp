#include "iostream"
#include "vector"
using namespace std;

int hasPaths(string path, vector<vector<char>> g, int n, int from){
    int paths = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (path.front() == g[i][j] && (from == -1 ? true : (from == i))){
                if (path.size() == 1){
                    paths += 1;
                }else{
                    string nextPath = path;
                    auto it = nextPath.begin();
                    it = nextPath.erase(it);
                    paths += hasPaths(nextPath, g, n, j);
                }
            }
        }
    }

    return paths;
}


int main(){
    int n = 5;
    vector<vector<char>> g{{'z','q','c','n','g'},{'y','c','a','p','a'},{'s','b','k','l','t'},{'c','c','x','x','x'},{'y','y','y','b','x'}};
    string path = "abc";
    int from = -1;    

    int paths = hasPaths(path, g, n, from);
    cout << paths;
}   
