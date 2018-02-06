#include "UnitTestFramework.h"

#include <sstream>

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

std::string toStringRows(Cell* m) {
  std::ostringstream result;
  result << "{";
  for(; m; m = m->down) {
    result << "{";
    for(Cell* p = m; p; p = p->right)
      result << p->data << ' ';
    result << "}";
  }
  result << "}";
  return result.str();
}

std::string toStringCols(Cell* m) {
  std::ostringstream result;
  result << "{";
  for(; m; m = m->right) {
    result << "{";
    for(Cell* p = m; p; p = p->down)
      result << p->data << ' ';
    result << "}";
  }
  result << "}";
  return result.str();
}

Matrix M1 = {
  { 5, 4 },
  { -7, 3 }
};

Matrix M2 = {
  { 5, 4, 9 },
  { -7, 3, 2 },
  { 1, 4, 11 } 
};

Matrix M3 = {
  { 5, 4, 3, 8},
  { -7, 8, 2, 4 }
};

Matrix M4 = {
  { 0, 3, 1, 5},
  { -2, 3, 4, 8 },
  { 9, 6, 9, 0 },
};

Matrix M5 = {
  { 1, 2, 3, 1, 5 },
  { 5, 2, 6, 9, 6 },
  { 8, 7, 9, 1, 9 }
};


TEST_CASE("Problem12", Problem12_DeleteFirstRowColumn) {
  Cell* M = buildAdjungate(createMatrix(M1, 2, 2));
  Assert::AreEqual(toStringRows(M), "{{3 }}");
  Assert::AreEqual(toStringCols(M), "{{3 }}");
}

TEST_CASE("Problem12", Problem12_DeleteFirstLastRowColumn) {
  Cell* M = buildAdjungate(createMatrix(M2, 3, 3));
  Assert::AreEqual(toStringRows(M), "{{5 4 }{-7 3 }}");
  Assert::AreEqual(toStringCols(M), "{{5 -7 }{4 3 }}");
}

TEST_CASE("Problem12", Problem12_DeleteFirstRowLastColumn) {
  Cell* M = buildAdjungate(createMatrix(M3, 2, 4));
  Assert::AreEqual(toStringRows(M), "{{-7 8 2 }}");
  Assert::AreEqual(toStringCols(M), "{{-7 }{8 }{2 }}");
}

TEST_CASE("Problem12", Problem12_DeleteLastRowFirstColumn) {
  Cell* M = buildAdjungate(createMatrix(M4, 3, 4));
  Assert::AreEqual(toStringRows(M), "{{3 1 5 }{3 4 8 }}");
  Assert::AreEqual(toStringCols(M), "{{3 3 }{1 4 }{5 8 }}");
}

TEST_CASE("Problem12", Problem12_Example) {
  Cell* M  = buildAdjungate(createMatrix(M5, 3, 5));
  Assert::AreEqual(toStringRows(M), "{{1 2 3 5 }{8 7 9 9 }}");
  Assert::AreEqual(toStringCols(M), "{{1 8 }{2 7 }{3 9 }{5 9 }}");
}
