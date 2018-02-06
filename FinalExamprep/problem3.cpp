/////////////////////////////////////////////////////////////
//
// Author: попълнете името си тук
// FN: попълнете факултетния си номер тук
// Date: 21.01.2018
//

///
/// Структура, описваща клетка в матрица
///

#include "iostream"
using namespace std;

struct Cell
{
  int data;
  Cell *right, *down;
};

// Да се реализира функция,
// [подходящ тип] buildAdjungate([подходящ тип] M)
// която по дадена матрица M с поне два реда и поне две колони, зададена с указател към най-горна най-лява клетка, конструира нова матрица, която се получава от дадената чрез пропускане на реда и стълба, съответстващи на максималния елемент в матрицата. При няколко максимални елемента, се избира първия отгоре надолу и отляво надясно. 

using Matrix = int[100][100];

Cell* createMatrix(Matrix a, int m, int n) {
  Cell* result;
  Cell** p = &result;
  for(int i = 0; i < n; i++, p = &(*p)->right)
    *p = new Cell{ a[0][i], nullptr, nullptr };
  Cell* prow = result;
  p = &result->down;
  for(int i = 1; i < m; i++, p = &(*p)->down, prow = prow->down, p = &prow->down) {
    Cell* pp = prow;
    for(int j = 0; j < n; j++, pp = pp->right, p = &(*p)->right)
      *p = pp->down = new Cell { a[i][j], nullptr, nullptr };
  }
  return result;
}

Matrix M5 = {
  { 1, 2, 3, 1, 5 },
  { 5, 2, 6, 9, 6 },
  { 8, 7, 9, 1, 9 }
};

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

void buildAdjungate(Cell*& M){
    pair<int, int> maxElemPosition = getMaxElementPos(M);

    Cell* dit = M;
    while (dit != nullptr){
        Cell* rit = dit;
        int rightpos = 0;
        while (rit->right != nullptr) {
            if (rightpos + 1 == maxElemPosition.second){
                rit->right = rit->right->right;
                rightpos++;
            }else{
                rit = rit->right;
                rightpos++;
            }
        }

        dit = dit->down;
    }

    dit = M;
    int downpos = 0;
    while (dit != nullptr){
        Cell* rit = dit;
        while (rit->right != nullptr){
            if (downpos + 1 == maxElemPosition.first){
                rit->down = rit->down->down;
            }
            rit = rit->right;
        }
        dit = dit->down;
        downpos++;
    }
}

//-------------------------------------------------------------------------
//
// ВАЖНО: Преди предаване на решението, моля премахнете коментара от дадения по-долу ред,
//        за да активирате автоматичните тестове за решението си.
//
//-------------------------------------------------------------------------
//#include "prob12-tests.h"

#include "UnitTestFramework.h"

int main() {

    Cell* m = createMatrix(M5, 3, 5);
    buildAdjungate(m);


  //-------------------------------------------------------------------------
  //
  // ВАЖНО: При предаване на работата във тялото на функцията main не трябва да се
  //        изпълнява нищо друго освен функцията RunTests().
  //
  //-------------------------------------------------------------------------
//   RunTests();

  return 0;
}
