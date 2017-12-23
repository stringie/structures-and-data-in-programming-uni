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
};

class KnightConfig{
private:
    bool fin;
    bool begin;
    int n;
    int k;
    stack<Knight> knights;

    bool placeKnight(Knight previous = Knight(-10,-10)){

        if(knights.empty() && begin){
            Knight first(0,0);
            Knight second(0,1);
            knights.push(first);
            knights.push(second);
            begin = false;
            return true;
        }

        int i = previous.x;
        int j = previous.y;
        if(previous.y == (n-1)){
            i++;
            j=0;
        }

        for (; i < n; ++i) {
            for (; j < n; ++j) {
                Knight knight(i,j);
                bool overlapping = false;
                stack<Knight> temp;
                for (int l = 0; l < temp.size() + knights.size(); ++l) {
                    Knight t = knights.top();
                    knights.pop();
                    temp.push(t);
                    if (t.overlaps(knight)){
                        overlapping = true;
                        break;
                    }
                }
                while (!temp.empty()){
                    knights.push(temp.top());
                    temp.pop();
                }

                if (!overlapping && !knight.overlaps(previous)){
                    knights.push(knight);
                    if(knights.top().x == (n-1) && knights.top().y == (n-1) && knights.size() == 1){
                        fin = true;
                        return true;
                    }
                    return true;
                }
            }
        }



        return false;
    }

public:
    KnightConfig(int n_, int k_) : n(n_), k(k_), fin(false), begin(true) {findNextConfig();}

    void printCurrentConfig(){
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                stack<Knight> temp;
                bool there = false;
                for (int l = 0; l < k; ++l) {
                    Knight k = knights.top();
                    knights.pop();
                    temp.push(k);
                    if (k.x == i && k.y == j){
                        there = true;
                        break;
                    }
                }
                if (there){
                    cout << "H ";
                }else{
                    cout << "_ ";
                }
                while (!temp.empty()){
                    knights.push(temp.top());
                    temp.pop();
                }
            }
            cout << "\n";
        }
        cout << "\n";
    }

    void findNextConfig(){
        if(knights.empty() && begin){
            placeKnight();
        } else{
            Knight prev = knights.top();
            knights.pop();
            bool placed = placeKnight(prev);
            if (!placed){
                findNextConfig();
            }
            while (knights.size() != k && placed && !fin){
                Knight previous = knights.top();
                bool place = placeKnight(previous);
            }
        }
    }

    bool noMoreConfigs(){
        return fin;
    }
};


int main(){
    int n; int k; cin >> n >> k;
    KnightConfig config(n, k);

    while (!config.noMoreConfigs()){
        config.printCurrentConfig();
        config.findNextConfig();
    }
    cout << "no more";
}

