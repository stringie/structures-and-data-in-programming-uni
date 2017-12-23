#include "iostream"
#include "stack"
using namespace std;

//Knight piece structure with methods for overlapping with other piece and iterating across the board + copy Knight
struct Knight{
    int x;
    int y;

    Knight(int x_, int y_) : x(x_), y(y_) {}

    bool overlaps(Knight k){
        bool onTop = x == k.x && y == k.y;
        bool inReach = (x + 2 == k.x && y + 1 == k.y) ||
                        (x + 2 == k.x && y - 1 == k.y) ||
                        (x - 2 == k.x && y + 1 == k.y) ||
                        (x - 2 == k.x && y - 1 == k.y) ||
                        (x + 1 == k.x && y + 2 == k.y) ||
                        (x + 1 == k.x && y - 2 == k.y) ||
                        (x - 1 == k.x && y + 2 == k.y) ||
                        (x - 1 == k.x && y - 2 == k.y);

        return onTop || inReach;
    }

    void iterate(int n){
        y++;
        if(y == n){
            y = 0;
            x++;
        }
    }

    Knight copy(){
        return Knight(x,y);
    }
};

class KnightConfig
{
public:
    KnightConfig(int board, int knightNumber);
    void printCurrentConfig();
    bool noMoreConfigs();
    void findNextConfig();

private:
    int n;
    int k;
    bool fin; 
    stack<Knight> knights;  

    //checking whether x y position is in knight stack
    bool isElemInStack(stack<Knight> s, int x, int y){
        while (!s.empty())
        {
            if (s.top().x == x && s.top().y == y){
                return true;
            }
            s.pop();
        }

        return false;
    }

    //method for overlapping knights
    bool overlapping(Knight knight, stack<Knight> s){
        while (!s.empty())
        {
            if(s.top().overlaps(knight)){
                return true;
            }
            s.pop();
        }
        return false;
    }
};

KnightConfig::KnightConfig(int board, int knightNumber)
{
    n = board;
    k = knightNumber;
    fin = false;
    for (size_t i = 0; i < knightNumber; i++)
    {
        Knight knight(0,i);
        knights.push(knight);
    }
}

void KnightConfig::findNextConfig(){
    //endgame
    if(knights.empty()){
        fin = true;
        return;
    }

    //pop top and iterate to next available position
    Knight top = knights.top();
    top.iterate(n); // cant stay in the same position
    knights.pop();
    while(overlapping(top, knights)){
        top.iterate(n);
    }

    //if outside board, discard piece, call recursively for next piece in stack
    //else push to stack and place recursively rest
    if (top.x >= n){
        findNextConfig();
    }else {
        knights.push(top);
        if(knights.size() < k){
            Knight copy = knights.top().copy();
            knights.push(copy);
            findNextConfig();
        }
    }
}

void KnightConfig::printCurrentConfig(){
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if (isElemInStack(knights, i, j)){
                cout << "H ";
            }else{
                cout << "_ ";
            }
        }
        cout << "\n";
    }
    cout << "\n";
}

bool KnightConfig::noMoreConfigs(){
    return fin;
}

int main(){
    
    int n, k; cin >> n >> k;

    KnightConfig config(n,k);
    while (!config.noMoreConfigs())
    {
        config.printCurrentConfig();
        config.findNextConfig();
    }

    //for viewing the debug window
    int p;
    cin >> p; 
}