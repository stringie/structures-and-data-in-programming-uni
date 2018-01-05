#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

vector<vector<char>> getMatrix(ifstream& file, int n){
    vector<vector<char>> matrix(n, vector<char>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file >> matrix[i][j];
        }
    }

    return matrix;
}

pair<int, int> locateMouse(vector<vector<char>> matrix, int n){
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if(matrix[i][j] == 'm'){
                pair<int, int> mouse = make_pair(i, j);
                return mouse;
            }
        }
    }
}

void printMatrix(vector<vector<char>> matrix, int n){
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

void findPath(vector<vector<char>> matrix, pair<int, int> mouse, int n){
    stack<pair<int, int>> s;
    s.push(mouse);

    while(true){
        if(s.empty())
            break;
        int x = s.top().first;
        int y = s.top().second;

        if(matrix[x][y] == 'e'){
            break;
        }

        int count = 0;
        for (int i = -1; i < 2; ++i) {
            for (int j = -1; j < 2; ++j) {
                if(i == 0 ^ j == 0){
                    if(x + i >= 0 && x+ i < n && y + j >= 0 && y + j < n && (matrix[x+i][y+j] == '0' || matrix[x+i][y+j] == 'e')){
                        s.push(make_pair(x+i, y+j));
                        if(matrix[x+i][y+j] == '0')
                            matrix[x+i][y+j] = '.';
                        count++;
                    }
                }
            }
        }

        if(!count){
            s.pop();
        }
    }

    if(!s.empty()){
        int x = s.top().first;
        int y = s.top().second;
        cout << "at: (" << s.top().first << ", " << s.top().second << ")\n";
        s.pop();
        while(!s.empty()){
            int nextX = s.top().first;
            int nextY = s.top().second;
            if(abs(nextX - x) + abs(nextY - y) == 1){
                cout << "at: (" << s.top().first << ", " << s.top().second << ")\n";
                s.pop();
                x = nextX;
                y = nextY;
            } else{
                s.pop();
            }
        }

        printMatrix(matrix, n);
    } else{
        cout << "no exit!";
    }
}

int main() {
    ifstream file("/home/string/dev/structures-and-data-in-programming-uni/Homework2/Problem1.4/matrix.txt");
    int n; file >> n;

    vector<vector<char>> matrix = getMatrix(file, n);
    pair<int, int> mouse = locateMouse(matrix, n);

    findPath(matrix, mouse, n);
}