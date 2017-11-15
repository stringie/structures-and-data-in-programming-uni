#include <iostream>
#include "Editor.h"
using namespace std;


int main() {

    Editor editor("example string");
    cout << editor.insert(1, "THIS ")->remove(0, 1)->insert(8, "IS ")->remove(5, 3)->insert(14, "C++")->remove(8, 6)->remove(11, 4)->getCurrent();
    cout <<endl<< editor.undo()->redo()->undo()->undo()->undo()->redo()->redo()->redo()->getCurrent();
}