#include "iostream"
using namespace std;

struct Cell
{
    int data;
    Cell *right, *down;
    Cell(int x, Cell* r, Cell* d) : data(x), right(r), down(d) {}
};

// Да се реализира функция,
// [подходящ тип] buildAdjungate([подходящ тип] M)
// която по дадена матрица M с поне два реда и поне две колони,
// зададена с указател към най-горна най-лява клетка, конструира нова матрица,
// която се получава от дадената чрез пропускане на реда и стълба, съответстващи 
// на максималния елемент в матрицата. При няколко максимални елемента, се избира 
// първия отгоре надолу и отляво надясно. 
int getMaxElement(Cell* M){
    if (M == nullptr)
        return INT32_MIN;

    int m = max(getMaxElement(M->down), getMaxElement(M->right));
    return max(M->data, m);
}

pair<int, int> getMaxElementPos(Cell* M){
    int max = getMaxElement(M);

    int x = 0, y = 0;
    Cell* dit = M;
    while(dit != nullptr){
        Cell* rit = dit;
        y = 0;
        while(rit != nullptr){
            if (rit->data == max){
                return make_pair(x, y);
            }
            rit = rit->right;
            y++;
        }

        dit = dit->down;
        x++;
    }
}

Cell* buildAdjungate(Cell* M){
    pair<int, int> maxElemPosition = getMaxElementPos(M);

    if (maxElemPosition.first == 0)
        M = M->down;
    if (maxElemPosition.second == 0)
        M = M->right;
    if (maxElemPosition.first == 0 && maxElemPosition.second == 0)
        return M;

    Cell* dit = M;
    int downpos = 0;
    while (dit != nullptr){
        Cell* rit = dit;
        int rightpos = 0;
        while (rit != nullptr) {
            if (downpos + 1 == maxElemPosition.first){
                rit->down = rit->down->down;
            }
            if (rightpos + 1 == maxElemPosition.second){
                rit->right = rit->right->right;
            }
            rit = rit->right;
            rightpos++;
        }
        dit = dit->down;
        downpos++;
    }

    return M;
}

#include "prob12-tests.h"
#include "UnitTestFramework.h"

int main() {
    RunTests();
}
