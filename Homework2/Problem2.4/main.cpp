#include <iostream>
#include <fstream>
#include "vector"
#include "queue"

using namespace std;

vector<pair<int, int>> getPlayers(vector<vector<char>> matrix, int n){

    vector<pair<int, int>> players;
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            if(matrix[k][i] != 'x' && matrix[k][i] != '*' && matrix[k][i] != '0'){
                players.push_back(make_pair(k, i));
            }
        }
    }

    return players;
}


vector<vector<char>> getMatrix(int n, ifstream &file){
    vector<vector<char>> matrix(n, vector<char>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file >> matrix[i][j];
        }
    }

    return matrix;
}

int FindPath(int x, int y, vector<vector<char>> matrix, int n){

    queue<pair<int, pair<int, int>>> path;
    path.push(make_pair(0, make_pair(x, y)));

    while(true){
        int currX = get<0>(get<1>(path.front()));
        int currY = get<1>(get<1>(path.front()));
        int length = get<0>(path.front());

        if(matrix[currX][currY] == '*'){
            return get<0>(path.front());
        }

        for (int i = -1; i < 2; ++i) {
            for (int j = -1; j < 2; ++j) {
                if(i == 0 ^ j == 0){
                    if(currX + i >= 0 && currX + i < n && currY + j >= 0 && currY + j < n && (matrix[currX+i][currY+j] == '0' || matrix[currX+i][currY+j] == '*')){
                        path.push(make_pair(length + 1, make_pair(currX + i, currY + j)));
                    }
                }
            }
        }
        matrix[currX][currY] = '+';
        path.pop();
    }
}

void PrintMatrix(vector<vector<char>> matrix, int n){
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matrix[i][j];
        }
        cout << endl;
    }
}

int main() {


    ifstream file("/home/string/dev/data-structures/Homework2/Problem2.4/matrix.txt");
    int n; file >> n;

    vector<vector<char>> matrix = getMatrix(n, file);
    vector<pair<int, int>> players = getPlayers(matrix, n);

    PrintMatrix(matrix, n);

    for(auto t : players){
        int x = get<0>(t);
        int y = get<1>(t);
        cout << "player at: (" << x << ", " << y << ") " << "-> path length: " << FindPath(x, y, matrix, n) << endl;
    }
}