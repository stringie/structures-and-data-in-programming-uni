#include "iostream"
#include "stack"
using namespace std;

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

class KnightConfig
{
public:
    KnightConfig(int board, int knightNumber);
    ~KnightConfig();
    void printCurrentConfig();
    bool noMoreConfigs();
    void findNextConfig();

private:
    int n;
    int k;
    bool fin; 
    stack<Knight> knights;  
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
    bool placeNext(){
        if(knights.empty()){
            fin = true;
            return false;
        }

        Knight top = knights.top();
        top.iterate(n);
        knights.pop();
        while(overlapping(top, knights)){
            top.iterate(n);
        }
        if (top.x >= n){
            placeNext();
            return false;
        }else{
            knights.push(top);
            if(knights.size() < k){
                Knight copy = knights.top().copy();
                knights.push(copy);
                placeNext();
            }
            return true;
        }
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

KnightConfig::~KnightConfig(){}

void KnightConfig::findNextConfig(){
    bool placed = placeNext();
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
    
    KnightConfig config(5,5);
    while (!config.noMoreConfigs())
    {
        config.printCurrentConfig();
        config.findNextConfig();
    }

    int p;
    cin >> p; 
}